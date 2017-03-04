#include "system/audio/device/audio_device.h"

namespace coffee
{
namespace audio
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(Device);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Device::Device()
    {
        COFFEE_CreateSingleton(Device);
    }

    //--------------------------------------------------------------------------------------------//

    Device::~Device()
    {
        COFFEE_DestroySingleton(Device);
    }

    //-QUERIES--------------------------------------------------------------------------------//

    bool Device::IsPlayingSound(uint32 id)
    {
        shell::Locker lock(_SoundsMutex);
        for (uint32 i=0 ; i<_Sounds.GetSize() ; ++i)
        {
            if (_Sounds[i]->ID==id)
                return true;
        }
        return false;
    }
    
    //-OPERATIONS---------------------------------------------------------------------------------//

    void Device::Initialize()
    {
        _Device = NULL;
        _Context = NULL;

        _Device = alcOpenDevice(NULL);
        if (_Device!=NULL)
        {
            _Context = alcCreateContext(_Device, NULL);
        
            if (_Context!=NULL)
            {
                alcMakeContextCurrent(_Context);

                _Buffers.Resize(128);
                for (uint32 i=0 ; i<_Buffers.GetSize() ; ++i)
                {
                    alGenBuffers(1, &_Buffers[i]._Id);
                    _Buffers[i]._Sound = NULL;
                }

                SetListenerPosition(basic::Vector3());
                SetListenerVelocity(basic::Vector3());
                SetListenerRotation(basic::Euler());
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Device::Finalize()
    {
        // Finalize custom sounds if required
        for (uint32 i=0 ; i<_Sounds.GetSize() ; ++i)
        {
            if (!_Sounds[i]->Instance.IsInstantiated())
                _Sounds[i]->Instance.FinalizeInstance();
        }
        _Sounds.Erase();

        COFFEE_Assert(_WaitingSounds.GetSize()==0, core::ERROR_CODE_Unexpected, "All sounds should be destroyed at this point");
        
        if (_Device!=NULL && _Context!=NULL)
        {
            for (uint32 i=0 ; i<_Buffers.GetSize() ; ++i)
            {
                COFFEE_Assert(_Buffers[i]._Sound==NULL, core::ERROR_CODE_Unexpected, "All sounds should be destroyed at this point");
                alDeleteBuffers(1, &_Buffers[i]._Id);
            }

            alcDestroyContext(_Context);
        }

        if (_Device!=NULL)
            alcCloseDevice(_Device);
    }

    //--------------------------------------------------------------------------------------------//

    void Device::Update()
    {
        for (uint32 i=0 ; i<_Buffers.GetSize() ; ++i)
        {
            if (_Buffers[i]._Sound!=NULL && _Buffers[i]._Sound->_HasFinishedPlaying())
                _Buffers[i]._Sound->Stop();
        }

        for (int32 i=(int32)_WaitingSounds.GetSize()-1 ; i>=0 ; --i)
        {
            // Find if there is a free buffer, using priorities as well
            uint32 buffer_index = NONE;
            real volume = _ComputeSoundVolume(*_WaitingSounds[i]);
            real minimum_volume = volume*0.9f;
            uint32 minimum_id = NONE;
            for (uint32 j=0 ; j<_Buffers.GetSize() ; ++j)
            {
                if (_Buffers[j]._Sound==NULL)
                {
                    buffer_index = j;
                    break;
                }

                real vol = _ComputeSoundVolume(*_Buffers[j]._Sound);
                if (vol<minimum_volume)
                {
                    minimum_id = j;
                    minimum_volume = vol;
                }
            }
            
            if (buffer_index==NONE && minimum_id!=NONE)
            {
                buffer_index = minimum_id;
            
                Sound* sound = _Buffers[buffer_index]._Sound; 
                bool it_was_playing = sound->IsPlaying();
                sound->Stop();
                if (it_was_playing && sound->IsLooping())
                    _WaitingSounds.AddItem(sound);
                _Buffers[buffer_index]._Sound = NULL;
            }

            if (buffer_index!=NONE)
            {
                if (_Buffers[buffer_index]._Sound==NULL)
                {
                    _Buffers[buffer_index]._Sound = _WaitingSounds[i];
                    _WaitingSounds[i]->_Bind(_Buffers[buffer_index]._Id);
                }

                _WaitingSounds[i]->_Play();
                _WaitingSounds.Remove(i);
            }
        }

        shell::Locker lock(_SoundsMutex);
        for (int32 i=(int32)_Sounds.GetSize()-1 ; i>=0 ; --i)
        {
            if (_Sounds[i]->Status==0)
            {
                if (_Sounds[i]->Instance.IsAvailable())
                {
                    _Sounds[i]->Instance.SetIs3D(_Sounds[i]->ItIs3D);
                    _Sounds[i]->Instance.SetPitch(_Sounds[i]->Pitch);
                    _Sounds[i]->Instance.SetGain(_Sounds[i]->Gain);

                    _WaitingSounds.AddItem(&_Sounds[i]->Instance);
                    _Sounds[i]->Status = 1;
                }
                else if (_Sounds[i]->Instance.IsInvalid())
                {
                    _Sounds.Remove(i);
                }
            }
            else if (_Sounds[i]->Status==2)
            {
                // Finalize custom sound if required
                if (!_Sounds[i]->Instance.IsInstantiated())
                    _Sounds[i]->Instance.FinalizeInstance();

                _Sounds.Remove(i);
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Device::PlaySound(const storage::Path& path, bool it_is_3d, real pitch, real gain,
        const basic::Vector3& position)
    {
        _Sound* sound = COFFEE_New(_Sound);
        sound->Instance = resource::Manager::Get().Load(path);
        sound->Instance.SetPosition(position);
        sound->ItIs3D = it_is_3d;
        sound->Pitch = pitch;
        sound->Gain = gain;
        sound->ID = NONE;

        shell::Locker lock(_SoundsMutex);
        _Sounds.AddItem(sound);
    }

    //--------------------------------------------------------------------------------------------//

    void Device::StopSound(const storage::Path& path)
    {
        shell::Locker lock(_SoundsMutex);
        for (uint32 i=0 ; i<_Sounds.GetSize() ; ++i)
        {
            if (_Sounds[i]->Instance.GetFilePath()==path)
            {
                _Sounds[i]->Status = 2;
                break;
            }
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    Sound* Device::PlayCustomSound(bool it_is_3d, real pitch, real gain,
        const basic::Vector3& position, uint32 id)
    {
        _Sound* sound = COFFEE_New(_Sound);
        sound->Instance.SetPosition(position);
        sound->ItIs3D = it_is_3d;
        sound->Pitch = pitch;
        sound->Gain = gain;
        sound->ID = id;

        shell::Locker lock(_SoundsMutex);
        _Sounds.AddItem(sound);
        return &sound->Instance;
    }

    //--------------------------------------------------------------------------------------------//

    void Device::SetCustomSoundPosition(uint32 id, const basic::Vector3& position)
    {
        for (uint32 i=0 ; i<_Sounds.GetSize() ; ++i)
        {
            if (_Sounds[i]->ID==id)
                _Sounds[i]->Instance.SetPosition(position);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Device::SetListenerPosition(const basic::Vector3& position)
    {
        _ListenerPosition = position;
        alListener3f(AL_POSITION, position.X, position.Y, position.Z);
    }
    
    //--------------------------------------------------------------------------------------------//

    void Device::SetListenerVelocity(const basic::Vector3& velocity)
    {
        _ListenerVelocity = velocity;
        alListener3f(AL_VELOCITY, velocity.X, velocity.Y, velocity.Z);
    }
    
    //--------------------------------------------------------------------------------------------//

    void Device::SetListenerRotation(const basic::Quaternion& rotation)
    {
        _ListenerRotation = rotation;
        basic::Vector3 zaxis = rotation.GetZAxis();
        basic::Vector3 yaxis = rotation.GetYAxis();
        float values[] = {-zaxis.X, zaxis.Y, -zaxis.Z, -yaxis.X, yaxis.Y, -yaxis.Z};
        alListenerfv(AL_ORIENTATION, values);
    }

    //-QUERIES------------------------------------------------------------------------------------//
    
    real Device::_ComputeSoundVolume(const Sound& sound) const
    {
        if (sound.Is3D())
        {
            real distance = sound.GetPosition().GetDistance(_ListenerPosition);
            if (distance<=2.0f)
                return sound.GetGain();
            return sound.GetGain() / (distance/2.0f);
        }        
        return sound.GetGain();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Device::_RequestPlay(Sound* sound)
    {
        _RequestStop(sound);
        _WaitingSounds.AddItem(sound);
    }

    //--------------------------------------------------------------------------------------------//
    
    void Device::_RequestStop(Sound* sound)
    {
        uint32 id = _WaitingSounds.FindItem(sound);
        if (id!=NONE)
            _WaitingSounds.Remove(id);

        uint32 buffer_index = NONE;
        for (uint32 i=0 ; i<_Buffers.GetSize() ; ++i)
        {
            if (_Buffers[i]._Sound==sound)
            {
                buffer_index = i;
                break;
            }
        }

        if (buffer_index!=NONE)
        {
            _Buffers[buffer_index]._Sound = NULL;

            if (sound->IsPlaying())
                sound->_Stop();

            sound->_UnBind(_Buffers[buffer_index]._Id);
        }

        shell::Locker lock(_SoundsMutex);
        for (uint32 i=0 ; i<_Sounds.GetSize() ; ++i)
        {
            if (sound==&_Sounds[i]->Instance)
            {
                _Sounds[i]->Status = 2;
                break;
            }
        }
    }

}
}
