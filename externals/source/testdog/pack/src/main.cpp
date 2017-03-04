//---------------------------------------------------------------------------
// PROJECT      : DOGMA Unit Test
// FILENAME     : main.cpp
// DESCRIPTION  : Test cases & main function
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
// INCLUDES
//---------------------------------------------------------------------------
#include <cstdio>
#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream>

// With this test project, we define the TDOG_DISABLE_AUTO_REG macro
// before including the TEST-DOG header file because we intend to
// register the test cases ourself with the runner. This is not normally
// required, but we are doing it here in order to get TEST-DOG to test itself.
#define TDOG_DISABLE_AUTO_REG
#include <testdog/unit_test.hpp>

//---------------------------------------------------------------------------
// DOCUMENTATION
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------

const char* const UNIQUE_REF_STR = "Unique Ref Str xyz1234";

//---------------------------------------------------------------------------
// MISC FUNCTIONS
//---------------------------------------------------------------------------
inline void wait_delay(int min_sec)
{
  // Crude "sleep" function which waits for a *minimum*
  // num of seconds. Unfortunately, it will hammer
  // the CPU (sorry about that), but as we only expect to
  // wait for a couple of seconds occasionally, we
  // are hoping we can get away with this rather
  // than invoking platform specific sleep calls.
  if (min_sec >= 0)
  {
    std::time_t until = std::time(0) + min_sec;
    while(time(0) <= until);
  }
}
//---------------------------------------------------------------------------
// CLASS public_runner
//---------------------------------------------------------------------------
class public_runner : public testdog::runner
{
public:
  // Make constructor public and
  // disable reporting to STDOUT.
  public_runner() : runner()
    { set_report_style(testdog::RS_NONE); }
};

//---------------------------------------------------------------------------
// INTERNAL TEST SUITE
//---------------------------------------------------------------------------
TDOG_TEST_SUITE(internal_suite)
{
  // Negative asserts
  TDOG_TEST_CASE(assert_false)
  {
    TDOG_ASSERT(false);
  }

  TDOG_TEST_CASE(assert_not_equal)
  {
    TDOG_ASSERT_EQUAL(5, 6);
  }

  TDOG_TEST_CASE(assert_str_not_equal)
  {
    TDOG_ASSERT_STR_EQUAL("Hello World", "Hello Universe");
  }

  TDOG_TEST_CASE(assert_stric_not_equal)
  {
    TDOG_ASSERT_STRIC_EQUAL("Hello World", "Hello Universe");
  }

  TDOG_TEST_CASE(assert_int_not_equal)
  {
    TDOG_ASSERT_INT_EQUAL(5, 6);
  }

  TDOG_TEST_CASE(assert_double_not_equal)
  {
    TDOG_ASSERT_DOUBLE_EQUAL(5.5, 5.6, 0.05);
  }

  TDOG_TEST_CASE(assert_array_not_equal)
  {
    int a[] = {1, 4, 8};
    int b[] = {1, 4, 9};
    TDOG_ASSERT_ARRAY_EQUAL(a, b, 3);
  }

  // Local time limit test (fail)
  TDOG_TEST_CASE(local_limit_fail)
  {
    TDOG_SET_TIME_LIMIT(1);

    // Wait for more than 1 second
    wait_delay(1);
  }

  // Dummy pass, fail and error tests
  TDOG_TEST_CASE(test_pass)
  {
    // Simple pass
    TDOG_TEST_PASS(UNIQUE_REF_STR);
  }

  TDOG_TEST_CASE(test_fail)
  {
    // Simple fail
    TDOG_TEST_FAIL("oops");
  }

  TDOG_TEST_CASE(test_error)
  {
    // Simple error
    TDOG_TEST_ERROR("oops");
  }

  TDOG_TEST_CASE(test_msg)
  {
    // Simple error
    TDOG_TEST_MSG("test message");
    TDOG_TEST_VAL("integer: %(i), HEX: 0x%(08X), OCT:0%(o)", 34283);
    TDOG_TEST_VAL("string: %(k)", L"hello\x09world\u2312");
  }

  // Global time limit tests
  TDOG_TEST_CASE(global_limit_pass)
  {
    // Wait for less than 2 second
    wait_delay(0);
  }

  TDOG_TEST_CASE(global_limit_fail)
  {
    TDOG_SET_TIME_LIMIT(1);

    // Wait for more than 1 second
    wait_delay(1);
  }

  TDOG_TEST_CASE(global_limit_override)
  {
    // Override with local
    TDOG_SET_TIME_LIMIT(3);

    // Wait for more than 1 second
    wait_delay(1);
  }

  TDOG_TEST_CASE(assert_throw_fail)
  {
    TDOG_ASSERT_THROW(throw int(1), std::string);
  }

  TDOG_TEST_CASE(assert_no_throw_fail)
  {
    TDOG_ASSERT_NO_THROW(throw int(1));
  }

}
//---------------------------------------------------------------------------
// MAIN TEST SUITE
//---------------------------------------------------------------------------
TDOG_TEST_SUITE(main_suite)
{
  // Test case name
  TDOG_TEST_CASE(instantiation)
  {
    TDOG_TEST_MSG(TDOG_TEST_NAME());
    TDOG_ASSERT_STR_EQUAL("main_suite::instantiation", TDOG_TEST_NAME());

    // Does test and suite exist in global runner
    TDOG_ASSERT(testdog::runner::global().suite_exists("main_suite"));
    TDOG_ASSERT(testdog::runner::global().test_exists("main_suite::instantiation"));
  }

  // Test the fixture class
  struct fix_t
  {
    int int_val;
    std::string str_val;
    fix_t() : int_val(668), str_val("Hello World") {}
  };

  TDOG_TEST_FIXTURE(fixture, fix_t)
  {
    TDOG_ASSERT_EQUAL(668, int_val);
    TDOG_ASSERT_STR_EQUAL("Hello World", str_val);
  }

  // Positive asserts
  TDOG_TEST_CASE(assert_positive)
  {
    // Ensure asserts leave the test in pass state
    TDOG_ASSERT(true);

    TDOG_ASSERT_MSG(true, "TDOG_ASSERT_MSG");
    TDOG_ASSERT_EQUAL(5, 5);
    TDOG_ASSERT_EQUAL(4.7, 4.7);
    TDOG_ASSERT_EQUAL(std::string("hello"), std::string("hello"));
    TDOG_ASSERT_EQUAL_MSG(12, 12, "TDOG_ASSERT_EQUAL_MSG");

    TDOG_ASSERT_STR_EQUAL("Hello World", "Hello World");
    TDOG_ASSERT_STR_EQUAL_MSG("Hello World", "Hello World",
      "TDOG_ASSERT_STR_EQUAL_MSG");

    TDOG_ASSERT_STRIC_EQUAL("Hello World", "hEllo world");
    TDOG_ASSERT_STRIC_EQUAL_MSG("Hello World", "hEllo world",
      "TDOG_ASSERT_STRIC_EQUAL_MSG");

    TDOG_ASSERT_INT_EQUAL(3, 3);

    TDOG_ASSERT_DOUBLE_EQUAL(5.5, 5.6, 0.15);
    TDOG_ASSERT_DOUBLE_EQUAL_MSG(5.5, 5.6, 0.15, "TDOG_ASSERT_DOUBLE_EQUAL_MSG");

    int a[] = {1, 4, 9};
    int b[] = {1, 4, 9};
    TDOG_ASSERT_ARRAY_EQUAL(a, b, 3);
    TDOG_ASSERT_ARRAY_EQUAL_MSG(a, b, 3, "TDOG_ASSERT_ARRARY_EQUAL_MSG");

    // Test internal state
    TDOG_ASSERT(!TDOG_HAS_TEST_FAILED());
  }

  // Positive asserts
  TDOG_TEST_CASE(assert_negative)
  {
    // Ensure asserts actually fail the test when
    // given a negative condition. This is much more
    // sophistication that the "assert_positive" test,
    // as we actually want the test to succeed if it
    // fails. To do this, we wrap a runner instance
    // and internal test cases. See the documentation
    // at the head of this file.
    public_runner prun;

    // Register Tests
    prun.register_test(TDOG_TEST_REFINST(internal_suite::assert_false));
    prun.register_test(TDOG_TEST_REFINST(internal_suite::assert_not_equal));
    prun.register_test(TDOG_TEST_REFINST(internal_suite::assert_str_not_equal));
    prun.register_test(TDOG_TEST_REFINST(internal_suite::assert_stric_not_equal));
    prun.register_test(TDOG_TEST_REFINST(internal_suite::assert_double_not_equal));
    prun.register_test(TDOG_TEST_REFINST(internal_suite::assert_array_not_equal));

    // Run tests individually so we can test results.
    // We pass *this* test case if its contained tests fail.
    TDOG_ASSERT_EQUAL(1, prun.run(testdog::RUN_TEST,
      "internal_suite::assert_false"));
    TDOG_ASSERT_EQUAL(1, prun.run(testdog::RUN_TEST,
      "internal_suite::assert_not_equal"));
    TDOG_ASSERT_EQUAL(1, prun.run(testdog::RUN_TEST,
      "internal_suite::assert_str_not_equal"));
    TDOG_ASSERT_EQUAL(1, prun.run(testdog::RUN_TEST,
      "internal_suite::assert_stric_not_equal"));
    TDOG_ASSERT_EQUAL(1, prun.run(testdog::RUN_TEST,
      "internal_suite::assert_double_not_equal"));
    TDOG_ASSERT_EQUAL(1, prun.run(testdog::RUN_TEST,
      "internal_suite::assert_array_not_equal"));
  }

  // Local time limits
  TDOG_TEST_CASE(local_limit_pass)
  {
    TDOG_SET_TIME_LIMIT(2);

    // Wait for less than 2 seconds
    wait_delay(0);
  }

  TDOG_TEST_CASE(local_limit_fail)
  {
    // Succeed if limit applied -  we need to wrap a
    // runner instance and an internal test.
    public_runner prun;

    // Register Test
    prun.register_test(TDOG_TEST_REFINST(internal_suite::local_limit_fail));

    // Run test
    TDOG_ASSERT_EQUAL(1, prun.run(testdog::RUN_TEST,
      "internal_suite::local_limit_fail"));
  }

  // Global time limits
  TDOG_TEST_CASE(global_limit_pass)
  {
    // Succeed if test passes
    public_runner prun;

    // Register Test
    prun.set_global_time_limit(2);
    prun.register_test(TDOG_TEST_REFINST(internal_suite::global_limit_pass));

    // Run test
    TDOG_ASSERT_EQUAL(0, prun.run(testdog::RUN_TEST,
      "internal_suite::global_limit_pass"));
  }

  TDOG_TEST_CASE(global_limit_fail)
  {
    // Succeed if test fails
    public_runner prun;

    // Register Test
    prun.set_global_time_limit(1);
    prun.register_test(TDOG_TEST_REFINST(internal_suite::global_limit_fail));

    // Run test
    TDOG_ASSERT_EQUAL(1, prun.run(testdog::RUN_TEST,
      "internal_suite::global_limit_fail"));
  }

  TDOG_TEST_CASE(global_limit_override)
  {
    // Succeed if test passes - local overrides global
    public_runner prun;

    // Register Test
    prun.set_global_time_limit(1);
    prun.register_test(TDOG_TEST_REFINST(internal_suite::global_limit_override));

    // Run test
    TDOG_ASSERT_EQUAL(0, prun.run(testdog::RUN_TEST,
      "internal_suite::global_limit_override"));
  }

  // Ensure that test passes, fails and erros can all be raised, and that
  // they are reflected in the runner results and stats
  TDOG_TEST_CASE(result_states)
  {
    public_runner prun;

    // Register Test
    prun.register_test(TDOG_TEST_REFINST(internal_suite::test_pass));
    prun.register_test(TDOG_TEST_REFINST(internal_suite::test_fail));
    prun.register_test(TDOG_TEST_REFINST(internal_suite::test_error));

    // Run tests (note result is 2 because we expect 2 failures)
    TDOG_ASSERT_EQUAL(2, prun.run());

    // Check result states
    TDOG_ASSERT_EQUAL(testdog::TR_PASSED,
      prun.test_result("internal_suite::test_pass"));
    TDOG_ASSERT_EQUAL(testdog::TR_FAILED,
      prun.test_result("internal_suite::test_fail"));
    TDOG_ASSERT_EQUAL(testdog::TR_TEST_ERROR,
      prun.test_result("internal_suite::test_error"));
    TDOG_ASSERT_EQUAL(testdog::TR_NOT_EXIST,
      prun.test_result("internal_suite::_invalid_name_"));

    // Check stats
    TDOG_ASSERT_EQUAL(3, prun.registered_count());
    TDOG_ASSERT_EQUAL(3, prun.stat_result(testdog::ST_RAN));
    TDOG_ASSERT_EQUAL(0, prun.stat_result(testdog::ST_SKIPPED));
    TDOG_ASSERT_EQUAL(1, prun.stat_result(testdog::ST_PASSED));
    TDOG_ASSERT_EQUAL(1, prun.stat_result(testdog::ST_FAILED));
    TDOG_ASSERT_EQUAL(1, prun.stat_result(testdog::ST_ERRORS));
  }

  // Ensure that we can disable tests & suites
  TDOG_TEST_CASE(disabled_tests)
  {
    public_runner prun;

    // Register Test
    prun.register_test(TDOG_TEST_REFINST(internal_suite::test_pass));
    prun.register_test(TDOG_TEST_REFINST(internal_suite::test_fail));
    prun.register_test(TDOG_TEST_REFINST(internal_suite::test_error));

    // Disable ALL Tests
    prun.set_all_tests_enabled(false);
    TDOG_ASSERT_EQUAL(false, prun.test_enabled("internal_suite::test_fail"));
    TDOG_ASSERT_EQUAL(-1, prun.run());
    TDOG_ASSERT_EQUAL(0, prun.stat_result(testdog::ST_RAN));
    TDOG_ASSERT_EQUAL(3, prun.stat_result(testdog::ST_SKIPPED));
    TDOG_ASSERT_EQUAL(testdog::TR_NOT_RUN,
      prun.test_result("internal_suite::test_fail"));

    // Re-enabled ALL Tests
    prun.set_all_tests_enabled(true);
    TDOG_ASSERT_EQUAL(2, prun.run());
    TDOG_ASSERT_EQUAL(3, prun.stat_result(testdog::ST_RAN));
    TDOG_ASSERT_EQUAL(0, prun.stat_result(testdog::ST_SKIPPED));
    TDOG_ASSERT_EQUAL(testdog::TR_FAILED,
      prun.test_result("internal_suite::test_fail"));

    // Disable Individual Test
    prun.set_test_enabled("internal_suite::test_fail", false);
    TDOG_ASSERT_EQUAL(1, prun.run());
    TDOG_ASSERT_EQUAL(2, prun.stat_result(testdog::ST_RAN));
    TDOG_ASSERT_EQUAL(1, prun.stat_result(testdog::ST_SKIPPED));
    TDOG_ASSERT_EQUAL(testdog::TR_NOT_RUN,
      prun.test_result("internal_suite::test_fail"));

    // Reset
    prun.set_all_tests_enabled(true);

    // Disable ALL Suite(s)
    prun.set_all_suites_enabled(false);
    TDOG_ASSERT_EQUAL(false, prun.suite_enabled("internal_suite"));
    TDOG_ASSERT_EQUAL(-1, prun.run());
    TDOG_ASSERT_EQUAL(0, prun.stat_result(testdog::ST_RAN));
    TDOG_ASSERT_EQUAL(3, prun.stat_result(testdog::ST_SKIPPED));
    TDOG_ASSERT_EQUAL(testdog::TR_NOT_RUN,
      prun.test_result("internal_suite::test_fail"));

    // Re-enable ALL Suite(s)
    prun.set_all_suites_enabled(true);
    TDOG_ASSERT_EQUAL(true, prun.suite_enabled("internal_suite"));
    TDOG_ASSERT_EQUAL(2, prun.run());
    TDOG_ASSERT_EQUAL(3, prun.stat_result(testdog::ST_RAN));
    TDOG_ASSERT_EQUAL(0, prun.stat_result(testdog::ST_SKIPPED));
    TDOG_ASSERT_EQUAL(testdog::TR_FAILED,
      prun.test_result("internal_suite::test_fail"));

    // Disable Individual Suite
    prun.set_suite_enabled("internal_suite", false);
    TDOG_ASSERT_EQUAL(-1, prun.run());
    TDOG_ASSERT_EQUAL(0, prun.stat_result(testdog::ST_RAN));
    TDOG_ASSERT_EQUAL(3, prun.stat_result(testdog::ST_SKIPPED));
    TDOG_ASSERT_EQUAL(testdog::TR_NOT_RUN,
      prun.test_result("internal_suite::test_fail"));
  }

  // Report generation
  TDOG_TEST_CASE(text_report_generation)
  {
    public_runner prun;

    // Register Test
    prun.register_test(TDOG_TEST_REFINST(internal_suite::test_pass));
    prun.register_test(TDOG_TEST_REFINST(internal_suite::test_fail));
    prun.register_test(TDOG_TEST_REFINST(internal_suite::test_msg));

    // Disable the fail test
    prun.set_test_enabled("internal_suite::test_fail",false);

    // Run tests (note result is 2 because we expect 2 failures)
    TDOG_ASSERT_EQUAL(0, prun.run());
    TDOG_ASSERT_EQUAL(testdog::RUN_ALL, prun.run_scope());

    // Generate STD report (get as string)
    std::stringstream t_stream;
    prun.generate_report(t_stream, testdog::RS_TEXT_STD);
    std::string rs = t_stream.str();
    TDOG_ASSERT((rs.size() > 0));

    // Search for keywords (pass msg only found in verbose)
    TDOG_ASSERT((rs.find("internal_suite::test_pass") != std::string::npos));
    TDOG_ASSERT((rs.find(UNIQUE_REF_STR) == std::string::npos));
    TDOG_ASSERT((rs.find("internal_suite::test_fail") == std::string::npos));

    // Generate VERBOSE report (get as string)
    prun.generate_report(t_stream, testdog::RS_TEXT_VERBOSE);
    rs = t_stream.str();
    TDOG_ASSERT((rs.size() > 0));

    // Search for keywords (pass msg only found in verbose)
    TDOG_ASSERT((rs.find("internal_suite::test_pass") != std::string::npos));
    TDOG_ASSERT((rs.find(UNIQUE_REF_STR) != std::string::npos));
    TDOG_ASSERT((rs.find("internal_suite::test_fail") != std::string::npos));

    TDOG_ASSERT((rs.find("test message") != std::string::npos));
    TDOG_ASSERT((rs.find("integer: 34283, HEX: 0x000085EB, OCT:0102753")
      != std::string::npos));
    TDOG_ASSERT((rs.find("string: hello\\tworld\\u2312") != std::string::npos));
  }

  TDOG_TEST_CASE(html_report_generation)
  {
    public_runner prun;

    // Register Test
    prun.register_test(TDOG_TEST_REFINST(internal_suite::test_pass));
    prun.register_test(TDOG_TEST_REFINST(internal_suite::test_fail));

    // Disable the fail test
    prun.set_test_enabled("internal_suite::test_fail",false);

    // Run tests (note result is 2 because we expect 2 failures)
    TDOG_ASSERT_EQUAL(0, prun.run());
    TDOG_ASSERT_EQUAL(testdog::RUN_ALL, prun.run_scope());

    // Generate STD report (get as string)
    std::stringstream t_stream;
    prun.generate_report(t_stream, testdog::RS_HTML_STD);
    std::string rs = t_stream.str();
    TDOG_ASSERT((rs.size() > 0));

    // Search for keywords (pass msg only found in verbose)
    TDOG_ASSERT((rs.find("internal_suite::test_pass") != std::string::npos));
    TDOG_ASSERT((rs.find(UNIQUE_REF_STR) == std::string::npos));
    TDOG_ASSERT((rs.find("internal_suite::test_fail") == std::string::npos));

    // Generate VERBOSE report (get as string)
    prun.generate_report(t_stream, testdog::RS_HTML_VERBOSE);
    rs = t_stream.str();
    TDOG_ASSERT((rs.size() > 0));

    // Search for keywords (pass msg only found in verbose)
    TDOG_ASSERT((rs.find("internal_suite::test_pass") != std::string::npos));
    TDOG_ASSERT((rs.find(UNIQUE_REF_STR) != std::string::npos));
    TDOG_ASSERT((rs.find("internal_suite::test_fail") != std::string::npos));
  }

  TDOG_TEST_CASE(xml_report_generation)
  {
    public_runner prun;

    // Register Test
    prun.register_test(TDOG_TEST_REFINST(internal_suite::test_pass));
    prun.register_test(TDOG_TEST_REFINST(internal_suite::test_fail));

    // Disable the fail test
    prun.set_test_enabled("internal_suite::test_fail",false);

    // Run tests (note result is 2 because we expect 2 failures)
    TDOG_ASSERT_EQUAL(0, prun.run());
    TDOG_ASSERT_EQUAL(testdog::RUN_ALL, prun.run_scope());

    // Generate STD report (get as string)
    std::stringstream t_stream;
    prun.generate_report(t_stream, testdog::RS_XML);
    std::string rs = t_stream.str();
    TDOG_ASSERT((rs.size() > 0));

    // Search for keywords
    TDOG_ASSERT((rs.find("internal_suite") != std::string::npos));
    TDOG_ASSERT((rs.find("test_pass") != std::string::npos));
    TDOG_ASSERT((rs.find(UNIQUE_REF_STR) != std::string::npos));
    TDOG_ASSERT((rs.find("test_fail") != std::string::npos));
  }

  TDOG_TEST_CASE(assert_throw_ok)
  {
    // Throw and expect int
    TDOG_ASSERT_THROW(throw int(1), int);
  }

  TDOG_TEST_CASE(assert_no_throw_ok)
  {
    // Throw nothing
    TDOG_ASSERT_NO_THROW(do{}while(false));
  }

  TDOG_TEST_CASE(assert_throw_fail)
  {
    // Throw an int (expect something else)
    public_runner prun;

    // Register Tests
    prun.register_test(TDOG_TEST_REFINST(internal_suite::assert_throw_fail));

    // Run tests individually so we can test results.
    // We pass *this* test case if its contained tests fail.
    TDOG_ASSERT_EQUAL(1, prun.run(testdog::RUN_TEST,
      "internal_suite::assert_throw_fail"));
  }

  TDOG_TEST_CASE(assert_no_throw_fail)
  {
    // Throw in no throw
    public_runner prun;

    // Register Tests
    prun.register_test(TDOG_TEST_REFINST(internal_suite::assert_no_throw_fail));

    // Run tests individually so we can test results.
    // We pass *this* test case if its contained tests fail.
    TDOG_ASSERT_EQUAL(1, prun.run(testdog::RUN_TEST,
      "internal_suite::assert_no_throw_fail"));
  }
}
//---------------------------------------------------------------------------
// MAIN FUNCTION
//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
  // Set project title
  testdog::runner::global().set_project_name(testdog::LIB_NAME);
  testdog::runner::global().set_project_version(testdog::LIB_VERSION);

  // Define the report style
  testdog::runner::global().set_report_style(testdog::RS_TEXT_VERBOSE);
  testdog::runner::global().set_report_charset("utf-8");

  // We must register the tests explicitly
  // if we pre-define the TDOG_DISABLE_AUTO_REG
  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::instantiation));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::fixture));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::assert_positive));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::assert_negative));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::local_limit_pass));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::local_limit_fail));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::global_limit_pass));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::global_limit_fail));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::global_limit_override));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::result_states));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::disabled_tests));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::text_report_generation));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::html_report_generation));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::xml_report_generation));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::assert_throw_ok));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::assert_no_throw_ok));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::assert_throw_fail));

  testdog::runner::global().register_test(
    TDOG_TEST_REFINST(main_suite::assert_no_throw_fail));

  // Run the tests
  int rslt = testdog::runner::global().run();

  // Generate additional HTML report in working directory
  std::ofstream fs;
  fs.open("./test_report.html");
  testdog::runner::global().generate_report(fs, testdog::RS_HTML_VERBOSE);
  fs.close();

  // Generate additional XML report in working directory
  fs.open("./test_report.xml");
  testdog::runner::global().generate_report(fs, testdog::RS_XML);
  fs.close();

  return rslt;
}
//---------------------------------------------------------------------------
