#ifndef _COFFEE_WIDE_APPLICATION_CONTROL_H_
#define _COFFEE_WIDE_APPLICATION_CONTROL_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/input/input.h"
#include "wide/ui/widget/widgets.h"
#include "system/graphics/viewport/graphics_viewport.h"

namespace coffee
{
    //-FORWARDS-----------------------------------------------------------------------------------//
    class ApplicationControlManager;
namespace edition
{
    class Plugin;
    class SelectionManager;
    class UndoManager;
}

    //--------------------------------------------------------------------------------------------//
    /// Base class of controls in the application
    ///
    /// An application control is a user interface behavior, which may be a single command, 
    /// a special control mode, or a hierarchical set of ApplicationControl (plugin, editor, ...).
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ApplicationControl : public input::Handler
    {
        friend class ApplicationControlManager;

        COFFEE_Type(ApplicationControl);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ApplicationControl(basic::String name="", basic::String help_text="");
        virtual ~ApplicationControl();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::String& GetName() const;
        const basic::String& GetHelpText() const;
        const ApplicationControl& GetActiveControl() const;
        ApplicationControl& GetActiveControl();
        const ApplicationControl& GetHeadActiveControl() const;
        ApplicationControl& GetHeadActiveControl();
        const ApplicationControl& GetHeadActiveControlGroup() const;
        ApplicationControl& GetHeadActiveControlGroup();
        const edition::Plugin* GetPlugin() const;
        edition::Plugin* GetPlugin();
        edition::UndoManager* GetUndoManager();
        const edition::SelectionManager* GetSelectionManager() const;
		edition::SelectionManager* GetSelectionManager();
		const input::Command& GetCommand() const;
        input::Command& GetCommand();
        const basic::Prow<input::Command*, true>& GetCommandArray() const;
        basic::Prow<input::Command*, true>& GetCommandArray();
        void SetViewport(graphics::Viewport* viewport);
        const graphics::Viewport& GetViewport() const;
        graphics::Viewport& GetViewport();
        graphics::Viewport& GetParentViewport();
        
        //-QUERIES--------------------------------------------------------------------------------//

        virtual bool IsUsable() const;
        bool IsValid() const;
        bool IsActive() const;
        bool HasActiveControl() const;
        bool HasCommand() const;
        bool HasViewport() const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void Register(ApplicationControl& control, input::Command* command=NULL);
        void Unregister();
        void Initialize();
        void Finalize();
        void Activate();
        void Deactivate();
        void DeactivateChildren();
        void Update(const basic::Time& time_step);
        void Render(graphics::Viewport& viewport, bool it_is_transparent, bool it_is_hdr);

        virtual void Destroy();

        void PopulateToolBar(ui::widget::ToolBar& tool_bar);
        void UpdateToolBar(ui::widget::ToolBar& tool_bar);
        
        void RegisterCommand(input::Command* command);
        
        //-HANDLERS-------------------------------------------------------------------------------//

        virtual void OnInitialize();
        virtual void OnFinalize();
        virtual void OnActivate();
        virtual void OnDeactivate();
        virtual void OnUpdate(const basic::Time& time_step) {}
        virtual void OnRender(graphics::Viewport& viewport, bool it_is_transparent, bool it_is_hdr) {}
        virtual void OnChildActivate(ApplicationControl& control);
        virtual void OnChildDeactivate(ApplicationControl& control);

        virtual void OnPopupMenu(ui::widget::Menu& menu);
        virtual void OnPopulateToolBar(ui::widget::ToolBar& tool_bar);
        virtual void OnUpdateToolBar(ui::widget::ToolBar& tool_bar);
        virtual void OnBeginCursorOverToolBar(ui::Window& widget);
        virtual void OnEndCursorOverToolBar();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ApplicationControl);
        COFFEE_Event bool OnCommand(shell::Event& event);
        
        COFFEE_DeclareExternEventHandler(ApplicationControl, OnCommandButton);
        COFFEE_DeclareExternEventHandler(ApplicationControl, OnBeginCursorOver);
        COFFEE_DeclareExternEventHandler(ApplicationControl, OnEndCursorOver);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool _CheckValidity();
        void _ChildActivate(ApplicationControl& control);
        void _ChildDeactivate(ApplicationControl& control);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Name;
        basic::String _HelpText;
        ui::widget::Button* _CommandButton;
        ApplicationControl* _ActiveControl;
        input::Command* _Command;
        basic::Prow<input::Command*, true> _CommandArray;
        graphics::Viewport* _Viewport;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ApplicationControl);
}
#endif
