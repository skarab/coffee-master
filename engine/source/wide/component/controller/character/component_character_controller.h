#ifndef _COFFEE_COMPONENT_CHARACTER_CONTROLLER_H_
#define _COFFEE_COMPONENT_CHARACTER_CONTROLLER_H_

#include "coffee_includes.h"
#include "wide/component/controller/component_controller.h"

namespace coffee
{
namespace component
{
    //--------------------------------------------------------------------------------------------//
    /// Character controller
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API CharacterController : public Controller
    {
        COFFEE_Component(CharacterController, "Character", "Controller/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        CharacterController();
        ~CharacterController();

        //-HANDLERS-------------------------------------------------------------------------------//

        bool OnInputEvent(const input::EVENT& event, const void* parameters);
        void OnStart();
        void OnStop();
        void OnUpdate(const basic::Time& time_step);
    
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _MoveSpeed;
        real _RollSpeed;
        real _JumpSpeed;
        bool _KeyArray[4];
        basic::Vector2 _MouseMovement;
        bool _ItHasMovedMouse;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, CharacterController);
}
}
#endif
