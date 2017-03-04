#ifdef COFFEE_OS_UNIX

namespace coffee
{
namespace input
{
    //-OPERATIONS---------------------------------------------------------------------------------//

    void Key::_PlatformUpdate()
    {
        _ItWasPressed = _ItIsPressed;
        _ItIsPressed = false;
    }

}
}
#endif
