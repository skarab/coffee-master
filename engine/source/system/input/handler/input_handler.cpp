#include "system/input/handler/input_handler.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(input::Handler);
        COFFEE_Ancestor(shell::EventHandler)
    COFFEE_EndType();

namespace input
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Handler::Handler()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Handler::~Handler()
    {
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    void Handler::OnDestroyEvent(shell::Event& event)
    {
        ForwardDestroyEvent(event);
    }

    //--------------------------------------------------------------------------------------------//

    void Handler::ForwardDestroyEvent(shell::Event& event)
    {
        if (&event.GetCode().GetType()==&GetClassMetaType())
        {
            EventKey* key_parameter;
            EventMouse* mouse_parameter;

            switch((EVENT)event.GetCode().GetIdentifier())
            {
                case EVENT_KeyPressed:
                case EVENT_KeyReleased:
                    key_parameter = (EventKey*)event.GetParameters().GetCustomParameter();
                    COFFEE_Delete(key_parameter);
                    break;
                case EVENT_MouseMove:
                case EVENT_MouseDoubleClick:
                case EVENT_MouseLeftButtonPressed:
                case EVENT_MouseLeftButtonReleased:
                case EVENT_MouseRightButtonPressed:
                case EVENT_MouseRightButtonReleased:
                case EVENT_MouseMiddleButtonPressed:
                case EVENT_MouseMiddleButtonReleased:
                    mouse_parameter = (EventMouse*)event.GetParameters().GetCustomParameter();
                    COFFEE_Delete(mouse_parameter);
                    break;
                default:
                    break;
            }
        }
    }

}
}
