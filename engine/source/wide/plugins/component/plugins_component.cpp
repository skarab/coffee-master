#include "wide/plugins/component/plugins_component.h"
#include "wide/application/application.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(plugins::Component);
    COFFEE_EndType();

    //--------------------------------------------------------------------------------------------//
    
    COFFEE_BeginResource(plugins, ComponentObject, "Scriptable component", "component", 0);
        COFFEE_Ancestor(plugins::Object);
    COFFEE_EndResource();

    //--------------------------------------------------------------------------------------------//
    
    COFFEE_BeginType(plugins::ComponentWrapper);
        COFFEE_Ancestor(scene::Component);
        COFFEE_Attribute(plugins::ComponentObject, _Resource, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(plugins::Component*, _Component, meta::MODE_Editable);
        COFFEE_Attribute(<uint8>, _Data, meta::MODE_Serializeable);
    COFFEE_EndType();

namespace plugins
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component() :
        _Wrapper(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Component::~Component()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//
        
    const scene::Node& Component::GetNode() const
    {
        COFFEE_Assert(_Wrapper!=NULL, core::ERROR_CODE_Unexpected, "Component is not binded");
        return _Wrapper->GetNode();
    }

    //--------------------------------------------------------------------------------------------//

    scene::Node& Component::GetNode()
    {
        COFFEE_Assert(_Wrapper!=NULL, core::ERROR_CODE_Unexpected, "Component is not binded");
        return _Wrapper->GetNode();
    }

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComponentWrapper::ComponentWrapper() :
        _Component(NULL),
        _Handler(&_Resource)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ComponentWrapper::~ComponentWrapper()
    {        
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void ComponentWrapper::OnStart()
    {
        if (_Resource.GetFilePath().IsEmpty())
        {
            _Resource = resource::Manager::Get().Load(
                storage::Path("/coffee/import/null.component"));
        }
        else if (IsReady())
        {
            _Component->OnStart();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ComponentWrapper::OnStop()
    {
        _CheckValidity();

        if (IsReady())
            _Component->OnStop();
    }

    //--------------------------------------------------------------------------------------------//

    void ComponentWrapper::OnUpdate(const basic::Time& time_step)
    {
        _CheckValidity();

        if (IsReady())
            _Component->OnUpdate(time_step);
    }

    //--------------------------------------------------------------------------------------------//

    void ComponentWrapper::OnFixedUpdate(const basic::Time& time_step)
    {
        _CheckValidity();

        if (IsReady())
            _Component->OnFixedUpdate(time_step);
    }

    //--------------------------------------------------------------------------------------------//

    bool ComponentWrapper::HandlePhysics()
    {
        _CheckValidity();

        if (IsReady())
            return _Component->HandlePhysics();
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void ComponentWrapper::OnCollisionBegin(const physics::Collision& collision)
    {
        if (IsReady())
            _Component->OnCollisionBegin(collision);
    }

    //--------------------------------------------------------------------------------------------//

    void ComponentWrapper::OnCollision(const physics::Collision& collision)
    {
        if (IsReady())
            _Component->OnCollision(collision);
    }

    //--------------------------------------------------------------------------------------------//

    void ComponentWrapper::OnCollisionEnd(const physics::Collision& collision)
    {
        if (IsReady())
            _Component->OnCollisionEnd(collision);
    }

    //--------------------------------------------------------------------------------------------//

    bool ComponentWrapper::HandleInputs()
    {
        _CheckValidity();

        if (IsReady())
            return _Component->HandleInputs();
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void ComponentWrapper::OnPropertyModified(const void* prop)
    {
        if (IsReady())
            _Component->OnPropertyModified(prop);
    }

    //--------------------------------------------------------------------------------------------//

    bool ComponentWrapper::OnInputEvent(const input::EVENT& event, const void* parameters)
    {
        if (IsReady())
            return _Component->OnInputEvent(event, parameters);
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ComponentWrapper::PreSerialize(storage::MODE mode)
    {
        if (mode==storage::MODE_Output && IsReady())
            _Component->SerializeToArray(_Data, storage::MODE_Output);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ComponentWrapper::_CheckValidity()
    {
        if (!_Resource.IsReady())
        {
            _Component = NULL;
            return;
        }

        switch (_Handler.Update())
        {
            case resource::HANDLER_STATE_Ready:
            {
                if (_Component==NULL)
                {
                    _Component = static_cast<ComponentLibrary&>(_Resource.GrabLibrary()).CreateComponent<plugins::Component>();
                    if (_Component!=NULL)
                    {
                        _Component->_Wrapper = this;
                        _Component->SerializeToArray(_Data, storage::MODE_Input);

                        // TODO:: Add checkbox to stop it if its in editor mode
                        //if (!Engine::Get().HasMode(RUN_MODE_Editor))
                            
                        _Component->OnStart();
                    }
                }
            } break;

            default:
            {
                _Component = NULL;
            } break;
        }
    }

}
}
