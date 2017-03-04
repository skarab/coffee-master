#include "asset/texture/asset_texture_ies.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::TextureIES);
        COFFEE_Ancestor(asset::Importer);
        COFFEE_Attribute(basic::String, _LampType, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_ReadOnly);
        COFFEE_Attribute(basic::String, _Manufacturer, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_ReadOnly);
        COFFEE_Attribute(basic::String, _Measurement, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_ReadOnly);
        COFFEE_Attribute(real, _Exponent, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _Scale, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _Distance, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    TextureIES::TextureIES() :
        _Exponent(1.0f),
        _Scale(1.0f),
        _Distance(0.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    TextureIES::~TextureIES()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool TextureIES::IsSupporting(const basic::String& file_extension)
    {
        return file_extension=="ies";
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool TextureIES::Import()
    {
        storage::Data* file_data = storage::System::Get().GetFileData(GetAssetPath());
        if (file_data==NULL)
            return false;
        if (file_data->GetSize()==0)
        {
            COFFEE_Delete(file_data);
            return false;
        }
        storage::Stream stream;
        stream.SetData(file_data);
        
        basic::String line;
        if (!stream.PopLine(line) || !line.IsPrefixed("IESNA"))
            return false;

        _LampType = "";
        _Manufacturer = "";
        _Measurement = "";

        while(stream.PopLine(line) && !line.IsPrefixed("TILT=NONE"))
        {
            if (line.IsPrefixed("[MANUFAC]"))
            {
                _Manufacturer = line.GetRight(line.GetLength()-strlen("[MANUFAC] "));
            }
            else if (line.IsPrefixed("[TEST]"))
            {
                _Measurement = line.GetRight(line.GetLength()-strlen("[TEST] "));
            }
            else if (line.IsPrefixed("[LAMP]"))
            {
                _LampType = line.GetRight(line.GetLength()-strlen("[LAMP] "));
            }
            else if (_LampType.IsEmpty() && line.IsPrefixed("[LUMINAIRE]"))
            {
                _LampType = line.GetRight(line.GetLength()-strlen("[LUMINAIRE] "));
            }
            else if (_LampType.IsEmpty() && line.IsPrefixed("[LAMPS]"))
            {
                _LampType = line.GetRight(line.GetLength()-strlen("[LUMINAIRE] "));
            }
        }

        if (_LampType.IsEmpty())
            _LampType = "Unknown";
        if (_Manufacturer.IsEmpty())
            _Manufacturer = "Unknown";
        if (_Measurement.IsEmpty())
            _Measurement = "Unknown";        
        
        if (stream.IsOver())
            return false;

        basic::String word;
        
        int32 rated_lumens;
        int32 multiply_factor;
        int32 vertical_angle_count;
        int32 horizontal_angle_count;
        int32 unit_type;
        real luminous_width;
        real luminous_length;
        real luminous_height;

        if (!stream.PopWord(word)) return false;
        // unknown

        if (!stream.PopWord(word)) return false;
        rated_lumens = word.GetInteger();

        if (!stream.PopWord(word)) return false;
        multiply_factor = word.GetInteger();

        if (!stream.PopWord(word)) return false;
        vertical_angle_count = word.GetInteger();

        if (!stream.PopWord(word)) return false;
        horizontal_angle_count = word.GetInteger();
        if (horizontal_angle_count==0)
        {
            COFFEE_Log(core::Log::None, "This IES lamp type isn't supported for now.");
            return false;
        }        

        if (!stream.PopWord(word)) return false;
        // unknown

        if (!stream.PopWord(word)) return false;
        unit_type = word.GetInteger();

        if (!stream.PopWord(word)) return false;
        luminous_width = word.GetReal();

        if (!stream.PopWord(word)) return false;
        luminous_length = word.GetReal();

        if (!stream.PopWord(word)) return false;
        luminous_height = word.GetReal();

        if (!stream.PopWord(word)) return false;
        if (!stream.PopWord(word)) return false;
        if (!stream.PopWord(word)) return false;
        // 3 unknowns

        _VerticalAngles.Resize(vertical_angle_count);
        for (int32 i=0 ; i<vertical_angle_count ; ++i)
        {
            if (!stream.PopWord(word)) return false;
            _VerticalAngles[i] = word.GetInteger();
        }
        
        basic::Array<int32> horizontal_angles;
        horizontal_angles.Resize(horizontal_angle_count);
        for (int32 i=0 ; i<horizontal_angle_count ; ++i)
        {
            if (!stream.PopWord(word)) return false;
            horizontal_angles[i] = word.GetInteger();
        }

        _SymmetryType = horizontal_angles[horizontal_angles.GetSize()-1];

       
        _MinimumCandela = 999999;
        _MaximumCandela = 0;
        _CandelaValues.Resize(vertical_angle_count*horizontal_angle_count);
        
        for (uint32 i=0 ; i<_CandelaValues.GetSize() ; ++i)
        {
            if (!stream.PopWord(word)) return false;
            _CandelaValues[i] = word.GetInteger();
            
            if (_CandelaValues[i]>_MaximumCandela)
                _MaximumCandela = _CandelaValues[i];
            if (_CandelaValues[i]<_MinimumCandela)
                _MinimumCandela = _CandelaValues[i];
        }

        storage::Path file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + ".texture";
        
        basic::Image* image = COFFEE_New(basic::Image);
        image->Create(512, 512, 1, meta::SCALAR_FORMAT_UInt16, 1);
        
        uint16* buffer = (uint16*)image->GetData();
        basic::Vector2 position;
        for (uint32 y=0 ; y<image->GetHeight() ; ++y)
        {
            for (uint32 x=0 ; x<image->GetWidth() ; ++x)
            {
                position.X = x*2.0f/image->GetWidth()-1.0f;
                position.Y = y*2.0f/image->GetHeight()-1.0f;
                *buffer = (uint16)(_ComputeIESValue(position)*65535.0f);
                ++buffer;
            }
        }
        
        DeleteImportedResources();
        AddThumbnail(Manager::Get().GenerateThumbnail(GetImportPath(), *image));
        AddThumbnail(Manager::Get().GenerateThumbnail(file_path, *image));

        graphics::Texture2D* texture;
        texture = COFFEE_New(graphics::Texture2D);
        texture->SetImage(*image);
        texture->SetParameters(graphics::TEXTURE_PARAMETER_BilinearFiltering
            | graphics::TEXTURE_PARAMETER_AnisotropicFiltering
            | graphics::TEXTURE_PARAMETER_Clamp
            | graphics::TEXTURE_PARAMETER_LinearSpace);
        texture->Initialize();
        texture->PreCreateLOD(0);
        resource::Chunk* resource_chunk;
        resource_chunk = resource::Manager::Get().Create(file_path);
        resource_chunk->AddLOD(*texture);
        
        AddImportedResource(resource_chunk);

        return true;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    real TextureIES::_ComputeIESValue(const basic::Vector2& position) const
    {
        real angle;
        uint32 first_index, second_index;
        real percentage;
        real candela;
        real distance;
        real ies_value;
        basic::Vector2 vect;

        vect = position;
        if (!vect.IsZero())
            vect.Normalize();

        switch (_SymmetryType)
        {
            case 0:
            case 360:
                angle = acos(-vect.Y);
                break;

            case 90:
                angle = acos(-vect.Y);
                //angle = acos(-abs(vect.Y));
                break;

            default:
                angle = acos(-vect.Y);                
                if (position.X<0.0f)
                    angle = 2.0f*Pi-angle;
                break;
        } 

        angle *= 180.0f/Pi;

        if (!_FindNearestVerticalAngleIndex(first_index, second_index, angle))
            return 0.0f;
        
        if (_VerticalAngles[second_index]-_VerticalAngles[first_index]==0)
        {
            percentage = 0.0f;
        }
        else
        {
            percentage = (angle-_VerticalAngles[first_index])/(_VerticalAngles[second_index]-_VerticalAngles[first_index]);
        }

        candela = _CandelaValues[first_index]+(_CandelaValues[second_index]-_CandelaValues[first_index])*percentage;
        //candela = (candela-_MinimumCandela)/(_MaximumCandela-_MinimumCandela);
        candela = candela/_MaximumCandela;

        distance = position.GetNorm()-_Distance;
        if (!IsEqual(_Scale, 0.0f))
            distance *= 1.0f/_Scale;
        distance = pow(1.0f-distance, _Exponent);

        ies_value = distance*candela;
        Clamp(ies_value, 0.0f, 1.0f);
        return ies_value;
    }

    //--------------------------------------------------------------------------------------------//

    bool TextureIES::_FindNearestVerticalAngleIndex(uint32& first_index, uint32& second_index, real angle) const
    {
        for (uint32 i=0 ; i<_VerticalAngles.GetSize() ; ++i)
        {
            if (_VerticalAngles[i]>=angle)
            {
                second_index = i;

                if (i==0)
                {
                    first_index = i;
                }
                else
                {
                    first_index = i-1;
                }
                return true;
            }
        }
        return false;
    }

}
}
