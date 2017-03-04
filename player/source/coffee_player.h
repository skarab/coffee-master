#ifndef _COFFEE_PLAYER_H_
#define _COFFEE_PLAYER_H_

#include "coffee_player_includes.h"

namespace coffee_player
{
    //--------------------------------------------------------------------------------------------//
    /// Player Application
    //--------------------------------------------------------------------------------------------//
    class COFFEE_PLAYER_API Application : public coffee::Application
    {
        COFFEE_DeclareSingleton(Application);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Application();
        ~Application();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void OnInitialize();
        void OnFinalize();
        void OnUpdate(const basic::Time& time_step);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource::Handler<scene::Resource> _Scene;
    };
}
#endif
