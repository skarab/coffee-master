#include "asset/shader/asset_shader_property.h"
#include "asset/asset_widget.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::ShaderProperty);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ShaderProperty::ShaderProperty() :
        _Evaluator(NULL),
        _SetImageButton(NULL),
        _CustomInfo(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ShaderProperty::~ShaderProperty()
    {
        if (_CustomInfo!=NULL)
            _CustomInfo->Destroy();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ShaderProperty::CreateContent()
    {
        bool it_is_asset = FindParent<Widget>()!=NULL;
        graphics::ShaderProperty* property((graphics::ShaderProperty*)GetData());
        
        if (!it_is_asset && (property->GetEvaluator()<graphics::SHADER_EVALUATOR_Custom
            || property->GetEvaluator()>graphics::SHADER_EVALUATOR_MultiTexture7))
        {
            Destroy();
            return;
        }

        uint32 evaluator_index;
        meta::Enum& evaluator_type = ((meta::Enum&)*COFFEE_FindType("graphics::SHADER_EVALUATOR"));

        _SetImageButton = NULL;
        
        GetLayout().SetStyle(
            ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren
            | ui::LAYOUT_STYLE_VerticalShrink
            | ui::LAYOUT_STYLE_HorizontalExpand);

        ui::Window* label_window = COFFEE_New(ui::Window);
        label_window->Create(this, basic::Vector2i(), basic::Vector2i(), 0);
        label_window->GetLayout().SetStyle(
            ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren
            | ui::LAYOUT_STYLE_VerticalShrink
            | ui::LAYOUT_STYLE_HorizontalExpand);
        
        if (it_is_asset || property->GetEvaluator()!=graphics::SHADER_EVALUATOR_Custom)
        {
            ui::widget::Label* name = COFFEE_New(ui::widget::Label);
            name->Create(label_window, basic::Vector2i(0, 0), basic::Vector2i(84, 16));
            name->SetText(property->GetName());
            name->GetLayout().SetCanvas(40, true);
        }

        if (it_is_asset)
        {
            _Evaluator = COFFEE_New(ui::widget::ComboBox);
            _Evaluator->Create(label_window, basic::Vector2i(), 10);
            _Evaluator->GetLayout().SetCanvas(50, true);
            _Evaluator->AddItem("Disabled", (void*)graphics::SHADER_EVALUATOR_Disabled);

            if (property->GetEvaluator()==graphics::SHADER_EVALUATOR_Disabled)
                _Evaluator->SelectItem(0);

            _Evaluator->AddItem("Custom", (void*)graphics::SHADER_EVALUATOR_Custom);

            if (property->GetEvaluator()==graphics::SHADER_EVALUATOR_Custom)
                _Evaluator->SelectItem(1);

            for (evaluator_index=0 ; evaluator_index<graphics::SHADER_EVALUATOR_Count ; ++evaluator_index)
            {
                if (graphics::SHADER_EVALUATOR_GetType((graphics::SHADER_EVALUATOR)evaluator_index)==property->GetType())
                {
                    _Evaluator->AddItem(
                        evaluator_type.GetValues()[evaluator_index]->GetName(),
                        (void *) evaluator_index);

                    if((graphics::SHADER_EVALUATOR)evaluator_index==property->GetEvaluator())
                        _Evaluator->SelectItem(_Evaluator->GetItemArray().GetSize() - 1);
                }
            }
        }
        
        if (property->GetType()==graphics::SHADER_PROPERTY_TYPE_Texture)
        {
            if (property->GetEvaluator()>=graphics::SHADER_EVALUATOR_MultiTexture0
                && property->GetEvaluator()<=graphics::SHADER_EVALUATOR_MultiTexture7)
            {
                graphics::Texture* texture((graphics::Texture*)property->GetValue().GetObject());
                
                if (texture->GetFilePath()!="/coffee/import/textures/null.texture")
                {
                    ui::widget::Image* image = COFFEE_New(ui::widget::Image);
                    image->Create(this, basic::Vector2i(), basic::Vector2i(80, 80),
                        ui::widget::IMAGE_STYLE_NoBorders | ui::widget::IMAGE_STYLE_AutoSize);
                    image->SetStyle(ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientSunken);
                    //image->GetLayout().SetCanvas(100, true);
                    
                    image->SetImage(*texture);
                }
                
                _SetImageButton = COFFEE_New(ui::widget::Button);
                _SetImageButton->Create(it_is_asset?this:label_window, basic::Vector2i(), basic::Vector2i(80, 24));
                _SetImageButton->SetHelpText(basic::String("Set texture"));
                if (it_is_asset)
                {
                    _SetImageButton->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand);
                }
                else
                {
                    _SetImageButton->GetLayout().SetCanvas(100, true);
                }
                _SetImageButton->SetText(texture->GetFilePath());
            }
        }
         
        if (property->GetEvaluator()==graphics::SHADER_EVALUATOR_Custom)
        {
            ui::Window* custom_window = COFFEE_New(ui::Window);
            custom_window->Create(it_is_asset?this:label_window, basic::Vector2i(), basic::Vector2i(), 0);
            custom_window->GetLayout().SetStyle(
                ui::LAYOUT_STYLE_HorizontalCanvas
                | ui::LAYOUT_STYLE_StickChildren
                | ui::LAYOUT_STYLE_VerticalShrink
                | (it_is_asset?ui::LAYOUT_STYLE_HorizontalExpand:0));
            if (!it_is_asset)
                custom_window->GetLayout().SetCanvas(100, true);

            if (_CustomInfo!=NULL)
                _CustomInfo->Destroy();

            if (property->GetValue().IsScalar())
            {
                 _CustomInfo = COFFEE_New(meta::ObjectInfo,
                    (void*)property->GetValue().GetScalarObject(),
                    (meta::Type*)property->GetValue().GetType());
            }
            else
            {
                _CustomInfo = COFFEE_New(meta::ObjectInfo,
                    (void*)property->GetValue().GetObject(),
                    (meta::Type*)&property->GetValue().GetObject()->GetMetaType());
            }

            _CustomInfo->SetName(it_is_asset?"-> default":property->GetName());
            ui::PropertyManager::Get().CreatePropertyInterface(*custom_window, *_CustomInfo,
                &_CustomInfo->GetType(), NULL, 0);
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ShaderProperty, ui::Property)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Select, ui::widget::Widget, _Evaluator, OnEvaluatorChanged)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _SetImageButton, OnSetImage)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_QueryDrag, ui::Window, OnQueryDrag)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_QueryDrop, ui::Window, OnQueryDrop)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_Drop, ui::Window, OnDrop)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool ShaderProperty::OnEvaluatorChanged(shell::Event& event)
    {
        graphics::ShaderProperty* property((graphics::ShaderProperty*)GetData());
        graphics::SHADER_EVALUATOR evaluator = (graphics::SHADER_EVALUATOR)(
            (uint32)_Evaluator->GetItemData(_Evaluator->GetSelectedIndex()));

        property->SetEvaluator(evaluator);
        property->Create();
        DestroyChildren();
        CreateContent();
        SendEvent(ui::PROPERTY_MESSAGE_Modified, this);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ShaderProperty::OnSetImage(shell::Event& event)
    {
        graphics::ShaderProperty* property((graphics::ShaderProperty*)GetData());
        graphics::Texture* texture((graphics::Texture*)property->GetValue().GetObject());
        ui::FileDialog* file_dialog;
        basic::Text extensions;

        extensions.AddLine(texture->GetResourceType() + " " + basic::String("resource"));
        extensions.AddLine(texture->GetResourceType());

        file_dialog = COFFEE_New(ui::FileDialog);
        file_dialog->Create(basic::String("Set texture"),
            ui::FILE_DIALOG_FLAG_Open | ui::FILE_DIALOG_FLAG_FileMustExist, extensions);
        if (file_dialog->DoModal())
        {
            *texture = resource::Manager::Get().Load(file_dialog->GetFilePath());
            DestroyChildren();
            CreateContent();
            SendEvent(ui::PROPERTY_MESSAGE_Modified, this);
            file_dialog->Destroy();
        }
        return true;
    }

    
    //--------------------------------------------------------------------------------------------//

    bool ShaderProperty::OnQueryDrag(shell::Event& event)
    {
        graphics::ShaderProperty* prop((graphics::ShaderProperty*)GetData());
        graphics::SHADER_EVALUATOR evaluator = prop->GetEvaluator();

        return ((uint32)evaluator>=(uint32)graphics::SHADER_EVALUATOR_MultiTexture0)
            && ((uint32)evaluator<=(uint32)graphics::SHADER_EVALUATOR_MultiTexture7);
    }

    //--------------------------------------------------------------------------------------------//

    bool ShaderProperty::OnQueryDrop(shell::Event& event)
    {
        if (event.GetParameters().GetParameter()!=NULL)
        {
            if (event.GetParameters().GetParameter()->IsKindOf<ui::widget::TreeControlItem>()
                || event.GetParameters().GetParameter()->IsKindOf<ShaderProperty>())
            {
                graphics::ShaderProperty* prop((graphics::ShaderProperty*)GetData());
                graphics::SHADER_EVALUATOR evaluator = prop->GetEvaluator();

                return ((uint32)evaluator>=(uint32)graphics::SHADER_EVALUATOR_MultiTexture0)
                    && ((uint32)evaluator<=(uint32)graphics::SHADER_EVALUATOR_MultiTexture7);
            }
        }
        return false;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool ShaderProperty::OnDrop(shell::Event& event)
    {
        if (event.GetParameters().GetParameter()!=NULL)
        {
            if (event.GetParameters().GetParameter()->IsKindOf<ui::widget::TreeControlItem>())
            {
                const ui::widget::TreeControlItem* item = static_cast<const ui::widget::TreeControlItem*>(event.GetParameters().GetParameter());
                storage::Path path = item->GetPath();
                storage::Path head = path.GetHeadFilePath("*");
                if (head!=path || head.GetFileExtension()!="texture")
                {
                    if (head.IsPrefixed("/assets")) { head.CutLeft(strlen("/assets")); head = basic::String("/import")+head; }
                    if (head.IsPrefixed("/coffee/assets")) { head.CutLeft(strlen("/coffee/assets")); head = basic::String("/coffee/import")+head; }

                    if (head.GetFileExtension()!="texture")
                    {
                        if (path.GetFileExtension()=="texture")
                        {
                            path = head.GetPath()+"/"+path.GetFileName();
                        }
                        else
                        {
                            path = head.GetPath()+"/"+path.GetFileNameWithoutExtension()+".texture";
                        }
                    }
                }
                
                if (path.GetFileExtension()!="texture" || !storage::System::Get().HasPath(path))
                    return false;

                graphics::ShaderProperty* prop((graphics::ShaderProperty*)GetData());
                graphics::Texture* texture((graphics::Texture*)prop->GetValue().GetObject());
                *texture = resource::Manager::Get().Load(path);
                DestroyChildren();
                CreateContent();
                SendEvent(ui::PROPERTY_MESSAGE_Modified, this);
                return true;
            }
            else if (event.GetParameters().GetParameter()->IsKindOf<ShaderProperty>())
            {
                graphics::ShaderProperty* prop((graphics::ShaderProperty*)GetData());
                graphics::Texture* texture((graphics::Texture*)prop->GetValue().GetObject());
                graphics::ShaderProperty* source_prop((graphics::ShaderProperty*)(
                    ((ShaderProperty*)event.GetParameters().GetParameter())->GetData()));
                graphics::Texture* source_texture((graphics::Texture*)source_prop->GetValue().GetObject());
                *texture = *source_texture;
                DestroyChildren();
                CreateContent();
                SendEvent(ui::PROPERTY_MESSAGE_Modified, this);
            }
        }
        return false;
    }

}
}
