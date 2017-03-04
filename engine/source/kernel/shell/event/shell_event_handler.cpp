#include "kernel/shell/event/shell_event_handler.h"
#include "coffee.h"

#define SHELL_EVENT_HANDLER_BeginSaveChildrenLoop() \
    int32 count = (int32)GetChildCount(); \

#define SHELL_EVENT_HANDLER_EndSaveChildrenLoop() \
        if (count>(int32)GetChildCount()) \
        { \
            index -= count-(int32)GetChildCount(); \
            if (index+1<0 || index+1>=(int32)GetChildCount()) \
                break; \
        } \

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(shell::EventHandler);
        COFFEE_Attribute(basic::Prow< shell::EventHandler * >, _Children, meta::MODE_Serializeable);
    COFFEE_EndType();

namespace shell
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    EventHandler::EventHandler() :
        _ItIsEnabled(true),
        _ItIsDestroyed(false),
        _UpdateLock(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    EventHandler::~EventHandler()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool EventHandler::IsQueueEmpty() const
    {
        return _Queue.IsEmpty();
    }

    //--------------------------------------------------------------------------------------------//

    bool EventHandler::AreQueuesEmpty() const
    {
        if (!IsQueueEmpty())
            return false;

        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            if (!((EventHandler*)&GetChild(child_index))->AreQueuesEmpty())
                return false;
        }
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool EventHandler::Register(EventHandler& event_handler)
    {
        Attach(event_handler);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool EventHandler::Unregister()
    {
        Detach();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void EventHandler::Register(void* class_instance, bool (* handler_method)(void *, Event &),
        const EventCode& handled_code)
    {
        _HandlerMethodArray.AddItem(EventHandlerMethod(
            handled_code, class_instance, handler_method));
    }

    //--------------------------------------------------------------------------------------------//

    void EventHandler::Unregister(void* class_instance)
    {
        uint32 method_index(0);
        while (method_index<_HandlerMethodArray.GetSize())
        {
            if (_HandlerMethodArray[method_index].GetClassInstance()==class_instance)
            {
                _HandlerMethodArray.Remove(method_index);
            }
            else
            {
                ++method_index;
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void EventHandler::SendEvent(const Event& event)
    {
        Event ev(event);
        ev.SetTarget(this);
        ForwardEvent(ev);
    }

    //--------------------------------------------------------------------------------------------//

    void EventHandler::ForwardEvent(const Event& event)
    {
        _QueueMutex.Lock();
        Event new_event = event;
        for (int32 i=(int32)_Queue.Events.GetSize()-1 ; i>=0 ; --i)
        {
            if (OnPackEvents(new_event, _Queue.Events[i]))
            {
                OnDestroyEvent(_Queue.Events[i]);
                _Queue.Events.Remove(i);
            }
        }
        _Queue.AddEvent(new_event);
        _QueueMutex.Unlock();
    }

    //--------------------------------------------------------------------------------------------//

    bool EventHandler::SendImmediateEvent(const Event& event)
    {
        Event ev(event);
        ev.SetTarget(this);
        ev.EnableFlag(EVENT_FLAG_Immediate, true);
        return _ProcessEvent(ev);
    }
    
    //--------------------------------------------------------------------------------------------//

    void EventHandler::Enable(bool it_has_to_enable, bool it_has_to_set_children)
    {
        EventCode event_code((uint32)EVENT_MESSAGE_Enable, GetClassMetaType());
        Event shell_event;
        shell_event.Set(event_code, EventParameters((void*)(it_has_to_enable?1:0),
            (meta::Object*)(it_has_to_set_children?1:0)), EVENT_FLAG_ForwardToParent);
        SendEvent(shell_event);
    }
        
    //--------------------------------------------------------------------------------------------//

    void EventHandler::Destroy()
    {
        _ItIsDestroyed = true;
        if (!_IsHierarchyLocked())
        {
            _SendKillMessage();
            basic::TreeNode<EventHandler>::Destroy();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void EventHandler::DestroyChildren()
    {
        for (int32 index=0 ; index<(int32)GetChildCount() ; ++index)
        {
            SHELL_EVENT_HANDLER_BeginSaveChildrenLoop();
            static_cast<EventHandler&>(GetChild(index)).Destroy();
            SHELL_EVENT_HANDLER_EndSaveChildrenLoop();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void EventHandler::Update()
    {
        _LockUpdate();
        for (int32 index=0 ; index<(int32)GetChildCount() ; ++index)
        {
            SHELL_EVENT_HANDLER_BeginSaveChildrenLoop();
            static_cast<EventHandler&>(GetChild(index)).Update();
            SHELL_EVENT_HANDLER_EndSaveChildrenLoop();
        }
        _UnlockUpdate();
        _ProcessEvents();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    bool EventHandler::OnEnable(Event& event)
    {
        _ItIsEnabled = event.GetBoolean();
        if (event.GetParameters().GetParameter()!=0)
        {
            for (int32 index=0 ; index<(int32)GetChildCount() ; ++index)
            {
                SHELL_EVENT_HANDLER_BeginSaveChildrenLoop();
                static_cast<EventHandler&>(GetChild(index)).OnEnable(event);
                SHELL_EVENT_HANDLER_EndSaveChildrenLoop();
            }
        }
        return true;
    }
    
    //-OPERATIONS---------------------------------------------------------------------------------//

    bool EventHandler::_HandleEvent(Event& event)
    {
        return _InternHandleEvent(event)
            || _InternHandleAncestorEvent(event);
    }

    //--------------------------------------------------------------------------------------------//

    bool EventHandler::_InternHandleEvent(Event& event)
    {
        if(&event.GetCode().GetType()==&GetClassMetaType()
            && event.GetTarget()==this
            && event.GetCode().GetIdentifier()==EVENT_MESSAGE_Enable && OnEnable(event))
        {
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void EventHandler::_LockUpdate()
    {
        COFFEE_Assert(_UpdateLock<10, core::ERROR_CODE_Unexpected, "Event handler lock overflow detected");
        ++_UpdateLock;
    }

    //--------------------------------------------------------------------------------------------//

    void EventHandler::_UnlockUpdate()
    {
        COFFEE_Assert(_UpdateLock>0, core::ERROR_CODE_Unexpected, "Event handler lock leak detected");
        --_UpdateLock;
    }
        
    //--------------------------------------------------------------------------------------------//

    bool EventHandler::_InternHandleAncestorEvent(Event & event)
    {
        return false;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    bool EventHandler::_IsHierarchyLocked() const
    {
        if (_UpdateLock>0)
            return true;
        for (int32 index=0 ; index<(int32)GetChildCount() ; ++index)
        {
            if (static_cast<const EventHandler&>(GetChild(index))._IsHierarchyLocked())
                return true;
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool EventHandler::_DispatchEvent(Event & event)
    {
        uint32 method_index;

        if (OnEvent(event) && event.IsFlagEnabled(EVENT_FLAG_StopWhenHandled))
            return true;

        for (method_index=0 ; method_index<_HandlerMethodArray.GetSize() ; ++method_index)
        {
            if (_HandlerMethodArray[ method_index ].GetHandledCode().GetIdentifier() == (uint32) NONE
                || _HandlerMethodArray[ method_index ].GetHandledCode() == event.GetCode())
            {
                if(_HandlerMethodArray[ method_index ].Call(event)
                    && event.IsFlagEnabled(EVENT_FLAG_StopWhenHandled))
                {
                    return true;
                }
            }
        }

        if (_HandleEvent(event))
            return true;

        if (event.IsFlagEnabled(EVENT_FLAG_ForwardToChildren))
        {
            for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
            {
                EventHandler& handler = static_cast<EventHandler&>(GetChild(child_index));
                if (handler.IsEnabled() && _DispatchEvent(handler, event))
                    return true;
            }
        }
        else if (event.IsFlagEnabled(EVENT_FLAG_ForwardToParent))
        {
            if (HasParent())
                return _DispatchEvent(static_cast<EventHandler&>(GetParent()), event);
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool EventHandler::_DispatchEvent(EventHandler& handler, Event& event)
    {
        if (event.IsFlagEnabled(EVENT_FLAG_Immediate))
        {
            if (handler._DispatchEvent(event)
                && event.IsFlagEnabled(EVENT_FLAG_StopWhenHandled))
            {
                return true;
            }
        }
        else
        {
            handler.ForwardEvent(event);
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void EventHandler::_ProcessEvents()
    {
        if (IsLockingEvents() && !_ItIsDestroyed)
            return;

        int32 count = Engine::Get().HasMode(RUN_MODE_Events)?6:32;
        
        _LockUpdate();        
        for (int32 i=0 ; i<count ; ++i)
        {
            Event event;
        
            _QueueMutex.Lock();
            bool empty = !_Queue.PickEvent(event);
            _QueueMutex.Unlock();
            if (empty)
                break;

            _ProcessEvent(event);

            if (IsLockingEvents() && !_ItIsDestroyed)
                break;

            // Make sure all events are processed before destroying
            if (_ItIsDestroyed)
                --i;
        }        
        _UnlockUpdate();        
        
        if (_ItIsDestroyed)
        {
            _SendKillMessage();
            Destroy();
        }
    }

    //--------------------------------------------------------------------------------------------//

    bool EventHandler::_ProcessEvent(Event& event)
    {
        _LockUpdate();
        bool result = true;
        if (_ItIsDestroyed || !_DispatchEvent(event))
        {
            OnUnhandledEvent(event);
            result = false;
        }
        OnDestroyEvent(event);
        _UnlockUpdate();
        return result;
    }
        
    //--------------------------------------------------------------------------------------------//

    void EventHandler::_SendKillMessage()
    {
        Event event;

        _QueueMutex.Lock();
        while(_Queue.PickEvent(event))
        {
            OnUnhandledEvent(event);
            OnDestroyEvent(event);
        }
        _QueueMutex.Unlock();

        event.Set(
            EventCode(EVENT_MESSAGE_Destroyed, GetClassMetaType()),
            EventParameters(),
            EVENT_FLAG_StopWhenHandled|((HasParent()&&!GetParent().IsDestroyed())?EVENT_FLAG_ForwardToParent:0));
        event.SetTarget(this);
        _DispatchEvent(event);
    }

}
}
