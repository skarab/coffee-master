#include "asset/sound/asset_sound_ogg.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::SoundOGG);
        COFFEE_Ancestor(asset::Importer);
        COFFEE_Attribute(bool, _ItIs3D, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(bool, _ItIsLooping, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _Pitch, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _Gain, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SoundOGG::SoundOGG() :
        _ItIs3D(false),
        _ItIsLooping(false),
        _Pitch(1.0f),
        _Gain(1.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    SoundOGG::~SoundOGG()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool SoundOGG::IsSupporting(const basic::String& file_extension)
    {
        return file_extension=="ogg";
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool SoundOGG::Import()
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

        vorbis_info *pInfo;
        OggVorbis_File oggFile;
        ov_callbacks callbacks = {
            audio::Sound::_DecompressOGG_fread, audio::Sound::_DecompressOGG_fseek,
            audio::Sound::_DecompressOGG_fclose, audio::Sound::_DecompressOGG_ftell };
        ov_open_callbacks((void*)&stream, &oggFile, NULL, 0, callbacks);

        pInfo = ov_info(&oggFile, -1);

        uint32 channels = pInfo->channels;
        uint32 byte_rate = 16*pInfo->rate;
        uint32 sample_rate = pInfo->rate;
        uint32 bits_per_sample = 16;

        char temp[32768];
        long bytes;
        int endian = 0;
        int bitStream;
        ulong size = 0;

        do
        {
            bytes = ov_read(&oggFile, temp, 32768, endian, 2, 1, &bitStream);
            size += bytes;
        } while (bytes>0);

        ov_clear(&oggFile);
        stream.PopData();

        if ((channels!=1 && channels!=2)
            || byte_rate<=0 || sample_rate<=0
            || size<=0)
        {
            return false;
        }

        storage::Path file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + ".sound";
        
        audio::Sound* sound;
        sound = COFFEE_New(audio::Sound);

        sound->SetIs3D(_ItIs3D);
        sound->SetIsLooping(_ItIsLooping);
        sound->SetPitch(_Pitch);
        sound->SetGain(_Gain);

        sound->_Create(size/(real)byte_rate, channels, byte_rate, sample_rate, bits_per_sample, 
            (const uint8*)file_data->GetBuffer(), file_data->GetSize(), true);
            
        sound->PreCreateLOD(0);
        resource::Chunk* resource_chunk;
        resource_chunk = resource::Manager::Get().Create(file_path);
        resource_chunk->AddLOD(*sound);
        
        DeleteImportedResources();
        AddImportedResource(resource_chunk);
        return true;
    }

}
}
