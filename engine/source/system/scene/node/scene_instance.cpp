#include "system/scene/node/scene_instance.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(scene::Instance);
        COFFEE_Ancestor(scene::Node);
        COFFEE_Attribute(scene::Resource, _Source, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndResource();

namespace scene
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Instance::Instance() :
        Node("Instance"),
        _Handler(&_Source)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Instance::Instance(const storage::Path& resource_path) :
        Node("Instance"),
        _Handler(&_Source)
    {
        _Source = resource::Manager::Get().Load(resource_path);
    }

    //--------------------------------------------------------------------------------------------//

    Instance::~Instance()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Instance::Destroy()
    {
        if (_Source._Root.GrabValue()!=NULL)
        {
            if (!_Source.GetRoot().HasParent())
                _Source.GetRoot().Destroy();
            _Source._Root.SetValue(NULL);
        }
        Node::Destroy();
    }

    //--------------------------------------------------------------------------------------------//

    void Instance::FixedUpdate(const basic::Time& time_step)
    {
        switch(_Handler.Update())
        {
            case resource::HANDLER_STATE_EndLoading: 
            {
                _StripNotInstantiables(_Source.GetRoot());
                Attach(_Source.GetRoot());
            } break;

            default:
                break;
        }

        Node::FixedUpdate(time_step);
    }

    //--------------------------------------------------------------------------------------------//

    void Instance::PreSerialize(storage::MODE mode)
    {
        if (mode==storage::MODE_Output)
        {
            _Temp = NULL;
            if (_Source.IsAvailable())
            {
                _Temp = &_Source.GetRoot();
                _Source.GetRoot().Detach();
                _Source._Root.SetValue(NULL);
            }
            else
            {
                COFFEE_Assert(_Source._Root.GetValue()==NULL, core::ERROR_CODE_Unexpected, "fix this if it happens");
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Instance::PostSerialize(storage::MODE mode)
    {
        Node::PostSerialize(mode);

        if (mode==storage::MODE_Output)
        {
            if (_Temp!=NULL)
            {
                COFFEE_Assert(_Source.IsAvailable(), core::ERROR_CODE_Unexpected, "fix this if it happens");
                COFFEE_Assert(_Source._Root.GrabValue()==NULL, core::ERROR_CODE_Unexpected, "fix this if it happens");
                _Source._Root.SetValue(_Temp);
                Attach(_Source.GetRoot());
            }
        }
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void Instance::_StripNotInstantiables(Node& node)
    {
        int32 index;
        for (index=(int32)node.GetComponentCount()-1 ; index>=0 ; --index)
        {
            if (!node.GetComponent(index).IsInstantiable())
                node.RemoveComponent(&node.GetComponent(index));
        }
        for (index=(int32)node.GetChildCount()-1 ; index>=0 ; --index)
        {
            Node& child = node.GetChild(index);
            if (child.IsInstantiable())
            {
                _StripNotInstantiables(child);
            }
            else
            {
                child.Destroy();
            }
        }
    }

}
}
