#ifndef _COFFEE_COMPONENT_FREE_CONTROLLER_H_
#define _COFFEE_COMPONENT_FREE_CONTROLLER_H_

#include "coffee_includes.h"
#include "wide/component/controller/component_controller.h"

namespace coffee
{
namespace component
{
    //--------------------------------------------------------------------------------------------//
    /// Free controller
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FreeController : public Controller
    {
        COFFEE_Component(FreeController, "Free", "Controller/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FreeController();
        ~FreeController();

        //-HANDLERS-------------------------------------------------------------------------------//

        bool OnInputEvent(const input::EVENT& event, const void* parameters);
        void OnStart();
        void OnStop();
        void OnUpdate(const basic::Time& time_step);
        void OnFixedUpdate(const basic::Time& time_step);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        basic::Vector3 _ComputeMove(real distance);
        basic::Vector3 _ComputeStrafe(real distance);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _MoveSpeed;
        real _RollSpeed;
        bool _ItHasToFixVelocity;
        bool _KeyArray[4];
        basic::Vector2 _MouseMovement;
        bool _ItHasMovedMouse;
        basic::Vector3 _Force;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FreeController);
}
}
#endif
