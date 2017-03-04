#ifndef _COFFEE_GRAPHICS_TEXTURE_ARRAY_H_
#define _COFFEE_GRAPHICS_TEXTURE_ARRAY_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/texture/graphics_texture.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Texture Array
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API TextureArray : public Texture
    {
        COFFEE_Resource(TextureArray);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        TextureArray();
        ~TextureArray();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::Prow<basic::Image*, true>& GetImages() const;
        basic::Prow<basic::Image*, true>& GrabImages();

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsValid() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Initialize();
        bool Finalize();
        void Bind(uint32 multi_texture_index = 0);
        void UnBind(uint32 multi_texture_index = 0);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _PlatformInitialize();
        void _PlatformFinalize();
        void _PlatformBind(uint32 multi_texture_index);
        void _PlatformUnBind(uint32 multi_texture_index);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource::Property< basic::Prow< basic::Image*, true > > _Images;
        resource::Property< uint32 > _Index;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, TextureArray);
}
}
#endif
