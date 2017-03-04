#include "system/input/keyboard/input_keyboard.h"
#include "system/input/input.h"
#include "kernel/core/log/core_log.h"
#include "kernel/core/error/core_error.h"

namespace coffee
{
namespace input
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementModuleSingleton(Keyboard);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Keyboard::Keyboard() :
        _ItHasCharacterPressed(false),
        _ItIsReplacing(false)
    {
        COFFEE_CreateModuleSingleton(Keyboard);

        for(uint32 index=0 ; index<COFFEE_InputKeyCodeEnd ; ++index)
        {
            if(index<COFFEE_InputKeyCodeStart)
            {
                _Buttons.Add();
            }
            else
            {
                _Buttons.AddItem(COFFEE_New(Key, (KEY)index));
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    Keyboard::~Keyboard()
    {
        COFFEE_DestroyModuleSingleton(Keyboard);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Keyboard::SetCharacterPressed(char character)
    {
        _CharacterPressed = character;
        _ItHasCharacterPressed = true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Keyboard::IsReplacing() const
    {
        return _ItIsReplacing;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Keyboard::OnUpdate(const basic::Time& time_step)
    {
        if (IsJustButtonPressed(KEY_Insert))
            _ItIsReplacing = !_ItIsReplacing;

        if (_ItHasCharacterPressed)
        {
            _ItHasCharacterPressed = false;
            input::Module::Get().GetSystem().SendEvent(EVENT_CharacterKeyPressed,
                reinterpret_cast<void*>(_CharacterPressed));
        }

        Device::OnUpdate(time_step);
    }

}
}
