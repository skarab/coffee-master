#ifndef _EDITOR_ASSET_TEXTURE_H_
#define _EDITOR_ASSET_TEXTURE_H_

#include "coffee_editor_includes.h"
#include "asset/asset_importer.h"
#include "asset/asset_manager.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// PNG texture importer
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Texture : public Importer
    {
        COFFEE_Type(Texture);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Texture();
        virtual ~Texture();

        //-QUERIES--------------------------------------------------------------------------------//

        static bool IsSupporting(const basic::String& file_extension);

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual bool Import();

    protected:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Parameters;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, Texture);
}
}
#endif
