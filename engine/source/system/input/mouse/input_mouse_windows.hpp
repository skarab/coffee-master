#ifdef COFFEE_OS_WINDOWS

#include "system/graphics/graphics.h"
#include "coffee.h"

namespace coffee
{
namespace input
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    void MOUSE_SetCursorPosition(int32 position_x, int32 position_y)
    {
        POINT cursor_position;
        
        cursor_position.x = position_x;
        cursor_position.y = position_y;
        
        if (graphics::Device::IsInstantiated())
        {
            ClientToScreen(graphics::Device::Get().GetPlatformWindow(), &cursor_position);
            SetCursorPos(cursor_position.x, cursor_position.y);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void MOUSE_GetCursorPosition(int32 & position_x, int32 & position_y)
    {
        if (graphics::Device::IsInstantiated())
        {
            POINT cursor_position;
            
            GetCursorPos(&cursor_position);
            ScreenToClient(graphics::Device::Get().GetPlatformWindow(), &cursor_position);
            
            position_x = cursor_position.x;
            position_y = cursor_position.y;
        }
        else
        {
            position_x = 0;
            position_y = 0;
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Mouse::ShowMouseCursor(bool it_has_to_show)
    {
        if (graphics::Device::IsInstantiated())
        {
            int32 x, y;
            MOUSE_GetCursorPosition(x, y);
            if (x<0 || y<0 || x>(int32)graphics::Device::Get().GetWidth()
                || y>(int32)graphics::Device::Get().GetHeight())
            {
                it_has_to_show = true;
            }
        }

        if(it_has_to_show == _ItHasCursorVisible)
            return;

        if(it_has_to_show)
        {
            while(ShowCursor(TRUE) < 0) {};
        }
        else
        {
            while(ShowCursor(FALSE) >= 0) {};
        }

        _ItHasCursorVisible = it_has_to_show;
    }

    //--------------------------------------------------------------------------------------------//

    void Mouse::BeginCapture()
    {
        if(!_ItIsCapturing)
        {
            _ItIsCapturing = true;
            ShowMouseCursor(false);
            _StoredPosition = _Position;
            _CenterMouse();
            _MovementVector = 0.0f;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Mouse::EndCapture()
    {
        if(_ItIsCapturing)
        {
            _ItIsCapturing = false;
            ShowMouseCursor(true);
            SetPosition(_StoredPosition);
            _MovementVector = 0.0f;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Mouse::SetPosition(const basic::Vector2& position)
    {
        _Position = position;

        MOUSE_SetCursorPosition((int32) _Position.X, (int32) _Position.Y);
    }

    //--------------------------------------------------------------------------------------------//

    void Mouse::OnInitialize()
    {
        SetIsSwapped(GetSystemMetrics(SM_SWAPBUTTON) == TRUE);
    }

    //--------------------------------------------------------------------------------------------//

    void Mouse::OnUpdate(const basic::Time& time_step)
    {
        int32 position_x, position_y;
        basic::Vector2 new_position;

        if (Application::IsInstantiated()
            && Application::Get().HasFocus())
        {
            MOUSE_GetCursorPosition(position_x, position_y);
            new_position.Set((real) position_x, (real) position_y);

            if (IsCapturing())
            {
                _MovementVector = new_position - _Position;
                _MovementVector.Y = -_MovementVector.Y;
                _CenterMouse();
            }
            else
            {
                _Position = new_position;
            }
        }

        Device::OnUpdate(time_step);
        _ScrollValue = 0;
    }

    //--------------------------------------------------------------------------------------------//

    void Mouse::OnScroll(int32 scroll)
    {
        _ScrollValue = scroll;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Mouse::_CenterMouse()
    {
        if (graphics::Device::IsInstantiated())
        {
            SetPosition(basic::Vector2(
                graphics::Device::Get().GetWidth()/2.0f,
                graphics::Device::Get().GetHeight()/2.0f));
        }
    }

}
}
#endif
