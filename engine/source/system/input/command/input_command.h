#ifndef _COFFEE_INPUT_COMMAND_H_
#define _COFFEE_INPUT_COMMAND_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"
#include "system/input/keyboard/input_key_code.h"
#include "system/input/mouse/input_mouse_button_code.h"

namespace coffee
{
namespace input
{
    //--------------------------------------------------------------------------------------------//
    /// Input command
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Command : public meta::Object
    {
        COFFEE_Type(Command);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Command();
        Command(const Command& command);
        Command(basic::String name, basic::String description="",
            KEY first_key=KEY_None, KEY second_key=KEY_None,
            KEY third_key=KEY_None, BUTTON mouse_button=BUTTON_None);
        ~Command();

        //-OPERATORS------------------------------------------------------------------------------//

        Command& operator=(const Command& command);

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetName(basic::String name);
        const basic::String& GetName() const;
        void SetDescription(basic::String description);
        const basic::String& GetDescription() const;
        KEY GetFirstKey() const;
        KEY GetSecondKey() const;
        KEY GetThirdKey() const;
        BUTTON GetMouse() const;

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 GetControlCount() const;
        basic::String GetControlString() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Update();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Name;
        basic::String _Description;
        KEY _FirstKey;
        KEY _SecondKey;
        KEY _ThirdKey;
        BUTTON _Mouse;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Command);
}
}
#endif
