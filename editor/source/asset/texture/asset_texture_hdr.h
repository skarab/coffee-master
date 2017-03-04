#ifndef _EDITOR_ASSET_TEXTURE_HDR_H_
#define _EDITOR_ASSET_TEXTURE_HDR_H_

#include "coffee_editor_includes.h"
#include "asset/asset_importer.h"
#include "asset/asset_manager.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// HDR lightprobe/texture importer
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API TextureHDR : public Importer
    {
        COFFEE_Type(TextureHDR);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        TextureHDR();
        ~TextureHDR();

        //-QUERIES--------------------------------------------------------------------------------//

        static bool IsSupporting(const basic::String& file_extension);

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Import();

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        basic::Image* _GenerateMipmap(graphics::Sky& sky, const basic::Image* input, uint32 id, uint32 width, uint32 height);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _Intensity;
        uint32 _Parameters; 
        uint32 _SkyMip;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, TextureHDR);
}
}
#endif
