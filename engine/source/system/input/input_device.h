#ifndef _COFFEE_INPUT_DEVICE_H_
#define _COFFEE_INPUT_DEVICE_H_

#include "coffee_includes.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/shell/module/shell_module.h"
#include "system/input/input_device_button.h"

namespace coffee
{
namespace input
{
    //--------------------------------------------------------------------------------------------//
    /// @class Device
    /// @brief Input device
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Device : public shell::Module
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Device();
        virtual ~Device();

        //-QUERIES--------------------------------------------------------------------------------//

        real GetButtonPressure(uint32 button);
        bool IsButtonPressed(uint32 button) const;
        bool WasButtonPressed(uint32 button) const;
        bool IsJustButtonPressed(uint32 button) const;
        bool IsJustButtonReleased(uint32 button) const;
        bool IsRepeatButtonPressed(uint32 button) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void OnUpdate(const basic::Time& time_step);

    protected:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<DeviceButton*, true> _Buttons;
    };
}
}
#endif
