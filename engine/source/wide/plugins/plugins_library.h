#ifndef _COFFEE_PLUGINS_LIBRARY_H_
#define _COFFEE_PLUGINS_LIBRARY_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"

namespace coffee
{
namespace plugins
{
    //--------------------------------------------------------------------------------------------//
    /// Plugin library inherited from all plugins
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Library : public meta::Object
    {
        COFFEE_Type(Library);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Library();
        virtual ~Library();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Initialize();
        void _Finalize();
        virtual void Initialize() {};
        virtual void Finalize() {};
        virtual void Update(const basic::Time& time_step) {};

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<meta::Type*> _RegisteredTypes;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Library);
}
}
#endif
