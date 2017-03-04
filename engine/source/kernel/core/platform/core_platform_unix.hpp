#ifdef COFFEE_OS_UNIX

namespace coffee
{
namespace core
{
    //-QUERIES------------------------------------------------------------------------------------//

    real Platform::GetTime() const
    {
        return 0.0f;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Platform::_Initialize()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void Platform::_Finalize()
    {
    }

}
}
#endif
