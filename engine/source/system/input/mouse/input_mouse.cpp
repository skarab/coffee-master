#include "kernel/core/log/core_log.h"
#include "kernel/core/error/core_error.h"
#include "system/input/mouse/input_mouse.h"
#include "system/input/mouse/input_mouse_windows.hpp"
#include "system/input/mouse/input_mouse_unix.hpp"

namespace coffee
{
namespace input
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementModuleSingleton(Mouse);

    //--------------------------------------------------------------------------------------------//

    Mouse::Mouse() :
        _Speed(1.0f),
        _ItIsCapturing(false),
        _ScrollValue(0),
        _ItHasCursorVisible(true),
        _ItIsSwapped(false)
    {
        COFFEE_CreateModuleSingleton(Mouse);

        for(uint32 index=0 ; index<COFFEE_InputMouseButtonCodeEnd ; ++index)
        {
            if(index<COFFEE_InputMouseButtonCodeStart)
            {
                _Buttons.Add();
            }
            else
            {
                _Buttons.AddItem(COFFEE_New(MouseButton, (BUTTON) index));
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    Mouse::~Mouse()
    {
        COFFEE_DestroyModuleSingleton(Mouse);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Mouse::SetSpeed(real speed)
    {
        _Speed = speed;
    }

    //--------------------------------------------------------------------------------------------//

    real Mouse::GetSpeed() const
    {
        return _Speed;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Vector2& Mouse::GetPosition() const
    {
        return _Position;
    }

    //--------------------------------------------------------------------------------------------//

    int32 Mouse::GetScrollValue() const
    {
        return _ScrollValue;
    }

    //--------------------------------------------------------------------------------------------//

    bool Mouse::IsCapturing() const
    {
        return _ItIsCapturing;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Vector2& Mouse::GetMovementVector() const
    {
        return _MovementVector;
    }

    //--------------------------------------------------------------------------------------------//

    bool Mouse::IsCursorVisible() const
    {
        return _ItHasCursorVisible;
    }

    //--------------------------------------------------------------------------------------------//

    void Mouse::SetIsSwapped(bool it_is_swapped)
    {
        _ItIsSwapped = it_is_swapped;
    }

    //--------------------------------------------------------------------------------------------//

    bool Mouse::IsSwapped() const
    {
        return _ItIsSwapped;
    }

}
}
