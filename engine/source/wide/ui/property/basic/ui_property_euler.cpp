#include "wide/ui/property/basic/ui_property_euler.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyEuler);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyEuler::PropertyEuler() :
        _Text(NULL),
        _ItIsSliding(false),
        _MinimumValue(real_minimum),
        _MaximumValue(real_maximum)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyEuler::~PropertyEuler()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyEuler::CreateContent()
    {
        _Text = COFFEE_New(widget::Label);
        _Text->Create(this, basic::Vector2i(0, 0), basic::Vector2i(84, 16));
        _Text->SetText(GetName());
        _Text->GetLayout().SetCanvas(GetTextControlSize(), true);

        for (uint32 index=0 ; index<3 ; ++index)
        {
            _ButtonArray[index] = COFFEE_New(widget::Button);
            _ButtonArray[index]->Create(this,
                coffee::basic::Vector2i(86 + 60 * index, 1), 16);
            _ButtonArray[index]->GetLayout().SetCanvas(
                (100 - GetTextControlSize()) / 9, true);

            _ComponentArray[index] = COFFEE_New(widget::EditBox);
            _ComponentArray[index]->Create(this,
                coffee::basic::Vector2i(86 + 60 * index+10, 1), 30);
            _ComponentArray[index]->GetLayout().SetCanvas(
                (100 - GetTextControlSize()) * 2 / 9, true);

            if (GetObjectInfo().IsAttribute() && GetObjectInfo().GetAttribute()._Param!=NULL
                && ((GetObjectInfo().GetAttribute()._Param->GetMode() & meta::MODE_ReadOnly) > 0))
            {
                _ButtonArray[index]->Enable(false);
                _ComponentArray[index]->Enable(false);
            }
        }

        _ButtonArray[0]->SetText("x");
        _ButtonArray[1]->SetText("y");
        _ButtonArray[2]->SetText("z");
        _SetValue(*(basic::Euler*)GetData(), false);
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyEuler::Update()
    {
        if (_ItIsSliding)
        {
            basic::Vector2 slide_vector;

            if (input::Mouse::IsAvailable())
                slide_vector = input::Mouse::Get().GetMovementVector();

            basic::Euler value = *((basic::Euler*)GetData());
            (&value.X)[_SlideIndex] += (slide_vector.X + slide_vector.Y) / 400.0f;
            _SetValue(value);
        }
        else
        {
            for (uint32 index=0 ; index<3 ; ++index)
            {
                if (_ButtonArray[index]->GetState()==widget::BUTTON_STATE_On
                    && WindowManager::IsAvailable())
                {
                    WindowManager::Get().GetCursor().BeginCapture();
                    _ItIsSliding = true;
                    _SlideIndex = index;
                    break;
                }
            }
        }

        if (*((basic::Euler*)GetData()) != _Value)
            _SetValue(*(basic::Euler *)GetData(), false);

        Window::Update();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyEuler, Property)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_ScrollUp, Window, OnScrollUp)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_ScrollDown, Window, OnScrollDown)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Changed, widget::Widget, _ComponentArray[0], OnEdit)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Changed, widget::Widget, _ComponentArray[1], OnEdit)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Changed, widget::Widget, _ComponentArray[2], OnEdit)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _ButtonArray[0], OnButtonReleased)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_PressedCanceled, widget::Widget, _ButtonArray[0], OnButtonReleased)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _ButtonArray[1], OnButtonReleased)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_PressedCanceled, widget::Widget, _ButtonArray[1], OnButtonReleased)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _ButtonArray[2], OnButtonReleased)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_PressedCanceled, widget::Widget, _ButtonArray[2], OnButtonReleased)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool PropertyEuler::OnScrollUp(shell::Event& event)
    {
        for (uint32 index=0 ; index<3 ; ++index)
        {
            if (_ComponentArray[index]->HasCursorOver())
            {
                basic::Euler value = *((basic::Euler*)GetData());
                (&value.X)[index] += 0.01f;
                _SetValue(value);
                return true;
            }
        }

        basic::Euler value = *((basic::Euler*)GetData());

        for (uint32 index=0 ; index<3 ; ++index)
            (&value.X)[index] += 0.01f;

        _SetValue(value);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyEuler::OnScrollDown(shell::Event& event)
    {
        for (uint32 index=0 ; index<3 ; ++index)
        {
            if (_ComponentArray[index]->HasCursorOver())
            {
                basic::Euler value = *((basic::Euler*)GetData());
                (&value.X)[index] -= 0.02f;
                _SetValue(value);
                return true;
            }
        }

        basic::Euler value = *((basic::Euler*)GetData());

        for (uint32 index=0 ; index<3 ; ++index)
            (&value.X)[index] -= 0.02f;

        _SetValue(value);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyEuler::OnButtonReleased(shell::Event& event)
    {
        if (_ItIsSliding && WindowManager::IsAvailable())
        {
            WindowManager::Get().GetCursor().EndCapture();
            _ItIsSliding = false;
        }

        return true;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool PropertyEuler::OnEdit(shell::Event& event)
    {
        basic::Euler value = *((basic::Euler*)GetData());
        for (uint32 index=0 ; index<3 ; ++index)
            (&value.X)[index].SetDegrees(_ComponentArray[index]->GetText().GetReal());
        _SetValue(value);
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyEuler::_SetValue(basic::Euler value, bool it_has_to_notify)
    {
        basic::String text;
        
        for (uint32 index=0 ; index<3 ; ++index)
        {
            float val = (&value.X)[index].GetDegrees();
            Clamp(val, _MinimumValue, _MaximumValue);
            (&value.X)[index].SetDegrees(val);
            text.Set("%.4f", (&value.X)[index].GetDegrees());
            _ComponentArray[index]->SetText(text);
        }

        if (it_has_to_notify)
            PropertyList::OnPreModify(this);

        *(basic::Euler*) GetData() = value;
        _Value = value;

        if (it_has_to_notify)
            SendEvent(PROPERTY_MESSAGE_Modified, this);
    }

}
}
