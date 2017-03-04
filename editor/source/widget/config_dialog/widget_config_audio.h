#ifndef _EDITOR_WIDGET_CONFIG_AUDIO_H_
#define _EDITOR_WIDGET_CONFIG_AUDIO_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Audio configuration widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ConfigAudio : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ConfigAudio();
        ~ConfigAudio();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::Window* tab_client);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ConfigAudio);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//
    };
}
}
#endif
