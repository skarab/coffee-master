#ifndef _EDITOR_ASSET_SHADER_PROPERTY_H_
#define _EDITOR_ASSET_SHADER_PROPERTY_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// Shader property
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ShaderProperty : public ui::Property
    {
        COFFEE_PropertyInterface(ShaderProperty, "graphics::ShaderProperty", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ShaderProperty();
        ~ShaderProperty();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ShaderProperty);
        COFFEE_Event bool OnEvaluatorChanged(shell::Event& event);
        COFFEE_Event bool OnSetImage(shell::Event& event);
        COFFEE_Event bool OnQueryDrag(shell::Event& event);
        COFFEE_Event bool OnQueryDrop(shell::Event& event);
        COFFEE_Event bool OnDrop(shell::Event& event);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ui::widget::ComboBox* _Evaluator;
        ui::widget::Button* _SetImageButton;
        meta::ObjectInfo* _CustomInfo;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, ShaderProperty);
}
}
#endif
