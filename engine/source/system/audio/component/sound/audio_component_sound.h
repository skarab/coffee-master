#ifndef _COFFEE_AUDIO_COMPONENT_SOUND_H_
#define _COFFEE_AUDIO_COMPONENT_SOUND_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/audio/component/audio_component.h"
#include "system/audio/sound/audio_sound.h"

namespace coffee
{
namespace audio
{
    //--------------------------------------------------------------------------------------------//
    /// Sound component
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComponentSound : public Component
    {
        COFFEE_Component(ComponentSound, "Sound", "Audio/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComponentSound();
        ~ComponentSound();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetSound(Sound sound);
        const Sound& GetSound() const;
        Sound& GetSound();

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnStart();
        void OnStop();
        void OnUpdate(const basic::Time& time_step);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Sound _Sound;
        resource::Handler<Sound> _Handler;
        basic::Vector3 _OldPosition;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComponentSound);
}
}
#endif
