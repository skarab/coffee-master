#include "system/scene/node/scene_node.h"
#include "system/graphics/component/graphics_component.h"
#include "system/physics/physics_component.h"
#include "system/physics/rigid_body/physics_rigid_body.h"
#include "wide/application/application.h"
#include "coffee.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(scene::Node);
        COFFEE_Attribute(basic::Prow< scene::Node * >, _Children, meta::MODE_Serializeable);
        COFFEE_Attribute(basic::String, _Name, meta::MODE_Serializeable | meta::MODE_Undoable);
        COFFEE_Attribute(uint32, _Flags, meta::MODE_Serializeable);
        COFFEE_AttributeCustom( < scene::Component* >, _Components, COFFEE_New(meta::ParamArray, meta::MODE_Serializeable | meta::MODE_Editable, basic::String("Name")));
    COFFEE_EndType();

namespace scene
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Node::Node(basic::String name) :
        _Name(name),
        _Flags(FLAG_Automatic|FLAG_Instantiable),
        _Transform(NULL),
        _Bounding(NULL),
        _Graphics(NULL),
        _RigidBody(NULL)        
    {
    }

    //--------------------------------------------------------------------------------------------//

    Node::~Node()
    {
        COFFEE_Assert(!IsRunning(), core::ERROR_CODE_Unexpected, "node shouldn't be running");
    }

    //-ACCESSORS----------------------------------------------------------------------------------//
    
    void Node::SetIsAutomatic(bool it_is_automatic)
    {
        COFFEE_EnableFlag(_Flags, FLAG_Automatic, it_is_automatic);
        
        if (it_is_automatic)
        {
            if (!IsRunning() && (!HasParent() || GetParent().IsRunning()))
            {
                if (!IsStoppedInEditor() || !Engine::Get().HasMode(RUN_MODE_Editor))
                    Start();
            }
        }
        else if (IsRunning())
        {
            Stop();
        }
    }
       
    //--------------------------------------------------------------------------------------------//

    void Node::SetIsStoppedInEditor(bool it_is_stopped_in_editor)
    {
        COFFEE_EnableFlag(_Flags, FLAG_StopInEditor, it_is_stopped_in_editor);
        SetIsAutomatic(IsAutomatic());

        if (IsRunning() && IsStoppedInEditor() && Engine::Get().HasMode(RUN_MODE_Editor))
            Stop();
    }
        
    //-QUERIES------------------------------------------------------------------------------------//
    
    Node* Node::FindChild(const basic::String& child_name)
    {
        for (uint32 index=0 ; index<GetChildCount() ; ++index)
        {
            if (GetChild(index).IsKindOf<Node>())
            {
                if (GetChild(index).GetName()==child_name)
                    return &GetChild(index);
            }
        }
        return NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Node::Start()
    {
        if (IsRunning())
            return;
        
        uint32 index;
        for (index=0 ; index<_Components.GetSize() ; ++index)
        {
            COFFEE_Assert(!_Components[index]->IsRunning(), core::ERROR_CODE_Unexpected, "the component should be stopped");
            if (_Components[index]->IsAutomatic() && (!_Components[index]->IsStoppedInEditor() || !Engine::Get().HasMode(RUN_MODE_Editor)))
                _Components[index]->Start();
        }
        for (index=0 ; index<GetChildCount() ; ++index)
        {
            COFFEE_Assert(!GetChild(index).IsRunning(), core::ERROR_CODE_Unexpected, "the child node should be stopped");
            if (GetChild(index).IsAutomatic() && (!GetChild(index).IsStoppedInEditor() || !Engine::Get().HasMode(RUN_MODE_Editor)))
                GetChild(index).Start();
        }
        
        COFFEE_EnableFlag(_Flags, FLAG_Running, true);        
    }

    //--------------------------------------------------------------------------------------------//

    void Node::Stop()
    {
        if (!IsRunning())
            return;
        
        uint32 index;
        for (index=0 ; index<GetChildCount() ; ++index)
        {
            if (GetChild(index).IsRunning())
                GetChild(index).Stop();
        }
        for (index=0 ; index<_Components.GetSize() ; ++index)
        {
            if (_Components[index]->IsRunning())
                _Components[index]->Stop();
        }

        COFFEE_EnableFlag(_Flags, FLAG_Running, false);
    }

    //--------------------------------------------------------------------------------------------//

    void Node::Restart()
    {
        if (IsRunning())
        {
            Stop();
            Start();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Node::Update(const basic::Time& time_step)
    {
        _Update(time_step, false);
    }

    //--------------------------------------------------------------------------------------------//

    void Node::FixedUpdate(const basic::Time& time_step)
    {
        _Update(time_step, true);
    }

    //--------------------------------------------------------------------------------------------//

    void Node::Attach(Node& node, uint32 index)
    {
        _ValidateName(node);

        COFFEE_Assert(!node.HasParent(), core::ERROR_CODE_IncorrectUsage, "the node is already parented");
        COFFEE_Assert(!node.IsRunning(), core::ERROR_CODE_Unexpected, "the node is running");

        basic::TreeNode<Node>::Attach(node, index);

        if (IsRunning() && node.IsAutomatic()
            && (!node.IsStoppedInEditor() || !Engine::Get().HasMode(RUN_MODE_Editor)))
        {
            node.Start();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Node::Detach()
    {
        if (IsRunning())
            Stop();

        basic::TreeNode<Node>::Detach();
    }

    //--------------------------------------------------------------------------------------------//

    bool Node::AddComponent(Component* component)
    {
        COFFEE_Assert(component!=NULL, core::ERROR_CODE_IncorrectUsage, "trying to add null component");
        COFFEE_Assert(!component->IsRunning(), core::ERROR_CODE_IncorrectUsage, "the component is running");
        
        if (component->IsKindOf<Transform>())
        {
            if (HasTransform()) return false;
            _Transform = static_cast<Transform*>(component);
        }
        else if (component->IsKindOf<Bounding>())
        {
            if (HasBounding()) return false;
            _Bounding = static_cast<Bounding*>(component);
        }
        else if (component->IsKindOf<graphics::Component>())
        {
            if (HasGraphics()) return false;
            _Graphics = static_cast<graphics::Component*>(component);
        }
        else if (component->IsKindOf<physics::RigidBody>())
        {
            if (HasRigidBody()) return false;
            _RigidBody = static_cast<physics::RigidBody*>(component);
        }
        
        _Components.AddItem(component);
        component->_Node = this;

        if (IsRunning() && component->IsAutomatic()
            && (!component->IsStoppedInEditor() || !Engine::Get().HasMode(RUN_MODE_Editor)))
        {
            component->Start();
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Node::RemoveComponent(Component* component, bool destroy_component)
    {
        uint32 component_index = _Components.FindItem(component);
        COFFEE_Assert(component!=NULL, core::ERROR_CODE_IncorrectUsage, "trying to add null component");
        COFFEE_Assert(component_index!=NONE, core::ERROR_CODE_IncorrectUsage, "the component doesn't belong to the node");
        
        if (component->IsRunning())
            component->Stop();

        if (component==_Transform) _Transform = NULL;
        else if (component==_Bounding) _Bounding = NULL;
        else if (component==_Graphics) _Graphics = NULL;
        else if (component==_RigidBody) _RigidBody = NULL;
        
        if (destroy_component)
        {
            _Components.Remove(component_index);
        }
        else
        {
            _Components[component_index] = NULL;
            _Components.Remove(component_index);
        }
        return true;
    }
        
    //--------------------------------------------------------------------------------------------//
    
    void Node::Destroy()
    {
        if (COFFEE_IsFlagEnabled(_Flags, FLAG_Updating))
        {
            COFFEE_EnableFlag(_Flags, FLAG_Destroyed, true);
        }
        else
        {
            basic::TreeNode<Node>::Destroy();
        }
    }

    //--------------------------------------------------------------------------------------------//
    
    void Node::PostSerialize(storage::MODE mode)
    {
        basic::TreeNode<Node>::PostSerialize(mode);
            
        if (mode==storage::MODE_Input)
        {
            COFFEE_EnableFlag(_Flags, FLAG_Updating, false);
            COFFEE_EnableFlag(_Flags, FLAG_Destroyed, false);
            COFFEE_EnableFlag(_Flags, FLAG_Running, false);
        
            for (uint32 index=0 ; index<_Components.GetSize() ; ++index)
            {
                _Components[index]->_Node = this;
                if (_Components[index]->IsKindOf<Transform>())
                    _Transform = static_cast<Transform*>(_Components[index]);
                else if (_Components[index]->IsKindOf<Bounding>())
                    _Bounding = static_cast<Bounding*>(_Components[index]);
                else if (_Components[index]->IsKindOf<graphics::Component>())
                    _Graphics = static_cast<graphics::Component*>(_Components[index]);
                else if (_Components[index]->IsKindOf<physics::RigidBody>())
                    _RigidBody = static_cast<physics::RigidBody*>(_Components[index]);
            }
        }
    }

    //-HANDLERS-------------------------------------------------------------------------------//

    void Node::OnPropertyModified(const void* prop)
    {
        if (prop==&_Flags)
            SetIsStoppedInEditor(IsStoppedInEditor());
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void Node::_Update(const basic::Time& time_step, bool it_is_fixed)
    {
        COFFEE_Assert(IsRunning(), core::ERROR_CODE_Unexpected, "the node isn't running");
        
        if (COFFEE_IsFlagEnabled(_Flags, FLAG_Destroyed))
        {
            Destroy();
            return;
        }

        COFFEE_EnableFlag(_Flags, FLAG_Updating, true);        
        uint32 index;
        for (index=0 ; index<_Components.GetSize() ; ++index)
        {
            if (_Components[index]!=_Transform && _Components[index]->IsRunning())
            {
                if (it_is_fixed) _Components[index]->OnFixedUpdate(time_step);
                else _Components[index]->OnUpdate(time_step);
            }
        }        
        
        // make sure transform is up to date before physics simulation
        if (_Transform!=NULL && _Transform->IsRunning())
        {
            if (it_is_fixed) _Transform->OnFixedUpdate(time_step);
            else _Transform->OnUpdate(time_step);
        }

        for (index=0 ; index<GetChildCount() ; ++index)
        {
            if (GetChild(index).IsRunning())
            {
                if (it_is_fixed) GetChild(index).FixedUpdate(time_step);
                else GetChild(index).Update(time_step);
            }
        }

        COFFEE_EnableFlag(_Flags, FLAG_Updating, false);
    }

    //--------------------------------------------------------------------------------------------//
    
    void Node::_ValidateName(scene::Node& node)
    {
        bool modified = true;
        uint32 id=0;
        basic::String base_name = node._Name;
        while(base_name.GetLength()>0 && base_name.GetLast()>='0' && base_name.GetLast()<='9')
            --base_name;
        if (base_name.GetLength()==0)
            base_name = "Node";

        while(modified)
        {
            modified = false;
            for (uint32 i=0 ; i<GetChildCount() ; ++i)
            {
                if (node._Name==GetChild(i)._Name && &node!=&GetChild(i))
                {
                    node._Name = base_name + basic::String("%d", id++);
                    modified = true;
                    break;
                }
            }
        }
    }

}
}
