#ifndef _COFFEE_SYSTEM_INPUT_EVENT_H_
#define _COFFEE_SYSTEM_INPUT_EVENT_H_

#include "coffee_includes.h"
#include "system/input/keyboard/input_key_code.h"

namespace coffee
{
namespace input
{
    //--------------------------------------------------------------------------------------------//
    /// Input events
    //--------------------------------------------------------------------------------------------//
    enum EVENT
    {
        EVENT_KeyPressed,                   //< parameter: EventKey
        EVENT_KeyReleased,                  //< parameter: EventKey
        EVENT_CharacterKeyPressed,          //< parameter: char
        EVENT_MouseMove,                    //< parameter: EventMouse
        EVENT_MouseDoubleClick,             //< parameter: EventMouse
        EVENT_MouseLeftButtonPressed,       //< parameter: EventMouse
        EVENT_MouseLeftButtonReleased,      //< parameter: EventMouse
        EVENT_MouseRightButtonPressed,      //< parameter: EventMouse
        EVENT_MouseRightButtonReleased,     //< parameter: EventMouse
        EVENT_MouseMiddleButtonPressed,     //< parameter: EventMouse
        EVENT_MouseMiddleButtonReleased,    //< parameter: EventMouse
        EVENT_Command                       //< parameter: Command (pointer on the registered command)
    };

    //--------------------------------------------------------------------------------------------//
    /// Key event parameter
    //--------------------------------------------------------------------------------------------//
    class EventKey : public meta::Object
    {
    public:
        EventKey(KEY key, bool it_is_repeating):
            Key(key), ItIsRepeating(it_is_repeating) {}
        KEY Key;
        bool ItIsRepeating;
    };

    //--------------------------------------------------------------------------------------------//
    /// Mouse event parameter
    //--------------------------------------------------------------------------------------------//
    class EventMouse : public meta::Object
    {
    public:
        EventMouse(const basic::Vector2i& position): Position(position) {}
        basic::Vector2i Position;
    };

}
}
#endif
