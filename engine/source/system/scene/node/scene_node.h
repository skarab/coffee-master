#ifndef _COFFEE_SCENE_NODE_H_
#define _COFFEE_SCENE_NODE_H_

#include "coffee_includes.h"
#include "kernel/basic/hierarchy/tree/basic_tree_node.h"
#include "system/scene/scene_flag.h"
#include "system/scene/component/scene_component.h"
#include "system/scene/transform/scene_transform.h"
#include "system/scene/bounding/scene_bounding.h"
#include "system/scene/path/scene_path.h"
#include "wide/plugins/component/plugins_component.h"

namespace coffee
{
    //-FORWARDS-----------------------------------------------------------------------------------//
    namespace input { class Component; }
    namespace graphics { class Component; }
    namespace physics { class Component; class RigidBody; }

namespace scene
{
    //--------------------------------------------------------------------------------------------//
    /// Scene node class
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Node : public basic::TreeNode<Node>
    {
        COFFEE_Type(Node);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Node(basic::String name = "Node");
        virtual ~Node();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetName(const basic::String& name) { _Name = name; }
        const basic::String& GetName() const { return _Name; }
        const uint32& GetFlags() const { return _Flags; }
        bool IsRunning() const { return COFFEE_IsFlagEnabled(_Flags, FLAG_Running); }
        void SetIsAutomatic(bool it_is_automatic);
        bool IsAutomatic() const { return COFFEE_IsFlagEnabled(_Flags, FLAG_Automatic); }
        void SetIsInstantiable(bool it_is_instantiable) { COFFEE_EnableFlag(_Flags, FLAG_Instantiable, it_is_instantiable); }
        bool IsInstantiable() const { return COFFEE_IsFlagEnabled(_Flags, FLAG_Instantiable); }
        void SetIsStoppedInEditor(bool it_is_stopped_in_editor);
        bool IsStoppedInEditor() const { return COFFEE_IsFlagEnabled(_Flags, FLAG_StopInEditor); }
        uint32 GetComponentCount() const { return _Components.GetSize(); }
        const Component& GetComponent(uint32 index) const { return *_Components[index]; }
        Component& GetComponent(uint32 index) { return *_Components[index]; }
        
        bool HasTransform() const { return _Transform!=NULL; }
        const Transform& GetTransform() const { return *_Transform; }
        Transform& GetTransform() { return *_Transform; }
        bool HasBounding() const { return _Bounding!=NULL; }
        const Bounding& GetBounding() const { return *_Bounding; }
        Bounding& GetBounding() { return *_Bounding; }
        bool HasGraphics() const { return _Graphics!=NULL; }
        const graphics::Component& GetGraphics() const { return *_Graphics; }
        graphics::Component& GetGraphics() { return *_Graphics; }
        bool HasRigidBody() { return _RigidBody!=NULL; }
        const physics::RigidBody& GetRigidBody() const { return *_RigidBody; }
        physics::RigidBody& GetRigidBody() { return *_RigidBody; }
        
        //-QUERIES--------------------------------------------------------------------------------//

        plugins::ComponentWrapper* FindComponent(const basic::String& type_name)
        {
            const meta::Type* type = COFFEE_FindType(type_name);
            if (type!=NULL)
            {
                for (uint32 index=0 ; index<_Components.GetSize() ; ++index)
                {
                    if (_Components[index]->IsA<plugins::ComponentWrapper>())
                    {
                        plugins::ComponentWrapper* wrapper = static_cast<plugins::ComponentWrapper*>(
                            _Components[index]);
                        if (wrapper->IsReady() && &wrapper->GetComponent().GetMetaType()==type)
                            return wrapper;
                    }
                }
            }
            return NULL;
        }

        template<class type>
        type* FindComponent()
        {
            for (uint32 index=0 ; index<_Components.GetSize() ; ++index)
            {
                if (_Components[index]->IsKindOf<type>())
                    return static_cast<type*>(_Components[index]);
            }
            return NULL;
        }

        template<class type>
        basic::Prow<type*> FindComponents()
        {
            basic::Prow<type*> components;
            for (uint32 index=0 ; index<_Components.GetSize() ; ++index)
            {
                if (_Components[index]->IsKindOf<type>())
                    components.AddItem(static_cast<type*>(_Components[index]));
            }
            return components;
        }

        template<class type>
        type* FindComponentInChildren()
        {
            type* component = FindComponent<type>();
            if (component!=NULL)
                return component;

            for (uint32 index=0 ; index<GetChildCount() ; ++index)
            {
                type* component = GetChild(index).FindComponentInChildren<type>();
                if (component!=NULL)
                    return component;
            }
            return NULL;
        }

        Node* FindChild(const basic::String& child_name);
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void Start();
        void Stop();
        void Restart();
        
        virtual void Update(const basic::Time& time_step);
        virtual void FixedUpdate(const basic::Time& time_step);

        void Attach(Node& node, uint32 index=NONE);
        void Detach();
        bool AddComponent(Component* component);
        bool RemoveComponent(Component* component, bool destroy_component=true);
        void Destroy();

        virtual void PostSerialize(storage::MODE mode);

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnPropertyModified(const void* property);

    protected:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Name;
        basic::Prow<Component*, true> _Components;
        uint32 _Flags;

        Transform* _Transform;
        Bounding* _Bounding;
        graphics::Component* _Graphics;
        physics::RigidBody* _RigidBody;

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Update(const basic::Time& time_step, bool it_is_fixed);
        void _ValidateName(scene::Node& node);
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Node);
}
}
#endif
