#include "kernel/basic/raster/image/basic_image.h"
#include "kernel/core/core.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Image);
        COFFEE_Attribute(uint32, _Width, meta::MODE_Serializeable);
        COFFEE_Attribute(uint32, _Height, meta::MODE_Serializeable);
        COFFEE_Attribute(uint32, _Depth, meta::MODE_Serializeable);
        COFFEE_Attribute(uint32, _ComponentType, meta::MODE_Serializeable);
        COFFEE_Attribute(uint32, _ComponentCount, meta::MODE_Serializeable);
        COFFEE_Attribute(bool, _ItIsBGR, meta::MODE_Serializeable);
        COFFEE_Attribute(<uint8>, _Data, meta::MODE_Serializeable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Image::Image() :
        _Width(0),
        _Height(0),
        _Depth(1),
        _ComponentType(meta::SCALAR_FORMAT_UInt8),
        _ComponentCount(0),
        _ItIsBGR(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Image::Image(const Image& image) :
        _Width(0),
        _Height(0),
        _Depth(1),
        _ComponentType(meta::SCALAR_FORMAT_UInt8),
        _ComponentCount(0),
        _ItIsBGR(false)
    {
        SetFrom(image);
    }

    //--------------------------------------------------------------------------------------------//

    Image::~Image()
    {
    }

    //-OPERATORS------------------------------------------------------------------------------//

    Image& Image::operator=(const Image& image)
    {
        SetFrom(image);
        return *this;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Image::IsEmpty() const
    {
        return _Data.GetSize()==0
            || _Width==0
            || _Height==0
            || _Depth==0
            || _ComponentCount==0;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Image::GetComponentSize() const
    {
        return (uint32)meta::SCALAR_FORMAT_GetFormatSize(_ComponentType);
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Image::GetDataSize() const
    {
        return _Width*_Height*_Depth*_ComponentCount*GetComponentSize();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Image::Create(uint32 width, uint32 height, uint32 depth, meta::SCALAR_FORMAT component_type,
        uint32 component_count, bool it_is_bgr)
    {
        _Width = width;
        _Height = height;
        _Depth = depth;
        _ComponentType = component_type;
        _ComponentCount = component_count;
        _ItIsBGR = it_is_bgr;
        _Data.Erase();
        _Data.Resize(GetDataSize());
    }

    //--------------------------------------------------------------------------------------------//

    bool Image::Resize(uint32 width, uint32 height, uint32 depth)
    {
        if (IsEmpty())
            return false;
        
        if(_Width==width && _Height==height && _Depth==depth)
            return true;

        Array<uint8> old_data = _Data;
        uint32 old_width = _Width;
        uint32 old_height = _Height;
        uint32 old_depth = _Depth;
        
        Create(width, height, depth, _ComponentType, _ComponentCount, _ItIsBGR);

        for (uint32 output_depth=0 ; output_depth<GetDepth() ; ++output_depth)
        {
            for (uint32 output_height=0 ; output_height<GetHeight() ; ++output_height)
            {
                for (uint32 output_width=0 ; output_width<GetWidth() ; ++output_width)
                {
                    uint32 input_width = output_width*(old_width-1)/(GetWidth()-1);
                    uint32 input_height = output_height*(old_height-1)/(GetHeight()-1);
                    uint32 input_depth = output_depth*(old_depth-1)/(GetDepth()-1);

                    COFFEE_Copy(
                        (uint8*) _Data.GetLinearBuffer() + (output_depth*GetWidth()*GetHeight()+(output_height*GetWidth()+output_width)) * GetComponentCount() * GetComponentSize(),
                        (uint8*) old_data.GetLinearBuffer() + (input_depth*old_width*old_height+(input_height * old_width + input_width)) * GetComponentCount() * GetComponentSize(),
                        GetComponentCount() * GetComponentSize());
                }
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Image::SetFrom(const Image& image, bool it_has_to_force_rgb)
    {
        if (it_has_to_force_rgb)
        {
            Create(image._Width, image._Height, image._Depth, meta::SCALAR_FORMAT_UInt8, 3, image._ItIsBGR);
        }
        else
        {
            Create(image._Width, image._Height, image._Depth, image._ComponentType, image._ComponentCount, image._ItIsBGR);
        }

        if (it_has_to_force_rgb)
        {
            COFFEE_Assert(image.GetComponentType()==meta::SCALAR_FORMAT_UInt8
                || image.GetComponentType()==meta::SCALAR_FORMAT_UInt16
                || image.GetComponentType()==meta::SCALAR_FORMAT_Real,
                core::ERROR_CODE_Unimplemented, "Unsupported image format");

            uint32 x_index;
            uint32 y_index;
            uint32 z_index;
            uint8 red, green, blue, alpha;
            real alpha_mask;
            uint8 * output_buffer;

            const uint8* input_buffer8 = (const uint8*) image.GetData();
            const uint16* input_buffer16 = (const uint16*) image.GetData();
            const real* input_bufferR = (const real*) image.GetData();
            output_buffer = (uint8 *) GetData();

            for (z_index=0 ; z_index<GetDepth() ; ++z_index)
            {
                for (y_index=0 ; y_index<GetHeight() ; ++y_index)
                {
                    for (x_index=0 ; x_index<GetWidth() ; ++x_index)
                    {
                        uint32 p = (z_index*image.GetWidth()*image.GetHeight()+(y_index * image.GetWidth() + x_index))* image.GetComponentCount();
                        
                        switch (image.GetComponentCount())
                        {
                            case 1:
                                if (image.GetComponentType()==meta::SCALAR_FORMAT_UInt8)
                                {
                                    red = input_buffer8[p];
                                }
                                else if (image.GetComponentType()==meta::SCALAR_FORMAT_UInt16)
                                {
                                    red = (uint8)(((uint32)input_buffer16[p])*255/65535);
                                }
                                else if (image.GetComponentType()==meta::SCALAR_FORMAT_Real)
                                {
                                    red = (uint8)(input_bufferR[p]/255.0f);
                                }
                                green = red;
                                blue = red;
                                break;

                            case 2:
                                if (image.GetComponentType()==meta::SCALAR_FORMAT_UInt8)
                                {
                                    red = input_buffer8[p];
                                    green = input_buffer8[p+1];
                                }
                                else if (image.GetComponentType()==meta::SCALAR_FORMAT_UInt16)
                                {
                                    red = (uint8)(((uint32)input_buffer16[p])*255/65535);
                                    green = (uint8)(((uint32)input_buffer16[p+1])*255/65535);
                                }
                                else if (image.GetComponentType()==meta::SCALAR_FORMAT_Real)
                                {
                                    red = (uint8)(input_bufferR[p]/255.0f);
                                    green = (uint8)(input_bufferR[p+1]/255.0f);
                                }
                                blue = 255;
                                break;

                            case 4:
                                if (image.GetComponentType()==meta::SCALAR_FORMAT_UInt8)
                                {
                                    red = input_buffer8[p];
                                    green = input_buffer8[p+1];
                                    blue = input_buffer8[p+2];
                                    alpha = input_buffer8[p+3];
                                }
                                else if (image.GetComponentType()==meta::SCALAR_FORMAT_UInt16)
                                {
                                    red = (uint8)(((uint32)input_buffer16[p])*255/65535);
                                    green = (uint8)(((uint32)input_buffer16[p+1])*255/65535);
                                    blue = (uint8)(((uint32)input_buffer16[p+2])*255/65535);
                                    alpha = (uint8)(((uint32)input_buffer16[p+3])*255/65535);
                                }
                                else if (image.GetComponentType()==meta::SCALAR_FORMAT_Real)
                                {
                                    red = (uint8)(input_bufferR[p]/255.0f);
                                    green = (uint8)(input_bufferR[p+1]/255.0f);
                                    blue = (uint8)(input_bufferR[p+2]/255.0f);
                                    alpha = (uint8)(input_bufferR[p+3]/255.0f);
                                }
                                alpha_mask = (255.0f - alpha) * ((x_index + y_index) % 2) / 2.0f;
                                red = (uint8)((red / 255.0f) * alpha + alpha_mask*0.31f);
                                green = (uint8)((green / 255.0f) * alpha + alpha_mask*0.53f);
                                blue = (uint8)((blue / 255.0f) * alpha + alpha_mask*0.51f);
                                break;

                            default:
                                if (image.GetComponentType()==meta::SCALAR_FORMAT_UInt8)
                                {
                                    red = input_buffer8[p];
                                    green = input_buffer8[p+1];
                                    blue = input_buffer8[p+2];
                                }
                                else if (image.GetComponentType()==meta::SCALAR_FORMAT_UInt16)
                                {
                                    red = (uint8)(((uint32)input_buffer16[p])*255/65535);
                                    green = (uint8)(((uint32)input_buffer16[p+1])*255/65535);
                                    blue = (uint8)(((uint32)input_buffer16[p+2])*255/65535);
                                }
                                else if (image.GetComponentType()==meta::SCALAR_FORMAT_Real)
                                {
                                    red = (uint8)(input_bufferR[p]/255.0f);
                                    green = (uint8)(input_bufferR[p+1]/255.0f);
                                    blue = (uint8)(input_bufferR[p+2]/255.0f);
                                }
                                break;
                        }

                        uint32 po = (z_index*GetWidth()*GetHeight()+(y_index*GetWidth()+x_index)*3)*3;
                        output_buffer[po] = red;
                        output_buffer[po+1] = green;
                        output_buffer[po+2] = blue;
                    }
                }
            }
        }
        else
        {
            COFFEE_Copy(GetData(), image.GetData(), image.GetDataSize());
        }

        return true;
    }

}
}
