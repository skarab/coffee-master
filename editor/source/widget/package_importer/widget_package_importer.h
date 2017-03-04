#ifndef _EDITOR_WIDGET_PACKAGE_IMPORTER_H_
#define _EDITOR_WIDGET_PACKAGE_IMPORTER_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Display package files and choose import settings
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API PackageImporter : public ui::widget::Dialog
    {
        COFFEE_Type(PackageImporter);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PackageImporter();
        ~PackageImporter();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Launch(const storage::PhysicalPath& package_path);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PackageImporter);
        COFFEE_Event bool OnImport(shell::Event& event);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _BuildFilesList();

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        storage::PhysicalPath _PackagePath;
        ui::widget::TreeControl* _Files;
        ui::widget::Button* _Import;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, PackageImporter);
}
}
#endif
