#ifndef _BUILDER_H_
#define _BUILDER_H_

#include "builder_includes.h"
#include "builder_widget.h"

namespace builder
{
    //--------------------------------------------------------------------------------------------//
    /// Builder Application
    //--------------------------------------------------------------------------------------------//
    class Application : public coffee::Application
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

        Widget* _Widget;
    };
}

#endif
