#include "wide/ui/property/scalar/ui_property_enum.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyEnum);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyEnum::PropertyEnum() :
        _EnumType(NULL),
        _Text(NULL),
        _ComboBox(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyEnum::~PropertyEnum()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyEnum::CreateContent()
    {
        uint32 value_index;

        _EnumType = (meta::Enum*)&GetObjectInfo().GetType();

        if(_EnumType->GetType()==meta::ENUM_TYPE_Multi)
        {
            _Group = COFFEE_New(widget::Group);
            _Group->Create(this, basic::Vector2i(),
                basic::Vector2i(GetClientRect().Size.X, 20));
            _Group->SetTitleBarText(GetName());

            for(value_index=0 ; value_index<_EnumType->GetValues().GetSize() ; ++value_index)
            {
                widget::CheckBox* check_box;
                check_box = COFFEE_New(widget::CheckBox);
                check_box->Create(_Group, basic::Vector2i(),
                    basic::Vector2i(40, 20), ui::widget::CHECK_BOX_STYLE_Default);
                check_box->SetText(_EnumType->GetValues()[value_index]->GetName());
                check_box->SetData((void *) _EnumType->GetValues()[value_index]->GetValue());

                if (((*((uint32*)GetData())) & _EnumType->GetValues()[value_index]->GetValue()) > 0)
                    check_box->SetState(widget::CHECK_BOX_STATE_Checked);

                if (GetObjectInfo().IsAttribute() && GetObjectInfo().GetAttribute()._Param!=NULL
                    && ((GetObjectInfo().GetAttribute()._Param->GetMode() & meta::MODE_ReadOnly) > 0))
                {
                    check_box->Enable(false);
                }
            }
        }
        else
        {
            _Text = COFFEE_New(widget::Label);
            _Text->Create(this, basic::Vector2i(0, 0), basic::Vector2i(84, 20));
            _Text->SetText(GetName());
            _Text->GetLayout().SetCanvas(GetTextControlSize(), true);

            _ComboBox = COFFEE_New(widget::ComboBox);
            _ComboBox->Create(this, basic::Vector2i(88, 0), 108);
            _ComboBox->GetLayout().SetCanvas(100 - GetTextControlSize(), true);

            if(_EnumType->GetType()==meta::ENUM_TYPE_SingleNone)
            {
                _ComboBox->AddItem("None");
                if ((*((uint32*)GetData()))==NONE)
                    _ComboBox->SelectItem(0);
            }

            for (value_index=0 ; value_index<_EnumType->GetValues().GetSize() ; ++value_index)
            {
                int id = _ComboBox->AddItem(_EnumType->GetValues()[value_index]->GetName());
                if ((*((uint32*)GetData()))==_EnumType->GetValues()[value_index]->GetValue())
                    _ComboBox->SelectItem(id);
            }

            if (GetObjectInfo().IsAttribute() && GetObjectInfo().GetAttribute()._Param!=NULL
                && ((GetObjectInfo().GetAttribute()._Param->GetMode() & meta::MODE_ReadOnly) > 0))
            {
                _ComboBox->Enable(false);
            }
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyEnum, Property)
        COFFEE_RegisterEventHandler(widget::EVENT_Select, widget::Widget, OnSelectItem)
        COFFEE_RegisterEventHandler(widget::EVENT_Pressed, widget::Widget, OnCheckItem)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool PropertyEnum::OnSelectItem(shell::Event& event)
    {
        uint32 enum_value(NONE);

        if(_EnumType->GetType()!=meta::ENUM_TYPE_Multi)
        {
            if (_EnumType->GetType()==meta::ENUM_TYPE_SingleNone)
            {
                if (_ComboBox->GetSelectedIndex()==0)
                {
                    enum_value = NONE;
                }
                else
                {
                    enum_value = _EnumType->GetValues()[_ComboBox->GetSelectedIndex()-1]->GetValue();
                }
            }
            else
            {
                enum_value = _EnumType->GetValues()[_ComboBox->GetSelectedIndex()]->GetValue();
            }

            PropertyList::OnPreModify(this);
            *((uint32 *) GetData()) = enum_value;
            SendEvent(PROPERTY_MESSAGE_Modified, this);
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyEnum::OnCheckItem(shell::Event& event)
    {
        if(_EnumType->GetType()==meta::ENUM_TYPE_Multi)
        {
            if(event.GetTarget()!=NULL && event.GetTarget()->IsA<ui::widget::CheckBox>())
            {
                widget::CheckBox* check_box = (widget::CheckBox*)event.GetTarget();
                uint32 value = (uint32)check_box->GetData();
                
                PropertyList::OnPreModify(this);

                COFFEE_EnableFlag(*((uint32 *) GetData()), value, check_box->GetState()==widget::CHECK_BOX_STATE_Checked);
                SendEvent(PROPERTY_MESSAGE_Modified, this);
            }
        }

        return true;
    }

}
}
