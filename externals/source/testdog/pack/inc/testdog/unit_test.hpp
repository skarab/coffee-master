//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : testdog/unit_test.hpp
// DESCRIPTION  : TEST-DOG facade header file.
// COPYRIGHT    : Andy Thomas (C) 2010
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// LICENSE
//---------------------------------------------------------------------------
// This file is part of the "TEST-DOG" program.
// TEST-DOG is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// TEST-DOG is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with TEST-DOG.  If not, see <http://www.gnu.org/licenses/>.
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// HEADER GUARD
//---------------------------------------------------------------------------
#ifndef TDOG_UNIT_TEST_H
#define TDOG_UNIT_TEST_H

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------
#include "macros.hpp"
#include "runner.hpp"

#include <string>

//---------------------------------------------------------------------------
// DOCUMENTATION
//---------------------------------------------------------------------------
//! \file testdog/unit_test.hpp
//! \brief This file is a facade header file for the TEST-DOG Unit Testing
//! Framework. Including it provides access to the TEST-DOG macros and the
//! testdog::runner class.

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------

//! \brief The TEST-DOG C++ namespace.
namespace testdog {

//---------------------------------------------------------------------------
// ABOUT TEST-DOG
//---------------------------------------------------------------------------

//! \brief Library name string constant.
const char* const LIB_NAME = "TEST-DOG C++ Unit Testing Framework";

//! \brief Library version number.
const char* const LIB_VERSION = "1.3.0";

//---------------------------------------------------------------------------
// MAIN PAGE DOCUMENTATION
//---------------------------------------------------------------------------
//! \mainpage TEST-DOG C++ Unit Testing Framework
//! \section tdog_contents CONTENTS
//!
//! - \ref tdog_intro
//! - \ref tdog_license
//! .
//! - \ref tdog_getting_started
//! - \ref tdog_build
//! - \ref tdog_example
//! .
//! - \ref tdog_main MAIN FEATURES
//! - \ref tdog_reports Report Generation
//! - \ref tdog_test_case Declaring Test Cases
//! - \ref tdog_assertions Test Case Assertions
//! - \ref tdog_fixtures Test Fixture
//! - \ref tdog_suites Test Suites
//! .
//! - \ref tdog_info FURTHER INFORMATION
//! - \ref tdog_project_info Associating Project Information
//! - \ref tdog_test_states Test States
//! - \ref Generating Additional Reports
//! - \ref tdog_manual_reg Manual Test Registration
//! .
//! \subsection tdog_ref Reference Pages
//! - \link macros.hpp Test Macros\endlink
//! - \link testdog::runner Test Runner Class\endlink
//! .
//!
//! \n
//! \section tdog_intro INTRODUCTION
//! TEST-DOG is a lightweight, portable and open source C++ Unit Testing
//! Framework.
//!
//! It features:
//! - Test Cases, Suites & Fixtures
//! - Report Generators (Text, XML and HTML)
//! - Macros for Easy Test Creation
//! - Time Limits
//! - Exceptions
//! - Test Runner
//! - Automated, or Manual, Test Registration
//! - Cross Platform & Lightweight with few Dependencies
//! - Supports MinGW, MSVC & Linux
//! - Open Source
//! - Fully Documented
//!.
//! The TEST-DOG Framework comprises a series of test declaration and assertion
//! macros, as well as a singleton based test runner class.
//!
//! \subsection tdog_license Copyright & License
//!
//! Copyright (C) Andy Thomas 2011
//!
//! TEST-DOG is free software: you can redistribute it and/or
//! modify it under the terms of the GNU General Public License as published
//! by the Free Software Foundation, either version 3 of the License, or
//! (at your option) any later version.
//! TEST-DOG is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//! You should have received a copy of the GNU General Public License
//! along with TEST-DOG.  If not, see <http://www.gnu.org/licenses/>.
//!
//! \subsection tdog_web Website
//! On the web: http://www.BigAngryDog.com/testdog/unit_testing.xhtml
//!
//! \n
//! \section tdog_getting_started GETTING STARTED
//! \subsection tdog_build Building & Linking TEST-DOG
//! The TEST-DOG Framework comprises a static library file and related header
//! files. Makefiles are provided which will build both a static library and
//! a self-test binary for the framework. See the README notes in the install
//! directory for more information.
//!
//! To link your project against TEST-DOG:
//! - 1. Link against: "lib/libtestdog.a" (or testdog.lib with MSVC)
//! - 2. Include the "inc/" (but not "inc/testdog/") subdirectory in your include path.
//! - 3. Use: "#include <testdog/unit_test.hpp>" in your source files.
//! .
//!
//! \subsection tdog_example A Simple Example
//! Below is an example of a simple test and main function:
//!
//! \code
//! #include <testdog/unit_test.hpp>
//!
//! // Declare a test case to check whether a custom function
//! // called "is_prime()" returns the correct results.
//! TDOG_TEST_CASE(is_prime_func)
//! {
//!   TDOG_ASSERT(is_prime(47));
//!   TDOG_ASSERT(!is_prime(8));
//!   TDOG_ASSERT(!is_prime(21));
//! }
//!
//! int main(int argc, char **argv)
//! {
//!   // Set default STDOUT report
//!   return testdog:::runner::global().run();
//! }
//! \endcode
//!
//! In this example, we have [presumably] written a function called
//! is_prime() which we  want to test. We include all the required TEST-DOG
//! functionality by simply including the header file "testdog/unit_test.hpp".
//!
//! We then declare a simple test case to exercise our function with the
//! help of the TDOG_TEST_CASE() macro. The test will auto-register with
//! a global instance of a class called testdog::runner. Note that runner
//! and its related data types are namespaced under "testdog".
//!
//! Finally, we run the tests by calling run() on the global instance of
//! runner. The return value from run() is always the number of tests which
//! fail, zero if all tests succeed, or -1 if no testing was performed.
//!
//! Additionally, the above code will generate a text trace which
//! will be written to STDOUT, and will look like:
//!
//! \code
//! -----------------------------------------------------------------
//! Registered Tests: 13
//! Run Scope: All Tests
//! Start Time: 2010-04-16 19:20:15
//! -----------------------------------------------------------------
//!
//! is_prime_func : TEST PASSED
//!
//! -----------------------------------------------------------------
//! STATISTICAL RESULTS
//! -----------------------------------------------------------------
//! TESTS RAN: 1
//! SKIPPED: 0
//! PASSED: 1
//! FAILED: 0
//! TEST ERRORS: 0
//! PASS RATE: 100%
//! -----------------------------------------------------------------
//! END TIME: 2010-04-16 19:20:15
//! RUN DURATION: 0 sec (approx.)
//! -----------------------------------------------------------------
//! \endcode
//!
//! \n
//! \section tdog_main MAIN FEATURES
//! \subsection tdog_reports Report Generation
//! We can control the reporting style by calling the
//! runner::set_report_style() method prior to run(). A report is
//! generated to STDOUT when one or more tests are run. The following
//! report styles are available:
//! - RS_NONE - None (no report is generated).
//! - RS_TEXT_STD - Human readable test report.
//! - RS_TEXT_VERBOSE - Human readable test report (verbose).
//! - RS_XML - XML test report (verbose).
//! - RS_HTML_STD - HTML test report.
//! - RS_HTML_VERBOSE - HTML test report (verbose).
//! - RS_HTML_SUMMARY - HTML test report (summary only).
//! .
//! The default value is RS_TEXT_STD.
//!
//! Additionally, further reports can be written to a std stream after any test
//! run with the runner::generate_report() method.
//!
//! \subsection tdog_test_case Declaring Test Cases
//! Test cases are declared using the TDOG_TEST_CASE() macro, as follows:
//!
//! \code
//! TDOG_TEST_CASE(test_name)
//! {
//!   // Test code
//!   ...
//! }
//! \endcode
//!
//! The test code should not return any result.
//!
//! The test name should not contain spaces, as it will be used internally to
//! form the basis of a C++ data type.
//!
//! Tests are normally executed in the runner in the order that they
//! are declared. However, tests can also be executed individually, as follows:
//!
//! \code
//! testdog::runner::global().run(RUN_TEST, "test_name");
//! \endcode
//!
//! It is also possible to disable the automatic registration of test cases,
//! in which case, tests must be registered explicitly with the runner.
//! See below for further information on this.
//!
//! \subsection tdog_assertions Test Case Assertions
//! Within any test case implementation, one of more assertions should
//! be defined using one of the TEST-DOG assert macros.
//!
//! For example:
//!
//! \code
//! TDOG_TEST_CASE(simple_test)
//! {
//!   TDOG_ASSERT(true); // Passes
//! }
//! \endcode
//!
//! The assert macros checks that the condition is true, and record a
//! failure condition in the report if it is not. A test case is deemed to
//! have passed if all its assert conditions are true, but failed if one
//! or more assertions fail.
//!
//! When an assert condition fails, a failure message will be displayed in the
//! test report output, along with location information such as filename and line
//! number. If the reporting style is "verbose", test passes and
//! informational messages will also be displayed in the report.
//!
//! If the test code throws an unhandled exception, the test
//! case will be placed into an <i>error state</i>. In this case, the test
//! has essentially failed, but the state is considered distinct as it allows
//! for possible test implementation errors to be easily distinguished.
//!
//! TEST-DOG assert macros include:
//! - TDOG_ASSERT()
//! - TDOG_ASSERT_EQUAL()
//! - TDOG_ASSERT_STR_EQUAL()
//! - TDOG_ASSERT_STRIC_EQUAL()
//! - TDOG_ASSERT_DOUBLE_EQUAL()
//! - TDOG_ASSERT_ARRAY_EQUAL()
//! - TDOG_ASSERT_THROW()
//! - TDOG_ASSERT_NO_THROW()
//! .
//! Additionally, it is possible to output an informational messsage using
//! the TDOG_TEST_MSG() macro. This will normally only appear in verbose
//! report outputs however.
//!
//! \subsection tdog_fixtures Test Fixture
//! A test fixture can be declared using the TDOG_TEST_FIXTURE(), and allows
//! a test to use custom data and setup/teardown functionality.
//!
//! This macro is similar to TDOG_TEST_CASE(), except that it
//! requires a data type which it will instantiate when the test is executed.
//! Test setup and teardown code can, therefore, be implemented in the data
//! type's constructor and destructor.
//!
//! For example:
//!
//! \code
//! // Declare fixture type
//! struct person_t
//! {
//!   std::string name;
//!   int age;
//!   person_t() : name("unknown"), age(25) {} // setup
//!   ~person_t() {} // teardown
//! };
//!
//! // Create test fixture
//! TDOG_TEST_FIXTURE(test_person, person_t)
//! {
//!   TDOG_ASSERT_STR_EQUAL_MSG("unknown", name, "Person name test");
//!   TDOG_ASSERT_EQUAL_MSG(25, age, "Default age");
//! }
//! \endcode
//!
//! Note, in the example, how the fixture's data members are accessible in
//! the test implementation. Also note that the fixture's constructor will
//! be called when the test starts, and it's destructor called when the test
//! ends.
//!
//! In the event that either the constructor or destructor throw an exception,
//! an error condition will be recorded and the test case will be deemed to
//! have failed.
//!
//! \subsection tdog_suites Test Suites
//! A test suite allows test cases to be run or disabled in groups.
//! The suite name will be used directly as a C++ namespace around test cases,
//! so it should not contain spaces or conflict with existing namespaces.
//! Declaring tests within namespaced suites also allows the same test name
//! to be used in multiple contexts.
//!
//! In the following example, two test cases are defined inside a test suite:
//!
//! \code
//! TDOG_TEST_SUITE(beast_suite)
//! {
//!   TDOG_TEST_CASE(number_test)
//!   {
//!     int num_beast = 665;
//!     TDOG_ASSERT_EQUAL(666, ++num_beast); // Passes
//!   }
//!
//!   TDOG_TEST_CASE(string_test)
//!   {
//!     std::string neighbor_of_beast = "668";
//!     TDOG_ASSERT_STR_EQUAL("668", neighbor_of_beast); // Passes
//!   }
//! }
//! \endcode
//!
//! When accessing test cases with the testdog::runner class, test cases
//! belonging to suites should always be referred to using the suite name
//! as a prefix.
//!
//! For example:
//!
//! \code
//! // Disable running of suite
//! bool exists = testdog::runner::global().test_exists("beast_suite::number_test");
//! \endcode
//!
//! \n
//! \section tdog_info FURTHER INFORMATION
//! \subsection tdog_project_info Associating Project Information
//! A project name and version string can be associated with the tests using:
//!
//! \code
//! testdog::runner().global().set_project_name("smppd");
//! testdog::runner().global().set_project_version("5.2.3");
//! \endcode
//!
//! This information will be displayed in test reports provided it is set
//! before running the tests.
//!
//! Additionally, an author name can be associated with each test. In
//! this case, this must be set within the test implementation itself, as
//! follows:
//!
//! \code
//! TDOG_TEST_CASE(some_test)
//! {
//!   TDOG_SET_AUTHOR("Employee 24601");
//!   ...
//! }
//! \endcode
//!
//! The underlying input type is std::string.
//!
//! \subsection tdog_selecting_tests Selecting which Tests to Run
//! The run() method of the runner class can be used to selectively run
//! tests individually, or a suite of tests, as follows:
//!
//! \code
//! // Run a single test
//! testdog::runner::global().run(RUN_TEST, "SUITE_NAME::TEST_NAME");
//! \endcode
//!
//! or...
//!
//! \code
//! // Run a suite
//! testdog::runner::global().run(RUN_SUITE, "SUITE_NAME");
//! \endcode
//!
//! See the runner::run() for more information.
//!
//! In addition, it is also possible to selectively disable tests (or suites)
//! in the runner.
//!
//! For example:
//!
//! \code
//! testdog::runner::global().set_test_enabled("SUITE_NAME::TEST_NAME", false);
//! \endcode
//!
//! In these examples, the fully qualified test names were supplied as
//! strings. You should also note that test names are case sensitive.
//!
//! \subsection tdog_test_states Test States
//! The current state of a test case registered with the runner can be
//! queried by calling:
//!
//! \code
//! test_result_t rslt = testdog::runner::global().test_result("SUITE_NAME::TEST_NAME");
//! \endcode
//!
//! This result will be one of the following values:
//! - TR_NOT_RUN - Test was not run.
//! - TR_PASSED - All test conditions passed OK.
//! - TR_FAILED - One or more test conditions failed.
//! - TR_TEST_ERROR - The test failed because of a possible implementation error.
//! .
//! If the test case is not part of a suite,
//! just the test name should be used (i.e. no suite prefix).
//!
//! \subsection Generating Additional Reports
//! By default, when tests in the runner are executed, the runner
//! progressively outputs a report to STDOUT. Typically, you would want to
//! use the text report style for STDOUT.
//!
//! However, you could if you wish, silence the reporting by setting the
//! report style to RS_NONE using the runner::set_report_style() method.
//!
//! You may also wish to receive reports in other formats instead. This can
//! achieved by using the generate_report() method after the run has
//! finished.
//!
//! In this example, we silence STDOUT, and instead write both XML and HTML
//! reports to file:
//!
//! \code
//! #include <testdog/unit_test.hpp>
//! ...
//!
//! int main(int argc, char **argv)
//! {
//!   // Silence STDOUT report
//!   testdog::set_report_style(testdog::RS_NONE);
//!
//!   // Run all tests
//!   int rslt = testdog::runner::global().run();
//!
//!   // Generate XML report file
//!   std::ofstream xml_out;
//!   file_out.open("test_report.xml");
//!   testdog::generate_report(xml_out, testdog::RS_XML);
//!   xml_out.close();
//!
//!   // Generate HTML report file
//!   std::ofstream html_out;
//!   file_out.open("test_report.html");
//!   testdog::generate_report(html_out, testdog::RS_HTML_VERBOSE);
//!   html_out.close();
//!
//!   return rslt;
//! }
//! \endcode
//! See runner::generate_report() for more information.
//!
//! \subsection tdog_manual_reg Manual Test Registration
//! Normally, test cases automatically register themselves with the global
//! runner instance when they are instantiated.
//!
//! However, it is possible to disable the automatic registration of
//! test cases by pre-defining the TDOG_DISABLE_AUTO_REG macro. In this case,
//! the register_test() method must be used to add tests to the runner
//! explicitly. In addition, the TDOG_TEST_REFINST() macro must be used to
//! reference the underlying test case implementation instance, as follows:
//!
//! \code
//! #define TDOG_DISABLE_AUTO_REG
//! #include <testdog/unit_test.hpp>
//!
//! // Define test
//! TDOG_TEST_CASE(some_test)
//! {
//!   ...
//! }
//!
//! int main(int argc, char **argv)
//! {
//!   // Explicitly register the test
//!   testdog::runner::global().register_test(TDOG_TEST_REFINST(some_test));
//!   ...
//! }
//! \endcode
//!
//! If the test case belongs within a test suite, you should use the
//! the suite name as a namespaced prefix. For example:
//!
//! \code
//! testdog::runner::global().register_test(TDOG_TEST_REFINST(suite_name::some_test));
//! \endcode
//!

//---------------------------------------------------------------------------
} // namespace
#endif // HEADER GUARD
//---------------------------------------------------------------------------
