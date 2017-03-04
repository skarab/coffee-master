#ifndef _COFFEE_AUDIO_DEVICE_H_
#define _COFFEE_AUDIO_DEVICE_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/audio/device/config/audio_config.h"
#include "system/audio/sound/audio_sound.h"

namespace coffee
{
namespace audio
{
    //--------------------------------------------------------------------------------------------//
    /// Audio device
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Device
    {
        friend class Sound;

        COFFEE_DeclareSingleton(Device);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Device();
        ~Device();

        //-ACCESSORS------------------------------------------------------------------------------//

        const Config& GetConfig() const { return _Config; }
        Config& GetConfig() { return _Config; }

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsPlayingSound(uint32 id);

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize();
        void Finalize();
        void Update();

        void PlaySound(const storage::Path& path, bool it_is_3d=false, real pitch=1.0f, real gain=1.0f,
            const basic::Vector3& position=basic::Vector3::Zero);
        void StopSound(const storage::Path& path);

        Sound* PlayCustomSound(bool it_is_3d=false, real pitch=1.0f, real gain=1.0f,
            const basic::Vector3& position=basic::Vector3::Zero, uint32 id=NONE);
        void SetCustomSoundPosition(uint32 id, const basic::Vector3& position);

        void SetListenerPosition(const basic::Vector3& position);
        void SetListenerVelocity(const basic::Vector3& velocity);
        void SetListenerRotation(const basic::Quaternion& rotation);

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        real _ComputeSoundVolume(const Sound& sound) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RequestPlay(Sound* sound);
        void _RequestStop(Sound* sound);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Config _Config;
        uint32 _Version;

        basic::Vector3 _ListenerPosition;
        basic::Vector3 _ListenerVelocity;
        basic::Quaternion _ListenerRotation;

        ALCdevice* _Device;
        ALCcontext* _Context;
        
        struct _Buffer
        {
            ALuint _Id;
            Sound* _Sound;

            bool operator ==(const _Buffer& other) const { return false; }
        };

        basic::Array<_Buffer> _Buffers;
        basic::Prow<Sound*, false> _WaitingSounds;

        class _Sound
        {
        public:

            _Sound() : Status(0), ItIs3D(false), Pitch(1.0f), Gain(1.0f), ID(0) {}
            ~_Sound() {}
            bool operator ==(const _Sound& other) const { return false; }
            
            Sound Instance;
            uint32 Status;
            bool ItIs3D;
            real Pitch;
            real Gain;
            uint32 ID;
        };

        shell::Mutex _SoundsMutex;
        basic::Prow<_Sound*, true> _Sounds;
    };
}
}
#endif
