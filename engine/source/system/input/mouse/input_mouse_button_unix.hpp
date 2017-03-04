#ifdef COFFEE_OS_UNIX

namespace coffee
{
namespace input
{
    //-OPERATIONS---------------------------------------------------------------------------------//

    void MouseButton::Update()
    {
        _ItWasPressed = _ItIsPressed;
        _ItIsPressed = false;
    }

}
}
#endif
