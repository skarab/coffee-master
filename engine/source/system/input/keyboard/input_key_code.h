#ifndef _COFFEE_INPUT_KEY_CODES_H_
#define _COFFEE_INPUT_KEY_CODES_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

//-CONSTANTS--------------------------------------------------------------------------------------//
#ifndef COFFEE_InputKeyCodeStart
    #define COFFEE_InputKeyCodeStart     0x08
    #define COFFEE_InputKeyCodeEnd       0xDF
    #define COFFEE_InputKeyNumberStart   0x30
    #define COFFEE_InputKeyNumberEnd     0x3A
    #define COFFEE_InputKeyNumpadStart   0x60
    #define COFFEE_InputKeyNumpadEnd     0x6A
    #define COFFEE_InputKeyAlphaStart    0x41
    #define COFFEE_InputKeyAlphaEnd      0x5B
#endif
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace input
{
    //----------------------------------------------------------------------------------------//
    /// Keyboard key codes
    ///
    /// Key codes used by the input handler for notifications.
    //----------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::input, KEY, "Key", SingleNone)
    COFFEE_EnumValue(KEY, Back         , 0x08)
    COFFEE_EnumValue(KEY, Tab          , 0x09)
    COFFEE_EnumValue(KEY, Clear        , 0x0C)
    COFFEE_EnumValue(KEY, Return       , 0x0D)
    COFFEE_EnumValue(KEY, Shift        , 0x10)
    COFFEE_EnumValue(KEY, Control      , 0x11)
    COFFEE_EnumValue(KEY, Menu         , 0x12)
    COFFEE_EnumValue(KEY, Pause        , 0x13)
    COFFEE_EnumValue(KEY, Capital      , 0x14)
    COFFEE_EnumValue(KEY, Kana         , 0x15)
    COFFEE_EnumValue(KEY, Junja        , 0x17)
    COFFEE_EnumValue(KEY, Final        , 0x18)
    COFFEE_EnumValue(KEY, Hanja        , 0x19)
    COFFEE_EnumValue(KEY, Kanji        , 0x19)
    COFFEE_EnumValue(KEY, Escape       , 0x1B)
    COFFEE_EnumValue(KEY, Convert      , 0x1C)
    COFFEE_EnumValue(KEY, NonConvert   , 0x1D)
    COFFEE_EnumValue(KEY, Accept       , 0x1E)
    COFFEE_EnumValue(KEY, ModeChange   , 0x1F)
    COFFEE_EnumValue(KEY, Space        , 0x20)
    COFFEE_EnumValue(KEY, Prior        , 0x21)
    COFFEE_EnumValue(KEY, Next         , 0x22)
    COFFEE_EnumValue(KEY, End          , 0x23)
    COFFEE_EnumValue(KEY, Home         , 0x24)
    COFFEE_EnumValue(KEY, Left         , 0x25)
    COFFEE_EnumValue(KEY, Up           , 0x26)
    COFFEE_EnumValue(KEY, Right        , 0x27)
    COFFEE_EnumValue(KEY, Down         , 0x28)
    COFFEE_EnumValue(KEY, Select       , 0x29)
    COFFEE_EnumValue(KEY, Print        , 0x2A)
    COFFEE_EnumValue(KEY, Execute      , 0x2B)
    COFFEE_EnumValue(KEY, SnapShot     , 0x2C)
    COFFEE_EnumValue(KEY, Insert       , 0x2D)
    COFFEE_EnumValue(KEY, Delete       , 0x2E)
    COFFEE_EnumValue(KEY, Help         , 0x2F)

    COFFEE_EnumValue(KEY, Zero         , 0x30)
    COFFEE_EnumValue(KEY, One          , 0x31)
    COFFEE_EnumValue(KEY, Two          , 0x32)
    COFFEE_EnumValue(KEY, Three        , 0x33)
    COFFEE_EnumValue(KEY, Four         , 0x34)
    COFFEE_EnumValue(KEY, Five         , 0x35)
    COFFEE_EnumValue(KEY, Six          , 0x36)
    COFFEE_EnumValue(KEY, Seven        , 0x37)
    COFFEE_EnumValue(KEY, Eight        , 0x38)
    COFFEE_EnumValue(KEY, Nine            , 0x39)

    COFFEE_EnumValue(KEY, A            , 0x41)
    COFFEE_EnumValue(KEY, B            , 0x42)
    COFFEE_EnumValue(KEY, C            , 0x43)
    COFFEE_EnumValue(KEY, D            , 0x44)
    COFFEE_EnumValue(KEY, E            , 0x45)
    COFFEE_EnumValue(KEY, F            , 0x46)
    COFFEE_EnumValue(KEY, G            , 0x47)
    COFFEE_EnumValue(KEY, H            , 0x48)
    COFFEE_EnumValue(KEY, I            , 0x49)
    COFFEE_EnumValue(KEY, J            , 0x4A)
    COFFEE_EnumValue(KEY, K            , 0x4B)
    COFFEE_EnumValue(KEY, L            , 0x4C)
    COFFEE_EnumValue(KEY, M            , 0x4D)
    COFFEE_EnumValue(KEY, N            , 0x4E)
    COFFEE_EnumValue(KEY, O            , 0x4F)
    COFFEE_EnumValue(KEY, P            , 0x50)
    COFFEE_EnumValue(KEY, Q            , 0x51)
    COFFEE_EnumValue(KEY, R            , 0x52)
    COFFEE_EnumValue(KEY, S            , 0x53)
    COFFEE_EnumValue(KEY, T            , 0x54)
    COFFEE_EnumValue(KEY, U            , 0x55)
    COFFEE_EnumValue(KEY, V            , 0x56)
    COFFEE_EnumValue(KEY, W            , 0x57)
    COFFEE_EnumValue(KEY, X            , 0x58)
    COFFEE_EnumValue(KEY, Y            , 0x59)
    COFFEE_EnumValue(KEY, Z            , 0x5A)

    COFFEE_EnumValue(KEY, LeftWin      , 0x5B)
    COFFEE_EnumValue(KEY, RightWin     , 0x5C)
    COFFEE_EnumValue(KEY, Apps         , 0x5D)

    COFFEE_EnumValue(KEY, NumPad0      , 0x60)
    COFFEE_EnumValue(KEY, NumPad1      , 0x61)
    COFFEE_EnumValue(KEY, NumPad2      , 0x62)
    COFFEE_EnumValue(KEY, NumPad3      , 0x63)
    COFFEE_EnumValue(KEY, NumPad4      , 0x64)
    COFFEE_EnumValue(KEY, NumPad5      , 0x65)
    COFFEE_EnumValue(KEY, NumPad6      , 0x66)
    COFFEE_EnumValue(KEY, NumPad7      , 0x67)
    COFFEE_EnumValue(KEY, NumPad8      , 0x68)
    COFFEE_EnumValue(KEY, NumPad9      , 0x69)

    COFFEE_EnumValue(KEY, Multiply     , 0x6A)
    COFFEE_EnumValue(KEY, Add          , 0x6B)
    COFFEE_EnumValue(KEY, Separator    , 0x6C)
    COFFEE_EnumValue(KEY, Subtract     , 0x6D)
    COFFEE_EnumValue(KEY, Decimal      , 0x6E)
    COFFEE_EnumValue(KEY, Divide       , 0x6F)
    COFFEE_EnumValue(KEY, F1           , 0x70)
    COFFEE_EnumValue(KEY, F2           , 0x71)
    COFFEE_EnumValue(KEY, F3           , 0x72)
    COFFEE_EnumValue(KEY, F4           , 0x73)
    COFFEE_EnumValue(KEY, F5           , 0x74)
    COFFEE_EnumValue(KEY, F6           , 0x75)
    COFFEE_EnumValue(KEY, F7           , 0x76)
    COFFEE_EnumValue(KEY, F8           , 0x77)
    COFFEE_EnumValue(KEY, F9           , 0x78)
    COFFEE_EnumValue(KEY, F10          , 0x79)
    COFFEE_EnumValue(KEY, F11          , 0x7A)
    COFFEE_EnumValue(KEY, F12          , 0x7B)
    COFFEE_EnumValue(KEY, F13          , 0x7C)
    COFFEE_EnumValue(KEY, F14          , 0x7D)
    COFFEE_EnumValue(KEY, F15          , 0x7E)
    COFFEE_EnumValue(KEY, F16          , 0x7F)
    COFFEE_EnumValue(KEY, F17          , 0x80)
    COFFEE_EnumValue(KEY, F18          , 0x81)
    COFFEE_EnumValue(KEY, F19          , 0x82)
    COFFEE_EnumValue(KEY, F20          , 0x83)
    COFFEE_EnumValue(KEY, F21          , 0x84)
    COFFEE_EnumValue(KEY, F22          , 0x85)
    COFFEE_EnumValue(KEY, F23          , 0x86)
    COFFEE_EnumValue(KEY, F24          , 0x87)

    COFFEE_EnumValue(KEY, NumLock      , 0x90)
    COFFEE_EnumValue(KEY, Scroll       , 0x91)
    COFFEE_EnumValue(KEY, LeftShift    , 0xA0)
    COFFEE_EnumValue(KEY, RightShift   , 0xA1)
    COFFEE_EnumValue(KEY, LeftControl  , 0xA2)
    COFFEE_EnumValue(KEY, RightControl , 0xA3)
    COFFEE_EnumValue(KEY, LeftMenu     , 0xA4)
    COFFEE_EnumValue(KEY, RightMenu    , 0xA5)

    COFFEE_EnumValue(KEY, MinTwo       , 0xDE)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, KEY)
}
}
#endif
