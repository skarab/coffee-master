#ifndef _COFFEE_GRAPHICS_TEXTURE_3D_H_
#define _COFFEE_GRAPHICS_TEXTURE_3D_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/texture/graphics_texture.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Texture3D
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Texture3D : public Texture
    {
        COFFEE_Resource(Texture3D);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Texture3D();
        ~Texture3D();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetImage(basic::Image& image);
        const basic::Image& GetImage() const;
        basic::Image& GrabImage();

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasImage() const;
        bool IsValid() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Initialize();
        bool Finalize();
        void Bind(uint32 multi_texture_index = 0);
        void UnBind(uint32 multi_texture_index = 0);

        void DestroyImage();

    private:

        //-QUERIES------------------------------------------------------------------------------------//

        uint32 _GetInternalType() const;
        uint32 _GetInternalFormat() const;
        uint32 _GetInternalComponentType() const;
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource::Property< basic::Image* > _Image;
        resource::Property< uint32 > _Index;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Texture3D);
}
}
#endif
