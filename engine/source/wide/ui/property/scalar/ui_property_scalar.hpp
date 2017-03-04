//------------------------------------------------------------------------------------------------//
/// @file wide/ui/property/scalar/ui_property_scalar.hpp
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    template< typename type, typename param_type >
    PropertyScalar< type, param_type >::PropertyScalar() :
        _Text(NULL),
        _EditBox(NULL),
        _Button(NULL),
        _ItIsUsingExtremum(false),
        _ItIsSliding(false),
        _ScrollStep(0.1f),
        _SlideFactor(0.125f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, typename param_type >
    PropertyScalar< type, param_type >::~PropertyScalar()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    template< typename type, typename param_type >
    void PropertyScalar< type, param_type >::SetExtremum(type minimum_value, type maximum_value)
    {
        _MinimumValue = minimum_value;
        _MaximumValue = maximum_value;
        _ItIsUsingExtremum = true;

        _SetValue(*(type *) GetData());
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    template< typename type, typename param_type >
    void PropertyScalar< type, param_type >::CreateContent()
    {
        _Text = COFFEE_New(widget::Label);
        _Text->Create(this, basic::Vector2i(0, 0), basic::Vector2i(84, 16));
        _Text->SetText(GetName());
        _Text->GetLayout().SetCanvas(GetTextControlSize(), true);

        _EditBox = COFFEE_New(widget::EditBox);
        _EditBox->Create(this, basic::Vector2i(88, 0), 85);
        _EditBox->GetLayout().SetCanvas(100 - GetTextControlSize()-6, true);

        _Button = COFFEE_New(widget::Button);
        _Button->Create(this, basic::Vector2i(176, 0), basic::Vector2i(18, 18),
            widget::BUTTON_STYLE_Default);
        _Button->SetImage(SKIN_ICON_Scroll);
        _Button->GetLayout().SetCanvas(6, true);

        _SetValue(*(type *) GetData());

        if (GetObjectInfo().IsAttribute() && GetObjectInfo().GetAttribute()._Param!=NULL)
        {
            if ((GetObjectInfo().GetAttribute()._Param->GetMode() & meta::MODE_ReadOnly) > 0)
            {
                _EditBox->Enable(false);
                _Button->Enable(false);
            }

            if (GetObjectInfo().GetAttribute()._Param->IsA<param_type>())
            {
                const param_type* param =
                    static_cast<const param_type*>(GetObjectInfo().GetAttribute()._Param);

                SetExtremum(param->GetMinimumValue(), param->GetMaximumValue());
                _ScrollStep = (param->GetMaximumValue() - param->GetMinimumValue()) / 30.0f;

                if (((type) 1.0f) + _ScrollStep == (type) 1.0f)
                    _ScrollStep = 1.0f;

                _SlideFactor = (param->GetMaximumValue() - param->GetMinimumValue()) / 60.0f;
                Clamp(_SlideFactor, 0.01f, 0.2f);
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, typename param_type >
    void PropertyScalar< type, param_type >::Update()
    {
        if(_ItIsSliding)
        {
            basic::Vector2 slide_vector;

            if(input::Mouse::IsAvailable())
                slide_vector = input::Mouse::Get().GetMovementVector();

            PropertyList::OnPreModify(this);
            _SetValue((type)(_GetValue() + (slide_vector.X + slide_vector.Y) * _SlideFactor));
            SendEvent(PROPERTY_MESSAGE_Modified, this);
        }
        else if (_Button->GetState()==widget::BUTTON_STATE_On
            && WindowManager::IsAvailable())
        {
            WindowManager::Get().GetCursor().BeginCapture();
            _ItIsSliding = true;
        }

        if (*((type*)GetData())!=_Value)
        {
            _SetValue(*((type *) GetData()));
        }

        Window::Update();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    template< typename type, typename param_type >
    bool PropertyScalar< type, param_type >::_HandleEvent(coffee::shell::Event& event)
    {
        return _InternHandleEvent(event) || _InternHandleAncestorEvent(event);
    }
    template< typename type, typename param_type >
    bool PropertyScalar< type, param_type >::_InternHandleEvent(coffee::shell::Event& event)
    {
        bool (Property::*parent_func)(shell::Event &) = &Property::_InternHandleEvent;
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Changed, widget::Widget, _EditBox, OnTextChanged)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_ScrollUp, Window, OnScrollUp)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_ScrollDown, Window, OnScrollDown)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _Button, OnButtonReleased)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_PressedCanceled, widget::Widget, _Button, OnButtonReleased)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    template< typename type, typename param_type >
    bool PropertyScalar< type, param_type >::OnTextChanged(shell::Event& event)
    {
        if(_EditBox->GetText().GetLength() > 0 && !(_EditBox->GetText().GetLength() == 1
            && _EditBox->GetText().GetBuffer()[0] == '-'))
        {
            PropertyList::OnPreModify(this);
            _SetValue(_GetValue());
            SendEvent(PROPERTY_MESSAGE_Modified, this);
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, typename param_type >
    bool PropertyScalar< type, param_type >::OnScrollUp(shell::Event& event)
    {
        if(_EditBox->HasCursorOver())
        {
            PropertyList::OnPreModify(this);
            _SetValue((type)(_GetValue() + _ScrollStep));
            SendEvent(PROPERTY_MESSAGE_Modified, this);
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, typename param_type >
    bool PropertyScalar< type, param_type >::OnScrollDown(shell::Event& event)
    {
        if(_EditBox->HasCursorOver())
        {
            PropertyList::OnPreModify(this);
            _SetValue((type)(_GetValue() - _ScrollStep));
            SendEvent(PROPERTY_MESSAGE_Modified, this);
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, typename param_type >
    bool PropertyScalar< type, param_type >::OnButtonReleased(shell::Event& event)
    {
        if (_ItIsSliding && WindowManager::IsAvailable())
        {
            WindowManager::Get().GetCursor().EndCapture();
            _ItIsSliding = false;
        }
        return true;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    template< typename type, typename param_type >
    void PropertyScalar< type, param_type >::_SetValue(type value)
    {
        if (_ItIsUsingExtremum)
            Clamp(value, _MinimumValue, _MaximumValue);

        _EditBox->SetEditedText(_GetTextFromValue(value));
        *((type *) GetData()) = value;
        _Value = value;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, typename param_type >
    type PropertyScalar< type, param_type >::_GetValue()
    {
        return _GetValueFromText(_EditBox->GetText());
    }

}
}
//------------------------------------------------------------------------------------------------//
