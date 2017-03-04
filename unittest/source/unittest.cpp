#ifdef COFFEE_COMPILER_MINGW
    #include "stdint-gcc.h"
#endif

#include <fstream>
#include <iosfwd>
#include "unittest.h"
using namespace coffee;
#include "coffee.test"

#define REGISTER_TEST(_test_) \
    testdog::runner::global().register_test( \
        *new unit_test::_test_##_tdog_test_class)

//-META-------------------------------------------------------------------------------------------//

COFFEE_RegisterApplication(unit_test::Application,
    RUN_MODE_MemoryReport | RUN_MODE_MemoryTrack
    | RUN_MODE_UnitTest | RUN_MODE_MetaType );

#define UNIT_TEST_REGISTER

namespace unit_test
{
    //-OPERATIONS---------------------------------------------------------------------------------//

    void Application::OnUpdate(const basic::Time& time_step)
    {
        static bool has_run_tests(false);

        coffee::Application::OnUpdate(time_step);

        // Run the tests only once
        if (!has_run_tests)
        {
            testdog::runner::create();

            testdog::runner::global().set_project_name("Coffee");
            testdog::runner::global().set_project_version("");
            testdog::runner::global().set_report_style(testdog::RS_TEXT_STD);
            testdog::runner::global().set_report_charset("utf-8");

            #include "coffee.test"

            testdog::runner::global().run();

            // Generate xml report
            std::ofstream file_out;
            file_out.open("test_report.html");
            testdog::runner::global().generate_report(file_out, testdog::RS_HTML_VERBOSE);
            file_out.close();

            Engine::Get().Quit();
            has_run_tests = true;        
            testdog::runner::destroy();
        }
    }

}
