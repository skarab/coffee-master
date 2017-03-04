#include "system/audio/component/sound/audio_component_sound.h"
#include "system/scene/node/scene_node.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(audio::ComponentSound);
        COFFEE_Ancestor(audio::Component);
        COFFEE_Attribute(audio::Sound, _Sound, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace audio
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComponentSound::ComponentSound() :
        _Handler(&_Sound)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ComponentSound::~ComponentSound()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void ComponentSound::SetSound(Sound sound)
    {
        _Sound = sound;
    }

    //--------------------------------------------------------------------------------------------//

    const Sound& ComponentSound::GetSound() const
    {
        return _Sound;
    }

    //--------------------------------------------------------------------------------------------//

    Sound& ComponentSound::GetSound()
    {
        return _Sound;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void ComponentSound::OnStart()
    {
        if (_Sound.GetFilePath().IsEmpty())
        {
            SetSound(resource::Manager::Get().Load(
                storage::Path("/coffee/import/sounds/default.sound")));
        }
        else if(_Sound.IsAvailable())
        {
            _Sound.Play();
        }
    }

    //--------------------------------------------------------------------------------------------//
    
    void ComponentSound::OnStop()
    {
        if (_Sound.IsAvailable())
            _Sound.Stop();
    }

    //--------------------------------------------------------------------------------------------//

    void ComponentSound::OnUpdate(const basic::Time& time_step)
    {
        switch (_Handler.Update())
        {
            case resource::HANDLER_STATE_EndLoading:
            {
                _Sound.Play();
            }

            case resource::HANDLER_STATE_Ready:
            {
                if (GetNode().HasTransform())
                {
                    basic::Vector3 position = GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation();
                    _Sound.SetPosition(position);
                    
                    basic::Vector3 velocity = (position-_OldPosition)/time_step.GetSecondCount();
                    _OldPosition = position;
                    _Sound.SetVelocity(velocity);
                }
            } break;
        }
    }

}
}
