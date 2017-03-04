#include "system/audio/sound/audio_sound.h"
#include "system/audio/device/audio_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginResource(audio, Sound, "Sound", "sound", 0);
        COFFEE_Ancestor(resource::Object);
        COFFEE_ResourceProperty(bool, _ItIs3D, meta::MODE_Serializeable | meta::MODE_Editable, resource::PROPERTY_FLAG_Instantiable | resource::PROPERTY_FLAG_AutoInstantiate);
        COFFEE_ResourceProperty(bool, _ItIsLooping, meta::MODE_Serializeable | meta::MODE_Editable, resource::PROPERTY_FLAG_Instantiable);
        COFFEE_ResourceProperty(real, _Pitch, meta::MODE_Serializeable | meta::MODE_Editable, resource::PROPERTY_FLAG_Instantiable | resource::PROPERTY_FLAG_AutoInstantiate);
        COFFEE_ResourceProperty(real, _Gain, meta::MODE_Serializeable | meta::MODE_Editable, resource::PROPERTY_FLAG_Instantiable | resource::PROPERTY_FLAG_AutoInstantiate);
        COFFEE_ResourceProperty(real, _Duration, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_ReadOnly, 0);
        COFFEE_ResourceProperty(uint32, _Channels, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_ReadOnly, 0);
        COFFEE_ResourceProperty(uint32, _ByteRate, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_ReadOnly, 0);
        COFFEE_ResourceProperty(uint32, _SampleRate, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_ReadOnly, 0);
        COFFEE_ResourceProperty(uint32, _BitsPerSample, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_ReadOnly, 0);
        COFFEE_ResourceProperty(< uint8 >, _Data, meta::MODE_Serializeable, 0);
        COFFEE_ResourceProperty(bool, _ItIsCompressed, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_ReadOnly, 0);
        COFFEE_ResourceProperty(< uint8 >, _CompressedData, meta::MODE_Serializeable, 0);
    COFFEE_EndResource();

namespace audio
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    static inline ALenum _GetFormatFromInfo(uint16 channels, uint16 bits_per_sample)
    {
        if (bits_per_sample==8)
        {
            if (channels==1)
                return AL_FORMAT_MONO8;
            else if (channels==2)
                return AL_FORMAT_STEREO8;
        }
        else if (bits_per_sample==16)
        {
            if (channels==1)
                return AL_FORMAT_MONO16;
            else if (channels == 2)
                return AL_FORMAT_STEREO16;
        }

        if (channels==1)
            return AL_FORMAT_MONO16;
        return AL_FORMAT_STEREO16;
    }

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Sound::Sound() :
        _ItIs3D(true),
        _ItIsLooping(false),
        _Pitch(1.0f),
        _Gain(1.0f),
        _Channels(0),
        _ByteRate(0),
        _SampleRate(0),
        _BitsPerSample(0),
        _ItIsPlaying(false),
        _ItIsCompressed(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Sound::~Sound()
    {
        _Destroy();
    }

    //-ACCESSORS------------------------------------------------------------------------------//

    void Sound::SetIs3D(bool it_is_3d)
    {
        _ItIs3D.Set(it_is_3d);
        alSourcei(_Source, AL_SOURCE_RELATIVE, it_is_3d?AL_FALSE:AL_TRUE);
        if (!it_is_3d)
        {
            SetPosition(basic::Vector3());
            SetVelocity(basic::Vector3());
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Sound::SetIsLooping(bool it_is_looping)
    {
        _ItIsLooping.Set(it_is_looping);
        alSourcei(_Source, AL_LOOPING, it_is_looping?AL_TRUE:AL_FALSE);
    }

    //--------------------------------------------------------------------------------------------//

    void Sound::SetPitch(real pitch)
    {
        _Pitch.Set(pitch);
        alSourcef(_Source, AL_PITCH, _Pitch.Get());
    }

    //--------------------------------------------------------------------------------------------//

    void Sound::SetGain(real gain)
    {
        _Gain.Set(gain);
        alSourcef(_Source, AL_GAIN, _Gain.Get());
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Sound::Initialize()
    {
        if (_ItIsCompressed.Get())
        {
            // TODO: having already decompressed happens when using reload in the editor
            _Data.Grab().Erase();

            _Decompress();
        }
        return true;
    }
     
    //--------------------------------------------------------------------------------------------//

    bool Sound::Finalize()
    {
        if (_ItIsCompressed.Get())
            _Data.Grab().Erase();
        return true;
    }
     
    //--------------------------------------------------------------------------------------------//

    bool Sound::InitializeInstance()
    {
        if (Device::IsInstantiated())
        {
            alGenSources(1, &_Source);
            
            SetIs3D(_ItIs3D.Get());
            SetIsLooping(_ItIsLooping.Get());
            SetPitch(_Pitch.Get());
            SetGain(_Gain.Get());
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Sound::FinalizeInstance()
    {
        if (Device::IsInstantiated())
        {
            Device::Get()._RequestStop(this);
            alDeleteSources(1, &_Source);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Sound::Play()
    {
        Device::Get()._RequestPlay(this);
    }

    //--------------------------------------------------------------------------------------------//

    void Sound::Pause()
    {
        if (_ItIsPlaying)
        {
            alSourcePause(_Source);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Sound::Rewind()
    {
        if (_ItIsPlaying)
        {
            alSourceRewind(_Source);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Sound::Stop()
    {
        Device::Get()._RequestStop(this);
    }

    //--------------------------------------------------------------------------------------------//

    void Sound::SetPlayTime(real time)
    {
        alSourcei(_Source, AL_BYTE_OFFSET, int32(time*_ByteRate.Get()));
    }
    
    //--------------------------------------------------------------------------------------------//

    real Sound::GetPlayTime()
    {
        int32 byte_offset;
        alGetSourcei(_Source, AL_BYTE_OFFSET, &byte_offset);
        return real(byte_offset)/_ByteRate.Get();
    }

    //--------------------------------------------------------------------------------------------//

    void Sound::SetPosition(const basic::Vector3& position)
    {
        _Position = position;

        if (Is3D())
        {
            alSource3f(_Source, AL_POSITION, position.X, position.Y, position.Z);
            alSourcei(_Source, AL_SOURCE_RELATIVE, AL_FALSE);
        }
        else
        {
            alSource3f(_Source, AL_POSITION, 0.0f, 0.0f, 0.0f);
            alSourcei(_Source, AL_SOURCE_RELATIVE, AL_TRUE);
        }
    }

    //--------------------------------------------------------------------------------------------//
    
    void Sound::SetVelocity(const basic::Vector3& velocity)
    {
        _Velocity = velocity;
        if (Is3D())
        {
            alSource3f(_Source, AL_VELOCITY, velocity.X, velocity.Y, velocity.Z);
        }
        else
        {
            alSource3f(_Source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
        }
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void Sound::OnPropertyModified(const void* prop)
    {
        if (prop==&_ItIs3D.Get()) { SetIs3D(_ItIs3D.Get()); }
        else if (prop==&_ItIsLooping.Get()) { SetIsLooping(_ItIsLooping.Get()); Play(); }
        else if (prop==&_Pitch.Get()) { SetPitch(_Pitch.Get()); }
        else if (prop==&_Gain.Get()) { SetGain(_Gain.Get()); }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
    
    void Sound::_Create(real duration, uint32 channels, uint32 byte_rate, uint32 sample_rate,
        uint32 bits_per_sample, const uint8* data, uint32 size, bool it_is_compressed)
    {
        _Duration.Set(duration);
        _Channels.Set(channels);
        _ByteRate.Set(byte_rate);
        _SampleRate.Set(sample_rate);
        _BitsPerSample.Set(bits_per_sample);
        _ItIsCompressed.Set(it_is_compressed);
        _Data.Grab().Erase();
        _CompressedData.Grab().Erase();

        if (it_is_compressed)
        {
            _CompressedData.Grab().Resize(size);
            COFFEE_Copy(_CompressedData.Grab().GetLinearBuffer(), data, size);
        }
        else
        {
            _Data.Grab().Resize(size);
            COFFEE_Copy(_Data.Grab().GetLinearBuffer(), data, size);
        }
    }

    //-FUNCTIONS----------------------------------------------------------------------------------//
    
    size_t Sound::_DecompressOGG_fread(void* ptr, size_t size, size_t count, void* user_data)
    {
        if (user_data==NULL)
            return 0;
        storage::Stream* stream = (storage::Stream*)user_data;
        if (stream->Pop(ptr, size*count))
            return size*count;
        return 0;
    }

    //--------------------------------------------------------------------------------------------//
    
    int Sound::_DecompressOGG_fseek(void* user_data, ogg_int64_t off, int whence)
    {
        if (user_data==NULL)
            return -1;

        storage::Stream* stream = (storage::Stream*)user_data;

        switch (whence)
        {
            case SEEK_SET:
                if (off>stream->GetSize())
                    return 1;
                stream->Seek((ulong_ptr)off);
                return 0;

            case SEEK_CUR:
                if (stream->GetOffset()+off>stream->GetSize())
                    return 1;
                stream->Seek((ulong_ptr)(stream->GetOffset()+off));
                return 0;
        }
        return 1;
    }

    //--------------------------------------------------------------------------------------------//
    
    int Sound::_DecompressOGG_fclose(void* user_data)
    {
        return 0;
    }

    //--------------------------------------------------------------------------------------------//
    
    long Sound::_DecompressOGG_ftell(void* user_data)
    {
        if (user_data==NULL)
            return -1;
        storage::Stream* stream = (storage::Stream*)user_data;
        return stream->GetOffset();
    }

    //-QUERIES------------------------------------------------------------------------------------//
    
    bool Sound::_HasFinishedPlaying() const
    {
        if (!IsPlaying())
            return false;
        if (IsLooping())
            return false;
        int32 state;
        alGetSourcei(_Source, AL_SOURCE_STATE, &state);
        return state==AL_STOPPED;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
    
    void Sound::_Bind(ALuint buffer_id)
    {
        alBufferData(buffer_id, _GetFormatFromInfo(_Channels.Get(), _BitsPerSample.Get()),
            _Data.Get().GetLinearBuffer(), _Data.Get().GetSize(), _SampleRate.Get());
        alSourcei(_Source, AL_BUFFER, buffer_id);
        SetPosition(_Position);
        SetVelocity(_Velocity);
    }
    
    //--------------------------------------------------------------------------------------------//
    
    void Sound::_UnBind(ALuint buffer_id)
    {
        alSourcei(_Source, AL_BUFFER, 0);        
    }

    //--------------------------------------------------------------------------------------------//
    
    void Sound::_Play()
    {
        alSourcePlay(_Source);
        _ItIsPlaying = true;
    }

    //--------------------------------------------------------------------------------------------//
    
    void Sound::_Stop()
    {
        alSourceStop(_Source);
        _ItIsPlaying = false;
    }

    //--------------------------------------------------------------------------------------------//
    
    void Sound::_Decompress()
    {
        COFFEE_Assert(!IsInstantiated(), core::ERROR_CODE_IncorrectUsage, "Trying to decompress instance");
        COFFEE_Assert(_ItIsCompressed.Get(), core::ERROR_CODE_IncorrectUsage, "Not compressed!");
        COFFEE_Assert(_Data.Get().GetSize()==0, core::ERROR_CODE_IncorrectUsage, "Already decompressed");
        COFFEE_Assert(_CompressedData.Get().GetSize()>0, core::ERROR_CODE_IncorrectUsage, "Not compressed!");

        storage::Data data;
        data.Push(_CompressedData.Get().GetLinearBuffer(), _CompressedData.Get().GetSize());

        storage::Stream stream;
        stream.SetData(&data);

        vorbis_info *pInfo;
        OggVorbis_File oggFile;
        ov_callbacks callbacks = {
            _DecompressOGG_fread, _DecompressOGG_fseek,
            _DecompressOGG_fclose, _DecompressOGG_ftell };
        ov_open_callbacks((void*)&stream, &oggFile, NULL, 0, callbacks);

        pInfo = ov_info(&oggFile, -1);

        char temp[32768];
        long bytes;
        int endian = 0;
        int bitStream;

        do
        {
            bytes = ov_read(&oggFile, temp, 32768, endian, 2, 1, &bitStream);
            ulong offset = _Data.Get().GetSize();
            _Data.Grab().Resize(_Data.Get().GetSize()+bytes);
            COFFEE_Copy((char*)_Data.Grab().GetLinearBuffer()+offset, temp, bytes);
        } while (bytes>0);

        ov_clear(&oggFile);
        stream.PopData();
    }

}
}
