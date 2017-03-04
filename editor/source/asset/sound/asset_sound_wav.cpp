#include "asset/sound/asset_sound_wav.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::SoundWAV);
        COFFEE_Ancestor(asset::Importer);
        COFFEE_Attribute(bool, _ItIs3D, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(bool, _ItIsLooping, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _Pitch, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(real, _Gain, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SoundWAV::SoundWAV() :
        _ItIs3D(true),
        _ItIsLooping(false),
        _Pitch(1.0f),
        _Gain(1.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    SoundWAV::~SoundWAV()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool SoundWAV::IsSupporting(const basic::String& file_extension)
    {
        return file_extension=="wav";
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool SoundWAV::Import()
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

        
        char xbuffer[5];
        xbuffer[4] = '\0';
        if (!stream.Pop(xbuffer, 4) || strcmp(xbuffer, "RIFF")!=0)
            return false;

        stream.Pop(4);

        if (!stream.Pop(xbuffer, 4) || strcmp(xbuffer, "WAVE")!=0)
            return false;

        if (!stream.Pop(xbuffer, 4) || strcmp(xbuffer, "fmt ")!=0)
            return false;

        stream.Pop(4);
        int16 audioFormat = *(int16*)stream.Pop(2);
        int16 channels = *(int16*)stream.Pop(2);
        int32 sampleRate = *(int32*)stream.Pop(4);
        int32 byteRate = *(int32*)stream.Pop(4);
        stream.Pop(2);
        int16 bitsPerSample = *(int16*)stream.Pop(2);

        /*
        if (audioFormat!=16)
        {
            int16 extraParams = *(int16*)stream.Pop(2);
            stream.Pop(extraParams);
        }*/

        if (!stream.Pop(xbuffer, 4) || strcmp(xbuffer, "data")!=0)
            return false;

        int32 dataChunkSize = *(int32*)stream.Pop(4);
        uint8* bufferData = (uint8*)COFFEE_Allocate(dataChunkSize);
        if (!stream.Pop(bufferData, dataChunkSize))
        {
            COFFEE_Free(bufferData);
            return false;
        }

        real duration = real(dataChunkSize)/byteRate;
        
        storage::Path file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + ".sound";
        
        audio::Sound* sound;
        sound = COFFEE_New(audio::Sound);

        sound->SetIs3D(_ItIs3D);
        sound->SetIsLooping(_ItIsLooping);
        sound->SetPitch(_Pitch);
        sound->SetGain(_Gain);

        sound->_Create(duration, channels, byteRate, sampleRate, bitsPerSample, 
            bufferData, dataChunkSize, false);
        COFFEE_Free(bufferData);
            
        sound->Initialize();
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
