//---------------------------------------------------------------------------
// PROJECT      : T-DOG
// FILENAME     : runner.cpp
// DESCRIPTION  : Test runner class.
// COPYRIGHT    : Andy Thomas (C)
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
#include "testdog/runner.hpp"
#include "basic_reporter.hpp"
#include "null_reporter.hpp"
#include "text_reporter.hpp"
#include "xml_reporter.hpp"
#include "html_reporter.hpp"
#include "util.hpp"
#include <iostream>

using namespace testdog;
//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------
// None

//---------------------------------------------------------------------------
// CLASS runner : PROTECTED MEMBERS
//---------------------------------------------------------------------------
basic_test* runner::m_find_tc(const std::string& tname) const
{
  // Find test case and return pointer. Returns 0 if not found.

  // Simple search, but vector size is not expected to be huge.
  std::size_t sz = m_basic_tests.size();

  for(std::size_t n = 0; n < sz; ++n)
  {
    if (tname == m_basic_tests[n]->full_name())
    {
      return m_basic_tests[n];
    }
  }

  return 0;
}
//---------------------------------------------------------------------------
bool runner::m_suite_enabled(const std::string& sname) const
{
  // Returns the suite enabled state in the map. The map only really
  // hold a list of disabled suites, so if it is not found in the
  // map, the result is assumed to be true.
  suite_state_t::const_iterator it = m_suite_state_map.find(sname);

  if (it != m_suite_state_map.end())
  {
    return it->second;
  }

  return true;
}
//---------------------------------------------------------------------------
basic_reporter* runner::m_create_reporter(report_style_t rs) const
{
  // Creates an appropriate concrete instance of a
  // report generator class. Should be destroyed with
  // a call to delete when finished with it. Note
  // that if reporting is disabled, with return
  // a silent dummy instance.
  switch(rs)
  {
    case RS_TEXT_STD: return new text_reporter(this, false);
    case RS_TEXT_VERBOSE: return new text_reporter(this, true);
    case RS_XML: return new xml_reporter(this);
    case RS_HTML_STD: return new html_reporter(this, html_reporter::HTML_STD);
    case RS_HTML_VERBOSE: return new html_reporter(this, html_reporter::HTML_VERBOSE);
    case RS_HTML_SUMMARY: return new html_reporter(this, html_reporter::HTML_SUMMARY);
    default: return new null_reporter(this);
  }
}
//---------------------------------------------------------------------------
void runner::m_clear_results()
{
  // Clears all results of previous test run.
  m_tests_ran = 0;
  m_tests_skipped = 0;
  m_tests_failed = 0;
  m_tests_passed = 0;
  m_test_errors = 0;
  m_start_time = 0;
  m_end_time = 0;
  m_run_scope = RUN_NONE;

  std::size_t sz = m_basic_tests.size();
  for(std::size_t n = 0; n < sz; ++n)
  {
    m_basic_tests[n]->clear_results();
  }
}
//---------------------------------------------------------------------------
runner::runner()
{
  // Hidden constructor
  m_report_style = RS_TEXT_STD;
  m_report_loc = true;

  m_contains_suites = false;
  m_text_report_break_width = 65;
  m_html_report_author_col = true;
  m_global_time_limit = 0;

  // Zero results
  m_clear_results();
}
//---------------------------------------------------------------------------
// CLASS runner : PUBLIC MEMBERS
//---------------------------------------------------------------------------
runner::~runner()
{
    std::vector<basic_test*>::iterator i;
    for (i=m_basic_tests.begin();i!=m_basic_tests.end();++i)
        delete *i;
}
runner *gRunner;
//---------------------------------------------------------------------------
runner& runner::global()
{
  return *gRunner;
}
void runner::create()
{
	gRunner = new runner();
}
void runner::destroy()
{
    delete gRunner;
}
//---------------------------------------------------------------------------
std::string runner::project_name() const
{
  // Returns the test project name.
  return m_project_name;
}
//---------------------------------------------------------------------------
void runner::set_project_name(const std::string& pname)
{
  // Allows the setting of a name for the test project name.
  m_project_name = trim_str(pname);
}
//---------------------------------------------------------------------------
std::string runner::project_version() const
{
  // Returns the user supplied version string for the test project.
  return m_project_version;
}
//---------------------------------------------------------------------------
void runner::set_project_version(const std::string& ver)
{
  // Sets the version string of the project under test.
  m_project_version = trim_str(ver);
}
//---------------------------------------------------------------------------
void runner::register_test(test_case& tc)
{
  // Register a test case instance with the runner.

  // Call overloaded method
  register_test(tc.internal_downcast());
}
//---------------------------------------------------------------------------
void runner::register_test(basic_test& tc)
{
  // Register the test case with this class.
  // We checks to seethat the test does not already exist,
  // and if it does, we first remove it before then adding
  // it again. This could be used to re-sort the run-order.
  basic_test* tc_ptr = &tc;
  std::size_t sz = m_basic_tests.size();

  for(std::size_t n = 0; n < sz; ++n)
  {
    if (m_basic_tests[n] == tc_ptr)
    {
      // Erase current position
      m_basic_tests.erase(m_basic_tests.begin() + n);
      break;
    }
  }

  // Hold pointer
  m_basic_tests.push_back(tc_ptr);

  // Determine if suites are used
  std::string temp_str = tc_ptr->suite_name();
  m_contains_suites |= (m_prev_suite_name != temp_str);
  m_prev_suite_name = temp_str;
}
//---------------------------------------------------------------------------
int runner::registered_count() const
{
  // Returns the number of tests registered in the runner.
  return static_cast<int>(m_basic_tests.size());
}
//---------------------------------------------------------------------------
void runner::clear_tests()
{
  // Clears all tests registered with the runner.
  m_clear_results();

  m_basic_tests.clear();
  m_prev_suite_name.clear();
  m_contains_suites = false;
}
//---------------------------------------------------------------------------
bool runner::test_exists(const std::string& tname) const
{
  // Returns whether the test case with the given name exists.
  return (m_find_tc(tname) != 0);
}
//---------------------------------------------------------------------------
bool runner::suite_exists(const std::string& sname) const
{
  // Returns whether the test suite with the given name exists.
  std::string sn = trim_str(sname);
  std::size_t sz = m_basic_tests.size();

  for(std::size_t n = 0; n < sz; ++n)
  {
    if (m_basic_tests[n]->suite_name() == sn)
    {
      return true;
    }
  }

  return false;
}
//---------------------------------------------------------------------------
bool runner::contains_suites() const
{
  // Returns true if there are more than one test suites in the runner.
  return m_contains_suites;
}
//---------------------------------------------------------------------------
std::vector<std::string>& runner::enum_test_names(
  std::vector<std::string>& rslt_out) const
{
  // Enumerates the names of all test cases registered in the runner.
  rslt_out.clear();

  std::size_t sz = m_basic_tests.size();

  for(std::size_t n = 0; n < sz; ++n)
  {
    if (m_basic_tests[n]->suite_name().empty())
    {
      rslt_out.push_back(m_basic_tests[n]->test_name());
    }
    else
    {
      rslt_out.push_back(m_basic_tests[n]->suite_name() + "::" +
        m_basic_tests[n]->test_name());
    }
  }

  return rslt_out;
}
//---------------------------------------------------------------------------
std::vector<std::string>& runner::enum_suite_names(
  std::vector<std::string>& rslt_out) const
{
  // Enumerates the names of all test suites registered in the runner.
  rslt_out.clear();

  std::string last_name;
  std::size_t sz = m_basic_tests.size();

  for(std::size_t n = 0; n < sz; ++n)
  {
    if (n == 0 || last_name != m_basic_tests[n]->suite_name())
    {
      rslt_out.push_back(m_basic_tests[n]->suite_name());
      last_name = m_basic_tests[n]->suite_name();
    }
  }

  return rslt_out;
}
//---------------------------------------------------------------------------
bool runner::test_enabled(const std::string& tname) const
{
  // Returns whether the test case with the given name is enabled.
  basic_test* tc = m_find_tc(tname);
  return (tc != 0 && tc->enabled());
}
//---------------------------------------------------------------------------
void runner::set_test_enabled(const std::string& tname, bool e)
{
  // Allows an individual test case with the given name to be disabled
  // (or re-enabled) in the test run.
  basic_test* tc = m_find_tc(tname);

  if (tc != 0)
  {
    tc->set_enabled(e);
  }
}
//---------------------------------------------------------------------------
void runner::set_all_tests_enabled(bool e)
{
  // Sets the enabled states for all tests (in all suites).
  std::size_t sz = m_basic_tests.size();

  for(std::size_t n = 0; n < sz; ++n)
  {
    m_basic_tests[n]->set_enabled(e);
  }
}
//---------------------------------------------------------------------------
bool runner::suite_enabled(const std::string& sname) const
{
  // Returns whether the test suite with the given name is enabled.
  return (suite_exists(sname) && m_suite_enabled(trim_str(sname)));
}
//---------------------------------------------------------------------------
void runner::set_suite_enabled(const std::string& sname, bool e)
{
  // Allows the test suite with the given name to be disabled
  // (or re-enabled) in the test run.
  m_suite_state_map[trim_str(sname)] = e;
}
//---------------------------------------------------------------------------
void runner::set_all_suites_enabled(bool e)
{
  // Sets the enabled states for all suites.
  if (e)
  {
    // Clear from the disabled list
    m_suite_state_map.clear();
  }
  else
  {
    std::size_t sz = m_basic_tests.size();

    for(std::size_t n = 0; n < sz; ++n)
    {
      m_suite_state_map[m_basic_tests[n]->suite_name()] = false;
    }
  }
}
//---------------------------------------------------------------------------
int runner::run(run_scope_t scope, const std::string& name)
{
  // Run all tests, or just those specified.
  if (scope != RUN_NONE)
  {
    // Zero results
    m_clear_results();
    m_run_scope = scope;

    // Create reporter
    basic_reporter* reporter = m_create_reporter(m_report_style);

    try
    {
      // Trim name
      std::string n_str = trim_str(name);

      // Initialize timer
      m_start_time = std::time(0);

      // Write report header
      reporter->gen_start(std::cout);

      // Loop through all tests
      basic_test* tc = 0;
      std::size_t sz = m_basic_tests.size();

      for(std::size_t n = 0; n < sz; ++n)
      {
        tc = m_basic_tests[n];

        // Is the test in scope
        if (scope == RUN_ALL ||
          (scope == RUN_SUITE && n_str == tc->suite_name()) ||
          (scope == RUN_TEST && n_str == tc->full_name()))
        {
          // Is the test enabled?
          if (m_suite_enabled(tc->suite_name()) && tc->enabled())
          {
            // Run the test
            ++m_tests_ran;

            if (tc->run(m_global_time_limit))
            {
              // Test passed
              ++m_tests_passed;
            }
            else
            if (tc->state() == BTS_TEST_ERROR)
            {
              // There was a test error
              ++m_test_errors;
            }
            else
            {
              // One or more condition failures
              ++m_tests_failed;
            }
          }
          else
          {
            // Test skipped
            tc->set_skipped();
            ++m_tests_skipped;
          }

          // Write report
          reporter->gen_test(std::cout, tc);
        }
      }

      // Mark end time
      m_end_time = std::time(0);

      // Write report footer
      reporter->gen_end(std::cout);
    }
    catch(...)
    {
      // Unexpected exception
      delete reporter;
      std::cout << "\nABORTED - Unexpected exception in test library.\n";
      throw;
    }

    // Delete reporter
    delete reporter;

    if (m_tests_ran > 0)
    {
      // Return test run result
      return m_tests_failed + m_test_errors;
    }
  }

  // No test were ran
  return -1;
}
//---------------------------------------------------------------------------
run_scope_t runner::run_scope() const
{
  // Returns the "scope" used in the last call to the run() method.
  return m_run_scope;
}
//---------------------------------------------------------------------------
int runner::global_time_limit() const
{
  // Returns the global time limit for test cases in seconds.
  return m_global_time_limit;
}
//---------------------------------------------------------------------------
void runner::set_global_time_limit(int gc_sec)
{
  // Sets the global time limit for test cases in seconds.
  if (gc_sec > 0)
  {
    m_global_time_limit = gc_sec;
  }
  else
  {
    m_global_time_limit = 0;
  }
}
//---------------------------------------------------------------------------
report_style_t runner::report_style() const
{
  // Returns the report style written to STDOUT during the test run.
  return m_report_style;
}
//---------------------------------------------------------------------------
void runner::set_report_style(report_style_t rs)
{
  // Sets the report style written to STDOUT during the test run.
  m_report_style = rs;
}
//---------------------------------------------------------------------------
std::ostream& runner::generate_report(std::ostream& ro, report_style_t rs) const
{
  // Generates a test report pertaining to the last test run and writes
  // it to the supplied output stream.
  // Create reporter
  basic_reporter* reporter = m_create_reporter(rs);

  try
  {
    // Write report header
    reporter->gen_start(ro);

    // Loop through all tests
    std::size_t sz = m_basic_tests.size();

    for(std::size_t n = 0; n < sz; ++n)
    {
      reporter->gen_test(ro, m_basic_tests[n]);
    }

    // Write report footer
    reporter->gen_end(ro);
  }
  catch(...)
  {
    // Unexpected exception
    delete reporter;
    std::cout << "\nABORTED - Unexpected exception in test library.\n";
    throw;
  }

  // Delete reporter
  delete reporter;
  return ro;
}
//---------------------------------------------------------------------------
std::string runner::report_charset() const
{
  // Returns the test report character set encoding.
  return m_report_charset;
}
//---------------------------------------------------------------------------
void runner::set_report_charset(const std::string& cs)
{
  // Sets the test report character set encoding.
  m_report_charset = trim_str(cs);
}
//---------------------------------------------------------------------------
bool runner::report_loc() const
{
  // Returns whether filenames and line number information is included
  // in the test reports or not.
  return m_report_loc;
}
//---------------------------------------------------------------------------
void runner::set_report_loc(bool l)
{
  // Sets whether filenames and line number information is included
  // in the test reports or not.
  m_report_loc = l;
}
//---------------------------------------------------------------------------
int runner::text_report_break_width() const
{
  // Returns the number of '-' characters used to create a 'break bar'
  // in the text style of a test log output.
  return m_text_report_break_width;
}
//---------------------------------------------------------------------------
void runner::set_text_report_break_width(int bw)
{
  // Sets the number of '-' characters used to create a 'break bar'
  // in the text style of a test log output.
  if (bw < 0) bw = 0;
  if (bw > 500) bw = 500;
  m_text_report_break_width = bw;
}
//---------------------------------------------------------------------------
std::string runner::html_report_stylesheet() const
{
  // Gets the stylesheet name for HTML test reports.
  return m_html_report_stylesheet;
}
//---------------------------------------------------------------------------
void runner::set_html_report_stylesheet(const std::string& ss)
{
  // Sets the stylesheet name for HTML test reports.
  m_html_report_stylesheet = trim_str(ss);
}
//---------------------------------------------------------------------------
bool runner::html_report_author_col() const
{
  // Returns whether the HTML reports have an "author" column in
  // the result tables.
  return m_html_report_author_col;
}
//---------------------------------------------------------------------------
void runner::set_html_report_author_col(bool a)
{
  // Sets whether the HTML reports have an "author" column in
  // the result tables.
  m_html_report_author_col = a;
}
//---------------------------------------------------------------------------
int runner::stat_result(result_stat_t st) const
{
  // Returns a statistical result for the last test run.
  switch(st)
  {
    case ST_RAN: return m_tests_ran;
    case ST_SKIPPED: return m_tests_skipped;
    case ST_PASSED: return m_tests_passed;
    case ST_FAILED: return m_tests_failed;
    case ST_ERRORS: return m_test_errors;
    case ST_PASS_RATE:
      if (m_tests_ran > 0)
      {
        return 100 * m_tests_passed / m_tests_ran;
      }
      else
      {
        return 0;
      }
    default: return -1;
  }
}
//---------------------------------------------------------------------------
test_result_t runner::test_result(const std::string& tname) const
{
  // Returns the result state of a given test case.
  basic_test* tc = m_find_tc(tname);

  if (tc != 0)
  {
    // We must map between internal state type basic_test_state_t
    // and "public" test_result_t type. The basic_test_state_t exists
    // because of desire to keep implementation details away from the
    // users of this library.
    switch(tc->state())
    {
      case BTS_NOT_RUN:
      case BTS_SKIPPED: return TR_NOT_RUN;
      case BTS_PASSED: return TR_PASSED;
      case BTS_FAILED: return TR_FAILED;
      case BTS_TEST_ERROR: return TR_TEST_ERROR;
      default: break;
    }
  }

  return TR_NOT_EXIST;
}
//---------------------------------------------------------------------------
std::time_t runner::start_time() const
{
  // Returns the date/time when the test run was started.
  return m_start_time;
}
//---------------------------------------------------------------------------
std::time_t runner::end_time() const
{
  // Returns the date/time when the last test run completed.
  return m_end_time;
}
//---------------------------------------------------------------------------
int runner::duration() const
{
  // Returns the total duration of the test run in seconds.
  return static_cast<int>(m_end_time - m_start_time);
}
//---------------------------------------------------------------------------
