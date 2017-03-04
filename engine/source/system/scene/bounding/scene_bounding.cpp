#include "system/scene/bounding/scene_bounding.h"
#include "system/scene/node/scene_node.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(scene::Bounding);
        COFFEE_Ancestor(scene::Component);
        COFFEE_Attribute(basic::Box, _Box, meta::MODE_Serializeable);
        COFFEE_Attribute(basic::Sphere, _Sphere, meta::MODE_Serializeable);
        COFFEE_Attribute(basic::Box, _LocalBox, meta::MODE_Serializeable);
    COFFEE_EndType();

namespace scene
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Bounding::Bounding() :
        _ItIsUpToDate(true)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Bounding::~Bounding()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Bounding::SetLocalBox(const basic::Box& box)
    {
        if (box!=_LocalBox)
        {
            _LocalBox = box;
            _ItIsUpToDate = false;
        }
    }

    //-QUERIES--------------------------------------------------------------------------------//

    bool Bounding::IsVisible(graphics::Viewport& viewport) const
    {
        // TODO
        return true;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void Bounding::OnStart()
    {
        _ItIsUpToDate = false;
    }

    //--------------------------------------------------------------------------------------------//

    void Bounding::OnStop()
    {
        if (GetNode().HasParent() && GetNode().GetParent().HasBounding())
            GetNode().GetParent().GetBounding()._ItIsUpToDate = false;
    }

    //--------------------------------------------------------------------------------------------//

    void Bounding::OnFixedUpdate(const basic::Time& time_step)
    {
        if (!_ItIsUpToDate)
        {
            bool it_is_ok(true);
            basic::Box box(_LocalBox);
            for (uint32 index=0 ; index<GetNode().GetChildCount() ; ++index)
            {
                Node& child = GetNode().GetChild(index);
                if (child.IsRunning() && child.HasTransform() && child.HasBounding())
                {
                    if (!child.GetTransform().IsUpToDate()
                        || !child.GetBounding()._ItIsUpToDate)
                    {
                        it_is_ok = false;
                    }

                    if (!child.GetBounding()._Box.IsEmpty())
                    {
                        box.AddBox(child.GetBounding()._Box
                            * child.GetTransform().GetMatrix(TRS_Local, TRS_Parent));
                    }
                }
            }
            _Box = box;            
            _Sphere.AddBox(_Box, true);
            _ItIsUpToDate = it_is_ok;

            if (GetNode().HasParent() && GetNode().GetParent().HasBounding())
                GetNode().GetParent().GetBounding()._ItIsUpToDate = false;
        }
    }

    //--------------------------------------------------------------------------------------------//
    
    void Bounding::OnTransform()
    {
        _ItIsUpToDate = false;
    }
    
    //--------------------------------------------------------------------------------------------//

    void Bounding::OnPropertyModified(const void* prop)
    {
        if (prop==&_LocalBox)
            _ItIsUpToDate = false;
    }

}
}
