#ifndef _COFFEE_SHELL_EVENT_HANDLER_H_
#define _COFFEE_SHELL_EVENT_HANDLER_H_

#include "coffee_includes.h"
#include "kernel/basic/hierarchy/tree/basic_tree_node.h"
#include "kernel/shell/event/shell_event.h"
#include "kernel/shell/event/shell_event_handler_method.h"
#include "kernel/shell/event/shell_event_queue.h"
#include "kernel/shell/event/shell_event_message.h"
#include "kernel/shell/thread/shell_mutex.h"

namespace coffee
{
namespace shell
{
    //-FORWARDS-----------------------------------------------------------------------------------//
    class Module;

    //--------------------------------------------------------------------------------------------//
    /// Event handler
    ///
    /// It manages hierarchical events using such things as event queuing,
    /// handlers registration, ...
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API EventHandler : public basic::TreeNode<EventHandler>
    {
        friend class Module;

        COFFEE_Type(EventHandler);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        EventHandler();
        virtual ~EventHandler();

        //-ACCESSORS------------------------------------------------------------------------------//

        bool IsEnabled() const { return _ItIsEnabled; }
        bool IsDestroyed() const { return _ItIsDestroyed; }

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsQueueEmpty() const;
        bool AreQueuesEmpty() const;

        // Don't process any events when it's locked
        virtual bool IsLockingEvents() const { return false; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Register(EventHandler& event_handler);
        bool Unregister();
        void Register(void* class_instance, bool (*handler_method)(void*, Event&),
            const EventCode& handled_code=EventCode());
        void Unregister(void* class_instance);
        void SendEvent(const Event& event);
        void ForwardEvent(const Event& event);
        bool SendImmediateEvent(const Event& event);
        
        void Enable(bool it_has_to_enable, bool it_has_to_set_children=true);
        virtual void Destroy();
        void DestroyChildren();
        virtual void Update();
        virtual bool OnEvent(Event& event) { return false; }
        virtual bool OnPackEvents(Event& new_event, const Event& old_event) { return false; }
        virtual void OnUnhandledEvent(Event& event) {}
        virtual void OnDestroyEvent(Event& event) {}
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(EventHandler);
        COFFEE_Event bool OnEnable(Event& event);
        
    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _LockUpdate();
        void _UnlockUpdate();
        bool _InternHandleAncestorEvent(Event& event);
        
    private:

        //-ACCESSORS------------------------------------------------------------------------------//

        bool _IsHierarchyLocked() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool _DispatchEvent(Event& event);
        bool _DispatchEvent(EventHandler& handler, Event& event);
        void _ProcessEvents();
        bool _ProcessEvent(Event& event);
        void _SendKillMessage();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Vector<EventHandlerMethod> _HandlerMethodArray;
        EventQueue _Queue;
        Mutex _QueueMutex;
        bool _ItIsEnabled;
        bool _ItIsDestroyed;
        int32 _UpdateLock;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, EventHandler);
}
}
#endif
