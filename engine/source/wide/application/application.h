#ifndef _COFFEE_WIDE_APPLICATION_H_
#define _COFFEE_WIDE_APPLICATION_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "wide/application/control/application_control_manager.h"
#include "wide/application/command/application_command.h"
#include "wide/project/project.h"

namespace coffee
{
    //--------------------------------------------------------------------------------------------//
    /// Heart of each Coffee application
    ///
    /// This is an interface to inherit in each new project.
    /// It contains the project configuration and the application controls, and gives access to
    /// useful callbacks...
    /// Basically it's only a simple single-threaded singleton module, handled automatically by
    /// the module manager.
    /// It has shell::MODULE_ATTRIBUTE_Defaults properties.
    ///
    /// @see COFFEE_RegisterApplication
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Application : public shell::Module
    {
        COFFEE_DeclareModuleSingleton(Application);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Application();
        virtual ~Application();

        //-ACCESSORS------------------------------------------------------------------------------//

        /// @brief Get the control manager
        const ApplicationControlManager& GetControlManager() const;
        ApplicationControlManager& GetControlManager();

        /// @brief Check if the application window has the focus
        bool HasFocus() const;
        
        /// @brief Get the target project
        const Project& GetProject() const;
        Project& GetProject();

        /// @brief Get the main game window
        virtual ui::Window* GetWindow();

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// @brief Initialization method called after whole engine is considered as initialized
        virtual void OnInitialize();

        /// @brief Finalization method
        virtual void OnFinalize();

        /// @brief Update method called each frame
        virtual void OnUpdate(const basic::Time& time_step);

        /// @brief Render method called per viewport, at each frame
        virtual void OnRender(graphics::Viewport& viewport, bool it_is_transparent, bool it_is_hdr);

        /// @brief Control activation handling
        virtual void OnActivateControl(ApplicationControl& control) {}

        /// @brief Control deactivation handling
        virtual void OnDeactivateControl(ApplicationControl& control) {}

        /// @brief Callback for when the mouse cursor enter the control toolbar button
        virtual void OnBeginCursorOverControl(ApplicationControl& control, ui::Window& widget) {}
        
        /// @brief Callback for when the mouse cursor leave the control toolbar button
        virtual void OnEndCursorOverControl(ApplicationControl& control) {}
        
		/// @brief Callback for when the application window get the focus
		virtual void OnGetFocus();

        /// @brief Callback for when the application window lose the focus
		virtual void OnLoseFocus();

        /// @brief Callback to receive logged messages
        virtual void OnLog(core::Log::Type type, const char* message) {}

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Application);
        COFFEE_Event bool OnStart(shell::Event& event);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ApplicationControlManager* _ControlManager;
        bool _ItHasFocus;
        Project _Project;
    };

}
#endif
