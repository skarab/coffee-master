#ifndef _COFFEE_INPUT_KEY_H_
#define _COFFEE_INPUT_KEY_H_

#include "coffee_includes.h"
#include "system/input/input_device_button.h"
#include "system/input/keyboard/input_key_code.h"

namespace coffee
{
namespace input
{
    //--------------------------------------------------------------------------------------------//
    /// Key
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Key : public DeviceButton
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Key(const KEY& code);
        ~Key();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Update(const basic::Time& time_step);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _PlatformUpdate();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        KEY _Code;
    };
}
}
#endif
