#include "builder.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_RegisterApplication(
    builder::Application,
    RUN_MODE_MemoryReport
   );

namespace builder
{
    //-META---------------------------------------------------------------------------------------//
    
    COFFEE_ImplementSingleton(Application);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Application::Application() :
        _Widget(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Application::~Application()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Application::OnInitialize()
    {
        coffee::Application::OnInitialize();
        graphics::Device::Get().PositionWindowToCenter(640, 440);

        _Widget = COFFEE_New(Widget);
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnFinalize()
    {
        coffee::Application::OnFinalize();
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnUpdate(const basic::Time& time_step)
    {
        coffee::Application::OnUpdate(time_step);
    }


}
