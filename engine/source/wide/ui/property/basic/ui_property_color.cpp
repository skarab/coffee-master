#include "wide/ui/property/basic/ui_property_color.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyColor);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyColor::PropertyColor() :
        _Text(NULL),
        _ItIsSliding(false),
        _MinimumValue(0.0f),
        _MaximumValue(1.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyColor::~PropertyColor()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyColor::CreateContent()
    {
        _Text = COFFEE_New(widget::Label);
        _Text->Create(this, basic::Vector2i(0, 0), basic::Vector2i(84, 16));
        _Text->SetText(GetName());
        _Text->GetLayout().SetCanvas(GetTextControlSize(), true);

        for(uint32 component_index=0 ; component_index<4 ; ++component_index)
        {
            _ButtonArray[component_index] = COFFEE_New(widget::Button);
            _ButtonArray[component_index]->Create(this,
                coffee::basic::Vector2i(86 + 60 * component_index, 1),
                coffee::basic::Vector2i(30, 14), widget::BUTTON_STYLE_Default);
            _ButtonArray[component_index]->GetLayout().SetCanvas(
                (100 - GetTextControlSize()) / 4, true);

            if (GetObjectInfo().IsAttribute() && GetObjectInfo().GetAttribute()._Param!=NULL
                && ((GetObjectInfo().GetAttribute()._Param->GetMode() & meta::MODE_ReadOnly) > 0))
            {
                _ButtonArray[component_index]->Enable(false);
            }
        }

        _ButtonArray[0]->SetHelpText(basic::String("Red"));
        _ButtonArray[1]->SetHelpText(basic::String("Green"));
        _ButtonArray[2]->SetHelpText(basic::String("Blue"));
        _ButtonArray[3]->SetHelpText(basic::String("Alpha"));

        _SetValue(*(basic::Color*)GetData(), false);
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyColor::Update()
    {
        if(_ItIsSliding)
        {
            basic::Vector2 slide_vector;

            if(input::Mouse::IsAvailable())
                slide_vector = input::Mouse::Get().GetMovementVector();

            basic::Color value = *((basic::Color*)GetData());
            value.GetBuffer()[_SlideIndex] += (slide_vector.X + slide_vector.Y) / 400.0f;
            _SetValue(value);
        }
        else
        {
            for (uint32 component_index=0 ; component_index<4 ; ++component_index)
            {
                if (_ButtonArray[component_index]->GetState()==widget::BUTTON_STATE_On
                    && WindowManager::IsAvailable())
                {
                    WindowManager::Get().GetCursor().BeginCapture();
                    _ItIsSliding = true;
                    _SlideIndex = component_index;
                    break;
                }
            }
        }

        if (*((basic::Color*)GetData()) != _Value)
            _SetValue(*(basic::Color *)GetData());

        Window::Update();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyColor, Property)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_ScrollUp, Window, OnScrollUp)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_ScrollDown, Window, OnScrollDown)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _ButtonArray[0], OnButtonReleased)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_PressedCanceled, widget::Widget, _ButtonArray[0], OnButtonReleased)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _ButtonArray[1], OnButtonReleased)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_PressedCanceled, widget::Widget, _ButtonArray[1], OnButtonReleased)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _ButtonArray[2], OnButtonReleased)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_PressedCanceled, widget::Widget, _ButtonArray[2], OnButtonReleased)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _ButtonArray[3], OnButtonReleased)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_PressedCanceled, widget::Widget, _ButtonArray[3], OnButtonReleased)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool PropertyColor::OnScrollUp(shell::Event& event)
    {
        for(uint32 component_index=0 ; component_index<4 ; ++component_index)
        {
            if(_ButtonArray[component_index]->HasCursorOver())
            {
                basic::Color value = *((basic::Color*)GetData());
                value.GetBuffer()[component_index] += 0.01f;
                _SetValue(value);
                return true;
            }
        }

        basic::Color value = *((basic::Color*)GetData());

        for(uint32 component_index=0 ; component_index<3 ; ++component_index)
            value.GetBuffer()[component_index] += 0.01f;

        _SetValue(value);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyColor::OnScrollDown(shell::Event& event)
    {
        for (uint32 component_index=0 ; component_index<4 ; ++component_index)
        {
            if (_ButtonArray[component_index]->HasCursorOver())
            {
                basic::Color value = *((basic::Color*)GetData());
                value.GetBuffer()[component_index] -= 0.02f;
                _SetValue(value);
                return true;
            }
        }

        basic::Color value = *((basic::Color*)GetData());

        for (uint32 component_index=0 ; component_index<3 ; ++component_index)
            value.GetBuffer()[ component_index ] -= 0.02f;

        _SetValue(value);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyColor::OnButtonReleased(shell::Event& event)
    {
        if (_ItIsSliding && WindowManager::IsAvailable())
        {
            WindowManager::Get().GetCursor().EndCapture();
            _ItIsSliding = false;
        }

        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyColor::_SetValue(basic::Color value, bool it_has_to_notify)
    {
        basic::String text;
        
        for (uint32 component_index=0 ; component_index<4 ; ++component_index)
        {
            Clamp(value.GetBuffer()[component_index], _MinimumValue, _MaximumValue);
            text.Set("%.2f", value.GetBuffer()[component_index]);
            _ButtonArray[component_index]->SetText(text);
        }

        for (uint32 component_index=0 ; component_index<4 ; ++component_index)
        {
            _ButtonArray[component_index]->SetColor(value);
        }

        if (it_has_to_notify)
            PropertyList::OnPreModify(this);

        *(basic::Color*) GetData() = value;
        _Value = value;

        if (it_has_to_notify)
            SendEvent(PROPERTY_MESSAGE_Modified, this);
    }

}
}
