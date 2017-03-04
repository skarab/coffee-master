#ifndef _EDITOR_ASSET_FONT_FNT_H_
#define _EDITOR_ASSET_FONT_FNT_H_

#include "coffee_editor_includes.h"
#include "asset/asset_importer.h"
#include "asset/asset_manager.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// FNT font asset
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API FontFNT : public Importer
    {
        COFFEE_Type(FontFNT);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FontFNT();
        ~FontFNT();

        //-QUERIES--------------------------------------------------------------------------------//

        static bool IsSupporting(const basic::String& file_extension);

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Import();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//


    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, FontFNT);
}
}
#endif
