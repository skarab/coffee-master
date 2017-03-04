#ifndef _EDITOR_WIDGET_EDITOR_FRAME_H_
#define _EDITOR_WIDGET_EDITOR_FRAME_H_

#include "coffee_editor_includes.h"
#include "widget/properties/widget_properties.h"
#include "widget/explorer/widget_explorer.h"
#include "widget/mdi/widget_mdi.h"
#include "widget/output/widget_output_bar.h"
#include "widget/debugger/widget_debugger.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Custom editor GUI frame defining global layout
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API EditorFrame
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        EditorFrame();
        ~EditorFrame();

        //-ACCESSORS------------------------------------------------------------------------------//

        const MDI& GetSceneMDI() const { return *_SceneMDI; }
        MDI& GetSceneMDI() { return *_SceneMDI; }
        const OutputBar& GetOutputBar() const { return *_OutputBar; }
        OutputBar& GetOutputBar() { return *_OutputBar; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize();
        void Finalize();
        void SetProgress(basic::String text, real percentage);
        void SetSubProgress(real percentage);
       
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ui::Window* _MainFrame;
        ui::Window* _StatusFrame;
        OutputBar* _OutputBar;
        Debugger* _Debugger;
        ui::widget::Label* _StatusProgressLabel;
        ui::widget::ProgressBar* _StatusProgress;
        ui::widget::ProgressBar* _StatusSubProgress;
        ui::Window* _BodyFrame;
        MDI* _SceneMDI;
    };
}
}
#endif
