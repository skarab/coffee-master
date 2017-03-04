#ifndef _COFFEE_INPUT_MOUSE_H_
#define _COFFEE_INPUT_MOUSE_H_

#include "coffee_includes.h"
#include "system/input/input_device.h"
#include "system/input/mouse/input_mouse_button.h"
#include "system/input/mouse/input_mouse_button_code.h"
#include "kernel/basic/math/basic_math.h"

namespace coffee
{
namespace input
{
    //--------------------------------------------------------------------------------------------//
    /// Mouse device
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Mouse : public Device
    {
        COFFEE_DeclareModuleSingleton(Mouse);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Mouse();
        ~Mouse();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetSpeed(real speed);
        real GetSpeed() const;
        void SetPosition(const basic::Vector2& position);
        const basic::Vector2& GetPosition() const;
        int32 GetScrollValue() const;
        bool IsCapturing() const;
        const basic::Vector2& GetMovementVector() const;
        bool IsCursorVisible() const;
        void SetIsSwapped(bool it_is_swapped);
        bool IsSwapped() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void OnInitialize();
        void OnUpdate(const basic::Time& time_step);
        void OnScroll(int32 scroll);
        void BeginCapture();
        void EndCapture();
        void ShowMouseCursor(bool it_has_to_show);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _CenterMouse();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _Speed;
        basic::Vector2 _Position;
        bool _ItIsCapturing;
        int32 _ScrollValue;
        basic::Vector2 _StoredPosition;
        basic::Vector2 _MovementVector;
        bool _ItHasCursorVisible;
        bool _ItIsSwapped;
    };
}
}
#endif
