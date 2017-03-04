#ifndef _UNIT_TEST_H_
#define _UNIT_TEST_H_

#include "unittest_externals.h"
#include "coffee.h"

namespace unit_test
{
    //--------------------------------------------------------------------------------------------//
    /// UnitTest Application
    ///
    /// The unit testing are based on the TestDog framework, each tests are defined in .test files
    /// next to the functionnalities source code.
    //--------------------------------------------------------------------------------------------//
    class Application : public coffee::Application
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        /// Required constructor
        Application() {}


        /// Required destructor
        ~Application() {}

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// The update will launch all tests then quit the application
        void OnUpdate(const coffee::basic::Time& time_step);
    };
}
#endif
