#ifndef _COFFEE_REPLACE_H_
#define _COFFEE_REPLACE_H_

#include "coffee.h"
using namespace coffee;

//-IMPORT-EXPORT----------------------------------------------------------------------------------//
#ifndef USE_COFFEE_REPLACE
    #define COFFEE_REPLACE_API __declspec(dllexport)
    #define COFFEE_REPLACE_TEMPLATE_API __declspec(dllexport)
#else
    #define COFFEE_REPLACE_API __declspec(dllimport)
    #define COFFEE_REPLACE_TEMPLATE_API
#endif

#ifdef USE_COFFEE_REPLACE
    #define COFFEE_REPLACE_EXPORT_STATICS false
#else
    #define COFFEE_REPLACE_EXPORT_STATICS true
#endif
//------------------------------------------------------------------------------------------------//

namespace coffee_replace
{
    //--------------------------------------------------------------------------------------------//
    /// coffee_replace::Library
    //--------------------------------------------------------------------------------------------//
    class COFFEE_REPLACE_API Library : public plugins::Library
    {
        COFFEE_Type(Library);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Library();
        ~Library();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize();
        void Finalize();
        void Update(const basic::Time& time_step);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//


    };

    COFFEE_RegisterType(COFFEE_REPLACE_EXPORT_STATICS, Library);
}

COFFEE_RegisterPlugin(coffee_replace::Library);

#endif
