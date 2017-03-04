//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : testdog/runner.hpp
// DESCRIPTION  : Test runner class.
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
#ifndef TDOG_RUNNER_H
#define TDOG_RUNNER_H

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------
#include "private/basic_test.hpp"
#include "private/test_case.hpp"

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <ostream>

//---------------------------------------------------------------------------
// DOCUMENTATION
//---------------------------------------------------------------------------
//! \file testdog/runner.hpp
//! \brief This file provides the testdog::runner class and associated types.
//! \sa testdog::runner

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------

// Namespace
namespace testdog {

//! \brief An enumerated type used to designate the style of test run reports.
//! \details Test reports are subdivided according to their "log level", and
//! are considered to be verbose or standard.
//!
//! Standard reports contain only summary information pertaining to test
//! cases which pass, but further details are provided for those tests which
//! fail. Whereas verbose reports contain the same detailed trace information
//! irrespective of whether the test case passed or not.
//! \sa runner::set_report_style(), runner::generate_report()
enum report_style_t
{
  RS_NONE = 0,      //!< None (no report is generated).
  RS_TEXT_STD,      //!< Human readable test report.
  RS_TEXT_VERBOSE,  //!< Human readable test report (verbose).
  RS_XML,           //!< XML test report (verbose).
  RS_HTML_STD,      //!< HTML test report.
  RS_HTML_VERBOSE,  //!< HTML test report (verbose).
  RS_HTML_SUMMARY,  //!< HTML test report (summary only).
};

//! \brief An enumerated type used to designate what tests should be run.
//! \sa runner::run()
enum run_scope_t
{
  RUN_NONE = 0,  //!< Run none (no tests were run).
  RUN_ALL,       //!< Run all tests.
  RUN_SUITE,     //!< Run only the specified test suite.
  RUN_TEST       //!< Run only the specified test case.
};

//! \brief An enumerated type used to designate a required statistic from
//! the last test run.
//! \sa runner::stat_result()
enum result_stat_t
{
  ST_RAN = 0,       //!< Number of tests executed in the test run.
  ST_SKIPPED,       //!< Number of tests skipped (i.e. were disabled).
  ST_PASSED,        //!< Number of tests that passed.
  ST_FAILED,        //!< Number of tests that failed.
  ST_ERRORS,        //!< Number of tests which implementation errors.
  ST_PASS_RATE      //!< Percentage of tests that passed.
};

//! \brief An enumerated type used to provide the a test case result.
//! \details The runner::test_result() method can be used to query the
//! result state of any test in the runner.
//! \sa runner::test_result()
enum test_result_t
{
  TR_NOT_EXIST = 0, //!< The test case does not exist in the runner.
  TR_NOT_RUN,       //!< Test was not run.
  TR_PASSED,        //!< All test conditions passed OK.
  TR_FAILED,        //!< One or more test conditions failed.
  TR_TEST_ERROR     //!< The test failed because of a possible implementation error.
};

// Forward declaration
class basic_reporter;

//---------------------------------------------------------------------------
// MACROS
//---------------------------------------------------------------------------
//! \brief Synonym for: testdog::runner::global()
//! \details This macro is provided for convenience. The following two
//! lines of code are equivalent:
//!
//! Example:
//!
//! \code
//! // 1. Run all tests
//! int rslt = testdog::runner::global().run();
//! ...
//! // 2. Run all tests
//! int rslt = TDOG().run();
//! \endcode
//! \sa runner::global()
#define TDOG() testdog::runner::global()

//---------------------------------------------------------------------------
// CLASS runner
//---------------------------------------------------------------------------
//! \class runner
//! \brief The runner class is used to run test cases and collate
//! result information.
//! \details The runner cannot be instantiated directly, rather access to a
//! global instance is granted through its singleton method: runner::global().
class runner
{
protected:

  // Protected properties
  std::string m_project_name;
  std::string m_project_version;
  report_style_t m_report_style;
  std::string m_report_charset;
  std::string m_html_report_stylesheet;
  bool m_report_loc;
  int m_text_report_break_width;
  bool m_html_report_author_col;
  int m_tests_ran;
  int m_tests_skipped;
  int m_tests_passed;
  int m_tests_failed;
  int m_test_errors;
  run_scope_t m_run_scope;
  std::time_t m_start_time;
  std::time_t m_end_time;
  bool m_contains_suites;
  int m_global_time_limit;
  std::string m_prev_suite_name;
  std::vector<basic_test*> m_basic_tests;

  typedef std::map<std::string, bool> suite_state_t;
  suite_state_t m_suite_state_map;

  // Protected methods
  basic_test* m_find_tc(const std::string& tname) const;
  bool m_suite_enabled(const std::string& sname) const;
  basic_reporter* m_create_reporter(report_style_t rs) const;
  void m_clear_results();

  // Hidden contructor
  runner();

public:

  //! @name Class Instantiation
  //! @{

  //! \brief Destructor.
  virtual ~runner();

  //! \brief Singleton access
  //! \details There is no public constructor for this class, and all
  //! access is via this singleton method to a single class instance.
  //!
  //! Example:
  //!
  //! \code
  //! // Run all tests
  //! testdog::runner::global().run();
  //! \endcode
  //!
  //! \return Reference to global instance
  static runner& global();
  static void create();
  static void destroy();
	
  //! @}
  //! @name Project Information
  //! @{

  //! \brief Returns the user supplied name of the project under test.
  //! \details The project name is an optional string which is displayed
  //! in test report outputs.
  //! \return Project name string
  //! \sa set_project_name(), project_version()
  std::string project_name() const;

  //! \brief Sets the name of the project under test.
  //! \details The project name is an optional string which is displayed
  //! in test report outputs.
  //!
  //! Example:
  //! \code
  //! testdog::runner().global().set_project_name("smppd");
  //! \endcode
  //! \param[in] pname Project name
  //! \sa project_name(), set_project_version()
  void set_project_name(const std::string& pname);

  //! \brief Returns the user supplied version string for the test project.
  //! \details The project version is an optional string which is displayed
  //! in test report outputs.
  //! \return Project version string
  //! \sa set_project_version(), project_name()
  std::string project_version() const;

  //! \brief Sets the version string of the project under test.
  //! \details The project version is an optional string which is displayed
  //! in test report outputs.
  //!
  //! Example:
  //! /code
  //! testdog::runner().global().set_project_version("3.1.6");
  //! /endcode
  //! \param[in] ver Project version string
  //! \sa project_version(), set_project_name()
  void set_project_version(const std::string& ver);

  //! @}
  //! @name Test Registration
  //! @{

  //! \brief Explicitly registers a test case instance with the runner.
  //! \details Normally there is no need to call this method, as test cases
  //! automatically register themselves with the global runner instance
  //! when they are instantiated.
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
  //! With self-registration, tests are run in the order that they are
  //! declared. One possible benefit of registering tests explicitly, therefore,
  //! is that it provides some control over the run order.
  //! \param[in] tc Underlying test instance
  //! \sa TDOG_TEST_REFINST(), registered_count()
  void register_test(test_case& tc);

  //! \overload
  //! \param[in] tc Underlying test instance
  void register_test(basic_test& tc);

  //! \brief Returns the number of tests registered in the runner.
  //! \return Number of tests
  //! \sa register_test(), stat_result()
  int registered_count() const;

  //! \brief Clears all tests registered with the runner.
  //! \sa register_test()
  void clear_tests();

  //! \brief Returns whether the test case with the given name exists.
  //! \details The test name should be fully qualified with the suite name.
  //!
  //! For example:
  //! \code
  //! bool ex = testdog::runner::global().test_exists("SUITE_NAME::TEST_NAME");
  //! \endcode
  //!
  //! Test names are case sensitive.
  //!
  //! If the test case is not part of a suite, just the test name should
  //! be used.
  //! \param[in] tname Test case name
  //! \return Boolean result
  //! \sa suite_exists()
  bool test_exists(const std::string& tname) const;

  //! \brief Returns whether the test suite with the given name exists.
  //! \details Suite names are case sensitive.
  //! \param[in] sname Suite name
  //! \return Boolean result
  //! \sa test_exists(), contains_suites()
  bool suite_exists(const std::string& sname) const;

  //! \brief Returns true if one or more tests were declared within
  //! a test suite.
  //! \return Boolean result
  //! \sa suite_exists()
  bool contains_suites() const;

  //! \brief Enumerates the fully qualified names of all test cases registered
  //! with the runner.
  //! \details The results are returned using "rslt_out", which
  //! supplies a vector array of std::string. The rslt_out array will
  //! first be emptied before being re-populated with test case names.
  //!
  //! Test names are provided in the order which they were originally
  //! registered, which is also their run order.
  //! \param[out] rslt_out A vector array of strings used to retrieve results
  //! \return A reference to rslt_out
  //! \sa enum_suite_names()
  std::vector<std::string>& enum_test_names(
    std::vector<std::string>& rslt_out) const;

  //! \brief Enumerates the names of all test suites in the runner.
  //! \details The results are returned using "rslt_out", which
  //! supplies a vector array of std::string. The rslt_out array will
  //! first be emptied before being repopulated with test suite names.
  //!
  //! An empty string will be used to designate the default suit, i.e.
  //! where test cases are declared outside of a test suite.
  //! \param[out] rslt_out A vector array of strings used to retrieve results
  //! \return A reference to rslt_out
  //! \sa enum_test_names()
  std::vector<std::string>& enum_suite_names(
    std::vector<std::string>& rslt_out) const;

  //! @}
  //! @name Disabling Tests
  //! @{

  //! \brief Returns whether a test case with the given name is enabled.
  //! \details Tests which have been disabled will not be executed by the runner.
  //!
  //! Use the fully qualified test name. For example:
  //!
  //! \code
  //! bool en = testdog::runner::global().test_enabled("SUITE_NAME::TEST_NAME");
  //! \endcode
  //!
  //! Test names are case sensitive.
  //!
  //! If the test case is not part of a suite, just the test name should be
  //! used without any namespace.
  //!
  //! The default enabled state for tests is true. The result will be false
  //! if a test of the given name does not exist.
  //!
  //! Note. The enabled state of test cases and their suites are independent,
  //! and both must be enabled for a test to run.
  //! \param[in] tname Test case name
  //! \return Boolean result value
  //! \sa set_test_enabled(), suit_enabled(), test_exists()
  bool test_enabled(const std::string& tname) const;

  //! \brief Allows an individual test case with the given name to be disabled
  //! (or re-enabled).
  //! \details Tests which have been disabled will not be executed by the runner.
  //!
  //! Use the fully qualified test name. For example:
  //!
  //! \code
  //! testdog::runner::global().set_test_enabled("SUITE_NAME::TEST_NAME", false);
  //! \endcode
  //!
  //! Test names are case sensitive.
  //!
  //! If the test case is not part of a suite, just the test name should be
  //! used without any namespace.
  //!
  //! The default enabled state for tests is true. This call does nothing if
  //! a test of the given name does not exist.
  //!
  //! Note. The enabled state of test cases and their suites are independent,
  //! and both must be enabled for a test to run.
  //! \param[in] tname Test case name
  //! \param[in] e Enabled flag
  //! \sa test_enabled(), set_all_tests_enabled(), set_suit_enabled(),
  //! test_exists()
  void set_test_enabled(const std::string& tname, bool e);

  //! \brief Sets the enabled states for all tests (in all suites).
  //! \param[in] e Enabled flag
  //! \sa set_all_suites_enabled(), set_test_enabled()
  void set_all_tests_enabled(bool e);

  //! \brief Returns whether the test suite with the given name is enabled.
  //! \details Tests belonging to a disabled suite will not be executed by
  //! the runner.
  //!
  //! When calling this method, use the fully qualified test name. For example:
  //!
  //! \code
  //! bool en = testdog::runner::global().suite_enabled("SUITE_NAME");
  //! \endcode
  //!
  //! The default enabled state for suites is true. Suite names are case
  //! sensitive. The result will be false if a suite of the given name does
  //! not exist.
  //!
  //! Note. The enabled state of test cases and their suites are independent,
  //! and both must be enabled for a test to run.
  //! \param[in] sname Suite name
  //! \return Boolean result value
  //! \sa set_suite_enabled(), test_enabled(), suit_exists()
  bool suite_enabled(const std::string& sname) const;

  //! \brief Allows the test suite with the given name to be disabled
  //! (or re-enabled).
  //! \details Tests belonging to a disabled suite will not be executed by
  //! the runner.
  //!
  //! When calling this method, use the fully qualified test name. For example:
  //!
  //! \code
  //! bool en = testdog::runner::global().suite_enabled("SUITE_NAME");
  //! \endcode
  //!
  //! The default enabled state for suites is true. Suite names are case
  //! sensitive. This call does nothing if a suite of the given name does
  //! not exist. The default suite state can be set by using an empty string
  //! ("") for its name.
  //!
  //! Note. The enabled state of test cases and their suites are independent,
  //! and both must be enabled for a test to run.
  //! \param[in] sname Suite name
  //! \param[in] e Enabled flag
  //! \sa suite_enabled(), set_all_suites_enabled(), set_test_enabled(),
  //! suite_exists()
  void set_suite_enabled(const std::string& sname, bool e);

  //! \brief Sets the enabled states for all test suites.
  //! \param[in] e Enabled flag
  //! \sa set_all_tests_enabled(), set_suite_enabled()
  void set_all_suites_enabled(bool e);

  //! @}
  //! @name Running Tests
  //! @{

  //! \brief Run all tests, or just those specified.
  //! \details The "scope" parameter defines the scope of the test run,
  //! and may be one of the following values:
  //! - RUN_NONE - Run none (no tests were run).
  //! - RUN_ALL  - Run all tests.
  //! - RUN_SUITE - Run only the specified test suite.
  //! - RUN_TEST - Run only the specified test case.
  //! .
  //! The name parameter supplies the suite name if the scope is RUN_SUITE,
  //! or the fully qualified test name if RUN_TEST. It is ignored for
  //! the RUN_ALL scope.
  //!
  //! The run() method does nothing if RUN_NONE is specified--this is really
  //! a result value for use with the run_scope() method.
  //!
  //! Both scope and name have default values so that calling run() without
  //! any parameters will execute all tests. For example, to run all tests
  //! simply call:
  //!
  //! \code
  //! return testdog::runner::global().run();
  //! \endcode
  //!
  //! To run an individual test, call:
  //!
  //! \code
  //! testdog::runner::global().run(RUN_TEST, "SUITE_NAME::TEST_NAME");
  //! \endcode
  //!
  //! To run a single suite, use RUN_SUITE and supply the suite name. Use
  //! an empty string to run only the tests in the default suite, i.e. those
  //! tests declared outside of any TDOG_TEST_SUITE() macro.
  //!
  //! Test and suite names are case sensitive.
  //!
  //! The return value gives the number of test cases which failed, or had
  //! errors. The value will be 0 if all test cases ran successfully without
  //! asserting failures or test errors. If, however, no tests were run,
  //! the return value will be -1, rather than 0. This distinguishes a
  //! successful test run from one that doesn't actually test anything.
  //! This may occur if all test cases are disabled or if no
  //! tests have been registered with the runner.
  //! \return Number of test failures, or -1 if no tests performed
  //! \param[in] scope Scope of tests to run
  //! \param[in] name Name of suite or individual test case
  //! \sa test_result(), stat_result(), run_scope()
  int run(run_scope_t scope = RUN_ALL, const std::string& name = "");

  //! \brief Returns the "scope" used in the last call to the run()
  //! method.
  //! \details If run() was never called, the return value is RUN_NONE.
  //! \return Last run scope value
  //! \sa run()
  run_scope_t run_scope() const;

  //! \brief Returns the global time limit for test cases in seconds.
  //! \details The global test contraint is the maximum amount of time
  //! that individual test cases can take to complete.
  //! If any test case takes longer than this value, it will be deemed to
  //! have failed. A value of 0, the default, disables the global time
  //! constaint.
  //!
  //! Time constraints may also be applied to test cases on an individual
  //! basis, and where a test case has its a local time limit defined, it will
  //! be used in preference to the global one.
  //! \return Time limit applied to all test cases
  //! \sa set_global_time_limit()
  int global_time_limit() const;

  //! \brief Sets the global time limit for test cases in seconds.
  //! \details The global test contraint is the maximum amount of time
  //! that individual test cases can take to complete.
  //! If any test case takes longer than this value, it will be deemed to
  //! have failed. A value of 0, the default, disables the global time
  //! constaint.
  //!
  //! Time constraints may also be applied to test cases on an individual
  //! basis, and where a test case has its a local time limit defined, it will
  //! be used in preference to the global one.
  //! \param[in] gc_sec Time limit in seconds
  //! \sa global_time_limit()
  void set_global_time_limit(int gc_sec);

  //! @}
  //! @name Generating Test Reports
  //! @{

  //! \brief Returns the report style written to STDOUT during the test run.
  //! \details This setting controls the style of this report, which can be
  //! one of:
  //! - RS_NONE - None (no report is generated).
  //! - RS_TEXT_STD - Human readable test report.
  //! - RS_TEXT_VERBOSE - Human readable test report (verbose).
  //! - RS_XML - XML test report (verbose).
  //! - RS_HTML_STD - HTML test report.
  //! - RS_HTML_VERBOSE - HTML test report (verbose).
  //! - RS_HTML_SUMMARY - HTML test report (summary only).
  //! .
  //! A report is generated to STDOUT when one or more test cases are
  //! run. The default value is RS_TEXT_STD.
  //!
  //! Test reports are subdivided according to their "log level", and
  //! are considered to be verbose or standard.
  //!
  //! Standard reports contain only summary information pertaining to test
  //! cases which pass, but further details are provided for those tests which
  //! fail. Whereas verbose reports contain the same detailed trace information
  //! irrespective of whether the test case passed or not.
  //! \return Stdout reporting style
  //! \sa set_report_style(), generate_report(), run()
  report_style_t report_style() const;

  //! \brief Set the report style written to STDOUT during the test run.
  //! \details This setting controls the style of this report, which can be
  //! one of:
  //! - RS_NONE - None (no report is generated).
  //! - RS_TEXT_STD - Human readable test report.
  //! - RS_TEXT_VERBOSE - Human readable test report (verbose).
  //! - RS_XML - XML test report (verbose).
  //! - RS_HTML_STD - HTML test report.
  //! - RS_HTML_VERBOSE - HTML test report (verbose).
  //! - RS_HTML_SUMMARY - HTML test report (summary only).
  //! .
  //! A report is generated to STDOUT when one or more tests are
  //! run. The default value is RS_TEXT_STD.
  //!
  //! Example:
  //!
  //! \code
  //! // Use verbose report
  //! testdog::runner::global().set_report_style(testdog::RS_TEXT_VERBOSE);
  //! \endcode
  //!
  //! Test reports are subdivided according to their "log level", and
  //! are considered to be verbose or standard.
  //!
  //! Standard reports contain only summary information pertaining to test
  //! cases which pass, but further details are provided for those tests which
  //! fail. Whereas verbose reports contain the same detailed trace information
  //! irrespective of whether the test case passed or not.
  //! \param[in] rs Report style
  //! \sa report_style(), generate_report(), run()
  void set_report_style(report_style_t rs);

  //! \brief Generates a test report pertaining to the last test run and writes
  //! it to the supplied output stream.
  //! \details The report is generated according to the style rs, and
  //! is useful where test reports in multiple formats are required. Note that
  //! the report generated with this method would be in addition to that
  //! written to STDOUT as the the test runs.
  //!
  //! Here's an example of where a text style report is written to the STDOUT as
  //! the tests are executed, and a further XML report is written to file
  //! after the test run.
  //!
  //! \code
  //! #include <testdog/unit_test.hpp>
  //! ...
  //!
  //! int main(int argc, char **argv)
  //! {
  //!   // Set default STDOUT report
  //!   testdog::set_report_style(testdog::RS_TEXT_VERBOSE);
  //!
  //!   // Run all tests
  //!   int rslt = testdog::runner::global().run();
  //!
  //!   // Generate XML report file
  //!   std::ofstream file_out;
  //!   file_out.open("test_report.xml");
  //!   testdog::runner::global().generate_report(file_out, testdog::RS_XML);
  //!   file_out.close();
  //!
  //!   return rslt;
  //! }
  //! \endcode
  //!
  //! Unlike reports normally written to STDOUT during the test run,
  //! reports generated with a call to generate_report() are not progressive.
  //! I.e. the report will be realized only after the test run has fully
  //! completed.
  //!
  //! The generate_report() method does nothing if passed the report style
  //! value RS_NONE.
  //! \param[in,out] ro Output stream
  //! \param[in] rs Report style
  //! \return Reference to output stream
  //! \sa set_report_style()
  std::ostream& generate_report(std::ostream& ro, report_style_t rs) const;

  //! \brief Returns the test report character set encoding.
  //! \details This is a short string specifying a valid character set encoding
  //! for use in generating XML and HTML test reports. The value supplied is
  //! used simply to populate the "charset" field of XML and HTML documents.
  //! Valid examples include, "utf-8" and "iso-8859-1".
  //!
  //! The default value is an empty string which leaves the field unspecified.
  //! \return Report character set encoding
  //! \sa set_report_charset(), html_report_stylesheet(), report_style()
  std::string report_charset() const;

  //! \brief Sets the test report character set encoding.
  //! \details This is a short string specifying a valid character set encoding
  //! for use in generating XML and HTML test reports. The value supplied is
  //! used simply to populate the "charset" field of XML and HTML documents.
  //! Valid examples include, "utf-8" and "iso-8859-1".
  //!
  //! The default value is an empty string which leaves the field unspecified.
  //! \param[in] cs Report character set encoding
  //! \sa report_charset(), set_html_report_stylesheet(), set_report_style()
  void set_report_charset(const std::string& cs);

  //! \brief Returns whether filename and line number information is included
  //! in test reports or not.
  //! \details The default is true.
  //! \return Boolean result value
  //!\sa set_report_loc(), report_style()
  bool report_loc() const;

  //! \brief Sets whether filenames and line number information is included
  //! in test reports or not.
  //! \details The default is true.
  //! \param[in] l Location information switch
  //!\sa set_report_loc(), report_style()
  void set_report_loc(bool l);

  //! \brief Returns the number of '-' characters used to create a
  //! 'breaker line' in the text reporting style.
  //! \details A 'breaker line' is a sequence of '-' characters used to create
  //! a visual separator in text report outputs. This setting applies only
  //! to the RS_TEXT_STD and RS_TEXT_VERBOSE report styles.
  //!
  //! A value of 0 will disable the appearence of breaker lines in the output.
  //! \return Number of characters
  //! \sa set_text_report_break_width(), report_style()
  int text_report_break_width() const;

  //! \brief Sets the number of '-' characters used to create a
  //! 'breaker line' in the text reporting style.
  //! \details A 'breaker line' is a sequence of '-' characters used to create
  //! a visual separator in text report outputs. This setting applies only
  //! to the RS_TEXT_STD and RS_TEXT_VERBOSE report style.
  //!
  //! A value of 0 will disable the appearence of breaker lines in the output.
  //! \param[in] bw Break width (num of chars)
  //! \sa text_report_break_width(), set_report_style()
  void set_text_report_break_width(int bw);

  //! \brief Gets the stylesheet name for HTML test reports.
  //! \details The field is used to populate the stylesheet field when
  //! generating HTML test reports. It is not used for other reports.
  //!
  //! The default value is an empty string which means that HTML reports do
  //! not use a stylesheet.
  //! \return Stylesheet name
  //! \sa set_html_report_stylesheet(), report_charset(), report_style()
  std::string html_report_stylesheet() const;

  //! \brief Sets the external stylesheet filename for HTML test reports.
  //! \details The field is used to populate the stylesheet field when
  //! generating HTML test reports. It is not used for other reports.
  //!
  //! Example:
  //!
  //! \code
  //! // Supply the path of a local stylesheet
  //! testdog::runner::global().set_stylesheet("./styles.css");
  //! \endcode
  //!
  //! This can be used to override the document's styles.
  //!
  //! The default value is an empty string which means that HTML reports do
  //! not use an external stylesheet.
  //! \param[in] ss Stylesheet filename
  //! \sa html_report_stylesheet(), set_report_charset(), set_report_style()
  void set_html_report_stylesheet(const std::string& ss);

  //! \brief Returns whether the HTML reports have an "author" column in
  //! the result tables.
  //! \details In multi-author environments, it is possible to associate
  //! author names with test cases. This setting controls whether a separate
  //! column is used for author names in in HTML reports tables.
  //!
  //! This setting applies to the RS_HTML_STD and RS_HTML_VERBOSE and
  //! RS_HTML_SUMMARY report styles only. The default value is true.
  //! \return Author flag
  //! \sa set_html_report_author_col(), text_report_break_width(), report_style()
  bool html_report_author_col() const;

  //! \brief Sets whether the HTML reports have an "author" column in
  //! the result tables.
  //! \details In multi-author environments, it is possible to associate
  //! author names with test cases. This setting controls whether a separate
  //! column is used for author names in in HTML reports tables.
  //!
  //! This setting applies to the RS_HTML_STD and RS_HTML_VERBOSE and
  //! RS_HTML_SUMMARY report styles only. The default value is true.
  //! \param[in] a Author flag
  //! \sa html_report_author_col(), set_text_report_break_width(),
  //! set_report_style()
  void set_html_report_author_col(bool a);

  //! @}
  //! @name Accessing Test Statistics
  //! @{

  //! \brief Returns a statistical result for the last test run.
  //! \details The result will pertain to the following input values:
  //! - ST_RAN - Number of tests executed in the test run.
  //! - ST_SKIPPED - Number of tests skipped (i.e. were disabled).
  //! - ST_PASSED - Number of tests that passed.
  //! - ST_FAILED - Number of tests that failed.
  //! - ST_ERRORS - Number of tests which implementation errors.
  //! - ST_PASS_RATE - Percentage of tests that passed.
  //! .
  //! The return value will be zero if no test run was performed prior to
  //! calling this method, or -1 if the input value is invalid.
  //! \param[in] st Required statistic
  //! \return Statistical count
  //! \sa test_result(), registered_count()
  int stat_result(result_stat_t st) const;

  //! \brief Returns the state of a given test case.
  //! \details Given a test name, this method returns one of the following
  //! values:
  //! - TR_NOT_RUN - Test was not run.
  //! - TR_PASSED - All test conditions passed OK.
  //! - TR_FAILED - One or more test conditions failed.
  //! - TR_TEST_ERROR - The test failed because of a possible implementation error.
  //! .
  //! If the test case was declared within a test suite, the suite
  //! name should prefix the test name with "::" as the separator. If the test
  //! case is not part of a suite, just the test name should be used.
  //!
  //! Example:
  //! \code
  //! test_result_t rslt = testdog::runner::global().test_result("SUITE_NAME::TEST_NAME");
  //! \endcode
  //!
  //! Test names are case sensitive.
  //! \param[in] tname Test case name
  //! \return Test result state
  //! \sa stat_result()
  test_result_t test_result(const std::string& tname) const;

  //! \brief Returns the date/time when the last test run started.
  //! \details The result is in the form of std::time_t and accurate
  //! only to the second.
  //!
  //! If no tests have been run, or the clear_results() method
  //! was called, the return value is zero.
  //! \return Test run start time
  //! \sa end_time(), test_duration()
  std::time_t start_time() const;

  //! \brief Returns the date/time when the last test run completed.
  //! \details The result is in the form of std::time_t and accurate
  //! only to the second.
  //!
  //! If no tests have been run, or the clear_results() method
  //! was called, the return value is zero.
  //! \return Test run end time
  //! \sa start_time(), duration()
  std::time_t end_time() const;

  //! \brief Returns the total duration of the last test run in seconds.
  //! \details If no tests have been run, or the clear_results() method
  //! was called, the return value is zero.
  //! \return Duration of the test run
  //! \sa start_time(), end_time()
  int duration() const;

  //! @}

};
//---------------------------------------------------------------------------
} // namespace
#endif // HEADER GUARD
//---------------------------------------------------------------------------
