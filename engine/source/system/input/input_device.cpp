//------------------------------------------------------------------------------------------------//
/// @file system/input/input_device.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "system/input/input_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace input
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Device::Device()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Device::~Device()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    real Device::GetButtonPressure(uint32 button)
    {
        if(_Buttons[button] == NULL)
            return false;

        return _Buttons[button]->GetPressure();
    }

    //--------------------------------------------------------------------------------------------//

    bool Device::IsButtonPressed(uint32 button) const
    {
        if(_Buttons[button]==NULL)
            return false;

        return _Buttons[button]->IsPressed();
    }

    //--------------------------------------------------------------------------------------------//

    bool Device::WasButtonPressed(uint32 button) const
    {
        if(_Buttons[button]==NULL)
            return false;

        return _Buttons[button]->WasPressed();
    }

    //--------------------------------------------------------------------------------------------//

    bool Device::IsJustButtonPressed(uint32 button) const
    {
        if(_Buttons[button]==NULL)
            return false;

        return _Buttons[button]->IsJustPressed();
    }

    //--------------------------------------------------------------------------------------------//

    bool Device::IsJustButtonReleased(uint32 button) const
    {
        if(_Buttons[button] == NULL)
            return false;

        return _Buttons[button]->IsJustReleased();
    }

    //--------------------------------------------------------------------------------------------//

    bool Device::IsRepeatButtonPressed(uint32 button) const
    {
        if(_Buttons[button] == NULL)
            return false;

        return _Buttons[button]->IsRepeatPressed();
    }

    //--------------------------------------------------------------------------------------------//

    void Device::OnUpdate(const basic::Time& time_step)
    {
        for(uint32 index=0 ; index<_Buttons.GetSize() ; ++index)
        {
            if(_Buttons[index]!=NULL)
                _Buttons[index]->Update(time_step);
        }
    }

}
}
//------------------------------------------------------------------------------------------------//
