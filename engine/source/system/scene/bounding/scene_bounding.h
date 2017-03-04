#ifndef _COFFEE_SCENE_BOUNDING_H_
#define _COFFEE_SCENE_BOUNDING_H_

#include "coffee_includes.h"
#include "system/scene/component/scene_component.h"

namespace coffee
{
namespace graphics
{
    //-FORWARDS-----------------------------------------------------------------------------------//
    class Viewport;
}

namespace scene
{
    //--------------------------------------------------------------------------------------------//
    /// Component holding the node bounding box & sphere
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Bounding : public scene::Component
    {
        COFFEE_Component(Bounding, "Bounding", "Scene/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Bounding();
        ~Bounding();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::Box& GetBox() const { return _Box; }
        const basic::Sphere& GetSphere() const { return _Sphere; }
        void SetLocalBox(const basic::Box& box);
        const basic::Box& GetLocalBox() const { return _LocalBox; }
        
        //-QUERIES--------------------------------------------------------------------------------//

        bool IsVisible(graphics::Viewport& viewport) const;
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnStart();
        void OnStop();
        void OnFixedUpdate(const basic::Time& time_step);
        void OnTransform();
        void OnPropertyModified(const void* prop);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Box _Box;
        basic::Sphere _Sphere;
        basic::Box _LocalBox;
        bool _ItIsUpToDate;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Bounding);
}
}
#endif
