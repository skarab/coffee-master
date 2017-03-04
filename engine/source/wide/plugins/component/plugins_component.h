#ifndef _COFFEE_PLUGINS_COMPONENT_H_
#define _COFFEE_PLUGINS_COMPONENT_H_

#include "coffee_includes.h"
#include "system/scene/component/scene_component.h"
#include "system/physics/physics_collision.h"
#include "wide/plugins/plugins_object.h"
#include "wide/plugins/component/plugins_component_library.h"

namespace coffee
{
namespace plugins
{
    class ComponentWrapper;

    //--------------------------------------------------------------------------------------------//
    /// Scriptable component
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Component : public meta::Object
    {
        friend class ComponentWrapper;

        COFFEE_Type(Component);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Component();
        virtual ~Component();

        //-ACCESSORS------------------------------------------------------------------------------//
        
        const scene::Node& GetNode() const;
        scene::Node& GetNode();

        //-HANDLERS-------------------------------------------------------------------------------//

        // Basics

        virtual void OnStart() {}
        virtual void OnStop() {}
        virtual void OnUpdate(const basic::Time& time_step) {}
        virtual void OnFixedUpdate(const basic::Time& time_step) {}
        
        // Physics

        virtual bool HandlePhysics() const { return false; }
        virtual void OnCollisionBegin(const physics::Collision& collision) {}
        virtual void OnCollision(const physics::Collision& collision) {}
        virtual void OnCollisionEnd(const physics::Collision& collision) {}

        // Inputs

        virtual bool HandleInputs() const { return false; }
        virtual bool OnInputEvent(const input::EVENT& event, const void* parameters) { return false; }

        // Internals

        virtual void OnPropertyModified(const void* prop) {}   
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ComponentWrapper* _Wrapper;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Component);

    //--------------------------------------------------------------------------------------------//
    /// Wrapped resource
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComponentObject : public plugins::Object
    {
        COFFEE_Resource(ComponentObject);
    public:
        ComponentObject() {}
        ~ComponentObject() {}
    };
    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComponentObject);

    //--------------------------------------------------------------------------------------------//
    /// Component wrapping the scriptable component
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComponentWrapper : public scene::Component
    {
        COFFEE_Component(ComponentWrapper, "Component", "Script/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComponentWrapper();
        ~ComponentWrapper();

        //-ACCESSORS------------------------------------------------------------------------------//

        const plugins::Component& GetComponent() const { return * _Component; }
        plugins::Component& GetComponent() { return * _Component; }

        template<typename type>
        type* Grab(const basic::String& name)
        {
            if (IsReady())
            {
                const meta::Attribute* attribute = _Component->GetMetaType().FindAttribute(name);
                if (attribute!=NULL && attribute->_Type==&meta::TYPE<type>().Get())
                    return (type*)((char*)_Component+attribute->_Offset);
            }
            return NULL;
        }

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsReady() const { return _Component!=NULL; }

        //-HANDLERS-------------------------------------------------------------------------------//

        // Basics

        void OnStart();
        void OnStop();
        void OnUpdate(const basic::Time& time_step);
        void OnFixedUpdate(const basic::Time& time_step);

        // Physics

        bool HandlePhysics();
        void OnCollisionBegin(const physics::Collision& collision);
        void OnCollision(const physics::Collision& collision);
        void OnCollisionEnd(const physics::Collision& collision);

        // Inputs

        bool HandleInputs();
        bool OnInputEvent(const input::EVENT& event, const void* parameters);
        
        // Internals
        
        void OnPropertyModified(const void* prop);        
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void PreSerialize(storage::MODE mode);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _CheckValidity();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        plugins::ComponentObject _Resource;
        resource::Handler<plugins::ComponentObject> _Handler;
        plugins::Component* _Component;
        basic::Array<uint8> _Data;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComponentWrapper);
}
}
#endif
