#include "wide/ui/property/basic/ui_property_vector3f.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyVector3);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyVector3::PropertyVector3() :
        _Text(NULL),
        _ItIsSliding(false),
        _MinimumValue(real_minimum),
        _MaximumValue(real_maximum)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyVector3::~PropertyVector3()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyVector3::CreateContent()
    {
        _Text = COFFEE_New(widget::Label);
        _Text->Create(this, basic::Vector2i(0, 0), basic::Vector2i(84, 16));
        _Text->SetText(GetName());
        _Text->GetLayout().SetCanvas(GetTextControlSize(), true);

        for(uint32 index=0 ; index<3 ; ++index)
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
        _SetValue(*(basic::Vector3*)GetData(), false);
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyVector3::Update()
    {
        if (_ItIsSliding)
        {
            basic::Vector2 slide_vector;

            if(input::Mouse::IsAvailable())
                slide_vector = input::Mouse::Get().GetMovementVector();

            basic::Vector3 value = *((basic::Vector3*)GetData());
            value[_SlideIndex] += (slide_vector.X + slide_vector.Y) / 400.0f;
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

        if (*((basic::Vector3*)GetData())!=_Value)
            _SetValue(*(basic::Vector3*)GetData(), false);

        Window::Update();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyVector3, Property)
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

    bool PropertyVector3::OnScrollUp(shell::Event& event)
    {
        for (uint32 index=0 ; index<3 ; ++index)
        {
            if (_ComponentArray[index]->HasCursorOver())
            {
                basic::Vector3 value = *((basic::Vector3*)GetData());
                value[index] += 0.01f;
                _SetValue(value);
                return true;
            }
        }

        basic::Vector3 value = *((basic::Vector3*)GetData());

        for (uint32 index=0 ; index<3 ; ++index)
            value[index] += 0.01f;

        _SetValue(value);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyVector3::OnScrollDown(shell::Event& event)
    {
        for(uint32 index=0 ; index<3 ; ++index)
        {
            if(_ComponentArray[index]->HasCursorOver())
            {
                basic::Vector3 value = *((basic::Vector3*)GetData());
                value[index] -= 0.02f;
                _SetValue(value);
                return true;
            }
        }

        basic::Vector3 value = *((basic::Vector3*)GetData());

        for(uint32 index=0 ; index<3 ; ++index)
            value[index] -= 0.02f;

        _SetValue(value);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyVector3::OnButtonReleased(shell::Event& event)
    {
        if (_ItIsSliding && WindowManager::IsAvailable())
        {
            WindowManager::Get().GetCursor().EndCapture();
            _ItIsSliding = false;
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyVector3::OnEdit(shell::Event& event)
    {
        basic::Vector3 value = *((basic::Vector3*)GetData());

        for(uint32 index=0 ; index<3 ; ++index)
            value[index] = _ComponentArray[index]->GetText().GetReal();

        _SetValue(value);
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyVector3::_SetValue(basic::Vector3 value, bool it_has_to_notify)
    {
        basic::String text;
        
        for(uint32 index=0 ; index<3 ; ++index)
        {
            Clamp(value[index], _MinimumValue, _MaximumValue);
            text.Set("%.2f", value[index]);
            _ComponentArray[index]->SetEditedText(text);
        }

        for(uint32 index=0 ; index<3 ; ++index)
        {
            basic::String text("%f", value[index]);
            _ComponentArray[index]->SetEditedText(text);
        }

        if (it_has_to_notify)
            PropertyList::OnPreModify(this);

        *(basic::Vector3*) GetData() = value;
        _Value = value;

        if (it_has_to_notify)
            SendEvent(PROPERTY_MESSAGE_Modified, this);
    }

}
}
