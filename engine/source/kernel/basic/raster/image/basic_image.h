#ifndef _COFFEE_BASIC_RASTER_IMAGE_H_
#define _COFFEE_BASIC_RASTER_IMAGE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/basic/alpha/basic_alpha.h"
#include "kernel/storage/logical/storage_path.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Image
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Image : public meta::Object
    {
        COFFEE_Type(Image);
        
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Image();
        Image(const Image& image);
        ~Image();

        //-OPERATORS------------------------------------------------------------------------------//

        Image& operator=(const Image& image);

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetWidth() const { return _Width; }
        uint32 GetHeight() const { return _Height; }
        uint32 GetDepth() const { return _Depth; }
        meta::SCALAR_FORMAT GetComponentType() const { return _ComponentType; }
        uint32 GetComponentCount() const { return _ComponentCount; }
        bool IsBGR() const { return _ItIsBGR; }
        const void* GetData() const { return _Data.GetLinearBuffer(); }
        void* GetData() { return _Data.GetLinearBuffer(); }
        
        //-QUERIES--------------------------------------------------------------------------------//

        bool IsEmpty() const;
        uint32 GetComponentSize() const;
        uint32 GetDataSize() const;
        uint32 GetBitsPerPixel() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(uint32 width, uint32 height, uint32 depth, meta::SCALAR_FORMAT component_type,
            uint32 component_count, bool it_is_bgr=false);
        bool Resize(uint32 width, uint32 height, uint32 depth);
        bool SetFrom(const Image& image, bool it_has_to_force_rgb=false);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Width;
        uint32 _Height;
        uint32 _Depth;
        meta::SCALAR_FORMAT _ComponentType;
        uint32 _ComponentCount;
        bool _ItIsBGR;
        Array<uint8> _Data;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Image);
}
}
#endif
