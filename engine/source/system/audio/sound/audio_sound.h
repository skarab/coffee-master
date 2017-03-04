#ifndef _COFFEE_AUDIO_SOUND_H_
#define _COFFEE_AUDIO_SOUND_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/resource/resources.h"

namespace coffee
{
namespace audio
{
    class Device;

    //--------------------------------------------------------------------------------------------//
    /// Sound
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Sound : public resource::Object
    {
        friend class Device;

        COFFEE_Resource(Sound);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Sound();
        ~Sound();

        //-ACCESSORS------------------------------------------------------------------------------//

        bool IsPlaying() const { return _ItIsPlaying; }
        void SetIs3D(bool it_is_3d);
        bool Is3D() const { return _ItIs3D.Get(); }
        void SetIsLooping(bool it_is_looping);
        bool IsLooping() const { return _ItIsLooping.Get(); }
        void SetPitch(real pitch);
        real GetPitch() const { return _Pitch.Get(); }
        void SetGain(real gain);
        real GetGain() const { return _Gain.Get(); }
        const basic::Vector3& GetPosition() const { return _Position; }
        const basic::Vector3& GetVelocity() const { return _Velocity; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Initialize();
        bool Finalize();
        bool InitializeInstance();
        bool FinalizeInstance();
        
        void Play();
        void Pause();
        void Rewind();
        void Stop();
        void SetPlayTime(real time);
        real GetPlayTime();

        void SetPosition(const basic::Vector3& position);
        void SetVelocity(const basic::Vector3& velocity);
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnPropertyModified(const void* prop);

    //protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Create(real duration, uint32 channels, uint32 byte_rate, uint32 sample_rate,
            uint32 bits_per_sample, const uint8* data, uint32 size, bool it_is_compressed);

        //-FUNCTIONS------------------------------------------------------------------------------//

        static size_t _DecompressOGG_fread(void* ptr, size_t size, size_t count, void* user_data);
        static int _DecompressOGG_fseek(void* user_data, ogg_int64_t off, int whence);
        static int _DecompressOGG_fclose(void* user_data);
        static long _DecompressOGG_ftell(void* user_data);

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        bool _HasFinishedPlaying() const;
    
        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Bind(ALuint buffer_id);
        void _UnBind(ALuint buffer_id);
        void _Play();
        void _Stop();
        void _Decompress();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIsPlaying;
        ALuint _Source;

        resource::Property< bool > _ItIs3D;
        resource::Property< bool > _ItIsLooping;
        resource::Property< real > _Pitch;
        resource::Property< real > _Gain;

        basic::Vector3 _Position;
        basic::Vector3 _Velocity;

        resource::Property< real > _Duration;
        resource::Property< uint32 > _Channels;
        resource::Property< uint32 > _ByteRate;
        resource::Property< uint32 > _SampleRate;
        resource::Property< uint32 > _BitsPerSample;
        resource::Property< basic::Array< uint8 > > _Data;

        resource::Property< bool > _ItIsCompressed;
        resource::Property< basic::Array< uint8 > > _CompressedData;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Sound);
}
}
#endif
