#include "system/scene/scene_resource.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginResource(scene, Resource, "Scene", "scene", 0);
        COFFEE_Ancestor(resource::Object);
        COFFEE_ResourceProperty(scene::Node*, _Root, meta::MODE_Serializeable,
            resource::PROPERTY_FLAG_Instantiable | resource::PROPERTY_FLAG_AutoInstantiate);
    COFFEE_EndResource();

namespace scene
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Resource::Resource() :
        _Root(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Resource::~Resource()
    {
        _Destroy();
        COFFEE_Assert(_Root.GetValue()==NULL, core::ERROR_CODE_Unexpected, "Unexpected leak");
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const Node& Resource::GetRoot() const
    {
        return *_Root.Get();
    }

    //--------------------------------------------------------------------------------------------//

    Node& Resource::GetRoot()
    {
        return *_Root.Grab();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Resource::Initialize()
    {
        if (_Root.GrabValue()==NULL)
            _Root.SetValue(COFFEE_New(scene::Node, "Root"));
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Resource::Finalize()
    {
        if (_Root.GrabValue()!=NULL)
        {
            _Root.GrabValue()->Destroy();
            _Root.SetValue(NULL);
        }
        return true;
    }
    
    //--------------------------------------------------------------------------------------------//

    void Resource::ConstructInstance()
    {
        _Root.SetValue(NULL);
    }

    //--------------------------------------------------------------------------------------------//

    bool Resource::InitializeInstance()
    {
        // No need to create Root node, since its using automatic instantiation.
        return true;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Resource::FinalizeInstance()
    {
        return Finalize();
    }
       
    //--------------------------------------------------------------------------------------------//

    void Resource::PreSerialize(storage::MODE mode)
    {
        if (mode==storage::MODE_Output && IsInstantiated())
            FinalizeInstance();
        resource::Object::PreSerialize(mode);
    }

    //--------------------------------------------------------------------------------------------//

    void Resource::PostSerialize(storage::MODE mode)
    {
        if (mode==storage::MODE_Input && IsInstantiated())
        {
            //TODO: log this as error instead of crashing
            //COFFEE_Assert(_Root.GrabValue()==NULL, core::ERROR_CODE_Unexpected, "Bad scene");     
            FinalizeInstance();
        }
        resource::Object::PostSerialize(mode);
    }

    //--------------------------------------------------------------------------------------------//

    Node* Resource::FindNode(const Path& path)
    {
        Node* node = NULL;
        if (IsAvailable())
        {
            basic::Text items = path.GetNodePath().GetHierarchy();
            node = &GetRoot();
            for (uint32 i=1 ; i<items.GetLineCount() ; ++i)
            {
                node = node->FindChild(items[i]);
                if (node==NULL)
                    break;
            }
        }
        return node;
    }

    //-HANDLERS-------------------------------------------------------------------------------//

    bool Resource::OnInstantiateProperty(resource::PropertyBase& property, resource::PropertyBase& source_property, bool it_is_instantiating)
    {
        if (&property==&_Root)
        {
            Node* node = _Root.GrabValue();
            if (node!=NULL)
            {
                node->Destroy();
                _Root.SetValue(NULL);
            }

            if (it_is_instantiating)
            {
                Node* source_node = static_cast< resource::Property<Node*>& >(source_property).Grab();
                if (source_node!=NULL)
                {
                    node = static_cast<Node*>(source_node->Clone());
                    _Root.SetValue(node);
                }
            }
            return true;
        }
        return false;
    }

}
}
