#ifndef _COFFEE_INPUT_KEYBOARD_H_
#define _COFFEE_INPUT_KEYBOARD_H_

#include "coffee_includes.h"
#include "system/input/input_device.h"
#include "system/input/keyboard/input_key.h"
#include "system/input/keyboard/input_key_code.h"

namespace coffee
{
namespace input
{
    //--------------------------------------------------------------------------------------------//
    /// Keyboard device
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Keyboard : public Device
    {
        COFFEE_DeclareModuleSingleton(Keyboard);

     public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Keyboard();
        ~Keyboard();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetCharacterPressed(char character);
        bool IsReplacing() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void OnUpdate(const basic::Time& time_step);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItHasCharacterPressed;
        char _CharacterPressed;
        bool _ItIsReplacing;
    };
}
}
#endif
