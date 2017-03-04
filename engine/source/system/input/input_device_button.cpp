//------------------------------------------------------------------------------------------------//
/// @file system/input/input_device_button.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "system/input/input_device_button.h"
//------------------------------------------------------------------------------------------------//

//-CONSTANTS--------------------------------------------------------------------------------------//
#define COFFEE_InputDeviceButtonRepeatThreshold  1.0f
#define COFFEE_InputDeviceButtonRepeatTime  0.07f
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace input
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    DeviceButton::DeviceButton() :
        _ItIsPressed(false),
        _ItWasPressed(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    DeviceButton::~DeviceButton()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    real DeviceButton::GetPressure() const
    {
        return (real) _ItIsPressed;
    }

    //--------------------------------------------------------------------------------------------//

    bool DeviceButton::IsPressed() const
    {
        return _ItIsPressed;
    }

    //--------------------------------------------------------------------------------------------//

    bool DeviceButton::WasPressed() const
    {
        return _ItWasPressed;
    }

    //--------------------------------------------------------------------------------------------//

    bool DeviceButton::IsJustPressed() const
    {
        return _ItIsPressed && !_ItWasPressed;
    }

    //--------------------------------------------------------------------------------------------//

    bool DeviceButton::IsJustReleased() const
    {
        return !_ItIsPressed && _ItWasPressed;
    }

    //--------------------------------------------------------------------------------------------//

    bool DeviceButton::IsRepeatPressed() const
    {
        return _ItIsPressed
                && (_PressTime.GetSecondCount()==0.0f
                    || _PressTime.GetSecondCount()==COFFEE_InputDeviceButtonRepeatThreshold);
    }

    //--------------------------------------------------------------------------------------------//

    bool DeviceButton::IsRepeating() const
    {
        return _ItIsPressed && (_PressTime.GetSecondCount()==COFFEE_InputDeviceButtonRepeatThreshold);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void DeviceButton::Update(const basic::Time& time_step)
    {
        if (_ItIsPressed)
        {
            if (!_ItWasPressed)
            {
                _PressTime = 0.0f;
            }
            else
            {
                if(_PressTime.GetSecondCount()<=COFFEE_InputDeviceButtonRepeatThreshold)
                {
                    _PressTime += time_step;

                    if (_PressTime.GetSecondCount()>=COFFEE_InputDeviceButtonRepeatThreshold)
                        _PressTime = COFFEE_InputDeviceButtonRepeatThreshold;
                }
                else if(_PressTime.GetSecondCount()>=COFFEE_InputDeviceButtonRepeatTime)
                {
                    _PressTime.SetSecondCount(COFFEE_InputDeviceButtonRepeatThreshold);
                }
            }
        }
    }

}
}
//------------------------------------------------------------------------------------------------//
