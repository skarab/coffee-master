#ifndef _EDITOR_ASSET_TEXTURE_PNG_H_
#define _EDITOR_ASSET_TEXTURE_PNG_H_

#include "coffee_editor_includes.h"
#include "asset/texture/asset_texture.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// PNG texture importer
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API TexturePNG : public Texture
    {
        COFFEE_Type(TexturePNG);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        TexturePNG();
        ~TexturePNG();

        //-QUERIES--------------------------------------------------------------------------------//

        static bool IsSupporting(const basic::String& file_extension);

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Import();
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, TexturePNG);
}
}
#endif
