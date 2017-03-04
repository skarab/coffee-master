#ifndef _COFFEE_SCENE_COMPONENT_H_
#define _COFFEE_SCENE_COMPONENT_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "system/scene/scene_flag.h"
#include "system/physics/physics_collision.h"
#include "system/input/input_event.h"

namespace coffee
{
namespace graphics
{
    class Viewport;
}
namespace scene
{
    //-FORWARDS-----------------------------------------------------------------------------------//
    class Node;

    //--------------------------------------------------------------------------------------------//
    /// Scene component interface
    ///
    /// @see scene::Node, graphics::Component
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Component : public meta::Object
    {
        friend class Node;

        COFFEE_Type(Component);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Component();
        virtual ~Component();

        //-ACCESSORS------------------------------------------------------------------------------//

        virtual const basic::String GetName() const { return ""; }
        virtual const basic::String GetClassification() const { return ""; }
        const Node& GetNode() const { return *_Node; }
        Node& GetNode() { return *_Node; }
        const uint32& GetFlags() const { return _Flags; }
        bool IsRunning() const { return COFFEE_IsFlagEnabled(_Flags, FLAG_Running); }
        void SetIsAutomatic(bool it_is_automatic);
        bool IsAutomatic() const { return COFFEE_IsFlagEnabled(_Flags, FLAG_Automatic); }
        void SetIsInstantiable(bool it_is_instantiable) { COFFEE_EnableFlag(_Flags, FLAG_Instantiable, it_is_instantiable); }
        bool IsInstantiable() const { return COFFEE_IsFlagEnabled(_Flags, FLAG_Instantiable); }
        void SetIsStoppedInEditor(bool it_is_stopped_in_editor);
        bool IsStoppedInEditor() const { return COFFEE_IsFlagEnabled(_Flags, FLAG_StopInEditor); }
        
        //-QUERIES--------------------------------------------------------------------------------//

        bool HasNode() const { return _Node!=NULL; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Start();
        void Stop();
        void Restart();

        void PostSerialize(storage::MODE mode);
        
        //-HANDLERS-------------------------------------------------------------------------------//

        // Basics

        virtual void OnStart() {};
        virtual void OnStop() {};
        virtual void OnUpdate(const basic::Time& time_step) {};
        virtual void OnFixedUpdate(const basic::Time& time_step) {};
        virtual void OnPropertyModified(const void* prop);
        
        // Physics

        virtual bool HandlePhysics() { return false; }
        virtual void OnCollisionBegin(const physics::Collision& collision) {}
        virtual void OnCollision(const physics::Collision& collision) {}
        virtual void OnCollisionEnd(const physics::Collision& collision) {}

        // Inputs

        virtual bool HandleInputs() { return false; }
        virtual bool OnInputEvent(const input::EVENT& event, const void* parameters) { return false; }
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Node* _Node;
        uint32 _Flags;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Component);
}
}
#endif
