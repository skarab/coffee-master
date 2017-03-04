#ifndef _COFFEE_WIDE_PROJECT_H_
#define _COFFEE_WIDE_PROJECT_H_

#include "coffee_includes.h"
#include "system/scene/scene_resource.h"
#include "wide/plugins/plugins_object.h"
#include "wide/ui/skin/ui_skin.h"

#define COFFEE_ProjectConfigFile "coffee.project"

namespace coffee
{
    //--------------------------------------------------------------------------------------------//
    /// Project data, deployed from the editor to the player
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Project : public meta::Object
    {
        COFFEE_Type(Project);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Project();
        ~Project();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetIsInEditorMode(bool it_is_in_editor_mode) { _ItIsInEditorMode = it_is_in_editor_mode; }
        bool IsInEditorMode() const { return _ItIsInEditorMode; }
        void SetPath(storage::Path path) { _Path = path; }
        const storage::Path& GetPath() const { return _Path; }
        void SetStartScene(const scene::Resource& start_scene) { _StartScene = start_scene; }
        const scene::Resource& GetStartScene() const { return _StartScene; }
        scene::Resource& GetStartScene() { return _StartScene; }
        void SetCamera(const basic::String& camera) { _Camera = camera; }
        const basic::String& GetCamera() const { return _Camera; }
        void SetSkin(const ui::Skin& skin) { _Skin = skin; }
        const ui::Skin& GetSkin() const { return _Skin; }
        const basic::Prow<plugins::Object*, true>& GetPlugins() const { return _Plugins; }

        //-QUERIES--------------------------------------------------------------------------------//

        storage::PhysicalPath GetFullPath() const;
        bool IsPluginLoaded(const storage::Path& path) const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize();
        bool MountBaseFolders();
        bool MountFolders();
        void LoadPlugin(const storage::Path& path);
        void UnloadPlugin(const storage::Path& path);
        void Update(const basic::Time& time_step);
        void PushEditorPlugins();
        void PopEditorPlugins();

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 _FindPlugin(const storage::Path& path) const;
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIsInEditorMode;
        storage::Path _Path;
        scene::Resource _StartScene;
        basic::String _Camera;
        ui::Skin _Skin;
        basic::Prow<plugins::Object*, true> _Plugins;
        basic::Prow<plugins::Object*> _EditorPlugins;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Project);
}
#endif
