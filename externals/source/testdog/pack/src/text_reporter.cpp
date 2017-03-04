//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : text_reporter.cpp
// DESCRIPTION  : Concrete text reporting class.
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
#include "text_reporter.hpp"
#include "testdog/runner.hpp"
#include "util.hpp"

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------
using namespace testdog;

namespace testdog {

// Report tag names
// Updating these can be used to form the basis for internationalization
const char* const PROJECT_NAME_LEADER = "PROJECT: ";
const char* const PROJECT_VERSION_LEADER = "Version: ";
const char* const REG_COUNT_LEADER = "Registered Tests: ";
const char* const SCOPE_LEADER = "Run Scope: ";
const char* const RUN_NONE_STR = "No Tests were Run";
const char* const RUN_ALL_STR = "All Tests";
const char* const RUN_SUITE_STR = "Specified Suite";
const char* const RUN_TEST_STR = "Specified Test Only";
const char* const START_TIME_LEADER = "Start Time: ";
const char* const TC_OUTPUT_SEP = " : ";
const char* const PASS_EVENT = "OK";
const char* const FAIL_EVENT = "FAIL";
const char* const ERROR_EVENT = "ERROR";
const char* const MSG_EVENT = "";
const char* const SUITE_LEADER = "TEST SUITE : ";
const char* const DEF_SUITE_NAME = "[Default Suite]";
const char* const TEST_STARTED_LEADER = "TEST STARTED: ";
const char* const AUTHOR_LEADER = "Author: ";
const char* const FILENAME_LEADER = "Filename: ";
const char* const TEST_END_LEADER = "Completed: ";
const char* const SKIP_SECTION = "SKIPPED TESTS";
const char* const STAT_SECTION = "STATISTICAL RESULTS";
const char* const STAT_RAN_LEADER = "TESTS RAN: ";
const char* const STAT_SKIPPED_LEADER = "SKIPPED: ";
const char* const STAT_PASSED_LEADER = "PASSED: ";
const char* const STAT_FAILED_LEADER = "FAILED: ";
const char* const STAT_ERRORS_LEADER = "TEST ERRORS: ";
const char* const STAT_PERC_LEADER = "PASS RATE: ";
const char* const END_TIME_LEADER = "END TIME: ";
const char* const DURATION_LEADER = "RUN DURATION: ";
const char* const BTS_NOT_RUN_STR = "TEST NOT RUN";
const char* const BTS_SKIPPED_STR = "SKIPPED";
const char* const BTS_PASSED_STR = "TEST PASSED";
const char* const BTS_FAILED_STR = "TEST FAILED";
const char* const BTS_ERROR_STR = "TEST ERROR";
}
//---------------------------------------------------------------------------
// CLASS text_reporter : PROTECTED MEMBERS
//---------------------------------------------------------------------------
void text_reporter::m_write_txt_break(std::ostream& os) const
{
  // Write text breaker (if any)
  if (m_break_text_width > 0)
  {
    os << std::string(m_break_text_width, '-');
    os << "\n";
  }
}
//---------------------------------------------------------------------------
std::string text_reporter::s_rslt_str(const basic_test* tc)
{
  // Overral result of test
  switch(tc->state())
  {
    case BTS_NOT_RUN: return BTS_NOT_RUN_STR;
    case BTS_SKIPPED: return BTS_SKIPPED_STR;
    case BTS_PASSED: return BTS_PASSED_STR;
    case BTS_FAILED: return std::string(BTS_FAILED_STR) + " (" +
      int_to_str(tc->fail_cnt()) + ")";
    case BTS_TEST_ERROR: return BTS_ERROR_STR;
    default: return "";
  }
}
//---------------------------------------------------------------------------
std::string text_reporter::s_event_str(event_type_t e)
{
  // Event string
  switch(e)
  {
    case ET_PASS : return PASS_EVENT;
    case ET_FAIL : return FAIL_EVENT;
    case ET_ERROR : return ERROR_EVENT;
    default: return MSG_EVENT;
  }
}
//---------------------------------------------------------------------------
// CLASS text_reporter : PUBLIC MEMBERS
//---------------------------------------------------------------------------
text_reporter::text_reporter(const runner* owner, bool vbs)
  : basic_reporter(owner)
{
  // Constructor
  m_verbose = vbs;

  // Set default values
  m_break_text_width = m_runner_ptr->text_report_break_width();
  m_report_loc = m_runner_ptr->report_loc();
  m_multi_suite = m_runner_ptr->contains_suites();
  m_testname_leader = true;
  m_suite_breaks = true;

  // Zero
  clear();
}
//---------------------------------------------------------------------------
bool text_reporter::verbose() const
{
  // Accessor
  return m_verbose;
}
//---------------------------------------------------------------------------
void text_reporter::set_verbose(bool v)
{
  // Mutator
  m_verbose = v;
}
//---------------------------------------------------------------------------
int text_reporter::break_text_width() const
{
  // Accessor
  return m_break_text_width;
}
//---------------------------------------------------------------------------
void text_reporter::set_break_text_width(int bw)
{
  // Mutator
  if (bw < 0) bw = 0;
  m_break_text_width = bw;
}
//---------------------------------------------------------------------------
bool text_reporter::report_loc() const
{
  // Accessor
  return m_report_loc;
}
//---------------------------------------------------------------------------
void text_reporter::set_report_loc(bool rl)
{
  // Mutator
  m_report_loc = rl;
}
//---------------------------------------------------------------------------
bool text_reporter::testname_leader() const
{
  // Accessor
  return m_testname_leader;
}
//---------------------------------------------------------------------------
void text_reporter::set_testname_leader(bool tn)
{
  // Mutator
  m_testname_leader = tn;
}
//---------------------------------------------------------------------------
bool text_reporter::suite_breaks() const
{
  // Accessor
  return m_suite_breaks;
}
//---------------------------------------------------------------------------
void text_reporter::set_suite_breaks(bool sb)
{
  // Mutator
  m_suite_breaks = sb;
}
//---------------------------------------------------------------------------
void text_reporter::clear()
{
  // Clear internal data
  m_current_suite.clear();
  m_skipped_tests.clear();
}
//---------------------------------------------------------------------------
std::ostream& text_reporter::gen_start(std::ostream& os)
{
  // Write header to stream
  clear();

  m_write_txt_break(os);

  // Name
  std::string temp_str = m_runner_ptr->project_name();
  if (!temp_str.empty()) os << PROJECT_NAME_LEADER << temp_str << "\n";

  // Version
  temp_str = m_runner_ptr->project_version();
  if (!temp_str.empty()) os << PROJECT_VERSION_LEADER << temp_str << "\n";

  // Registered tests
  os << REG_COUNT_LEADER << m_runner_ptr->registered_count() << "\n";

  // Scope
  os << SCOPE_LEADER;
  switch(m_runner_ptr->run_scope())
  {
    case RUN_NONE: os << RUN_NONE_STR << "\n"; break;
    case RUN_ALL: os << RUN_ALL_STR << "\n"; break;
    case RUN_SUITE: os << RUN_SUITE_STR << "\n"; break;
    case RUN_TEST: os << RUN_TEST_STR << "\n"; break;
    default: os << "\n"; break;
  }

  // Start time
  os << START_TIME_LEADER << iso_time(m_runner_ptr->start_time()) << "\n";

  m_write_txt_break(os);
  if (m_verbose) os << "\n";

  return os;
}
//---------------------------------------------------------------------------
std::ostream& text_reporter::gen_test(std::ostream& os, const basic_test* tc)
{
  // Write test case to stream. tc cannot be null.

  // Example verbose...
  // ucd_tests::surrogates : TEST STARTED
  // ucd_tests::surrogates : FILENAME - ucd.cpp
  // ucd_tests::surrogates : Beginning test [451]
  // ucd_tests::surrogates : OK - condition [463]
  // ucd_tests::surrogates : FAIL - mismatch [489]
  // ucd_tests::surrogates : ERROR - unhandled std::exception "ioerror"
  // ucd_tests::surrogates : TEST DURATION - 5 sec
  // ucd_tests::surrogates : TEST FAILED(2)

  // Non-verbose...
  // ucd_tests::surrogates : TEST PASSED OK
  //
  // or...
  // ucd_tests::surrogates : FILENAME - ucd.cpp
  // ucd_tests::surrogates : FAIL - mismatch [489]
  // ucd_tests::surrogates : ERROR - unhandled std::exception "ioerror"
  // ucd_tests::surrogates : TEST FAILED(2)
  const std::string TC_SEP = ": ";

  if (tc->state() == BTS_SKIPPED)
  {
    if (m_verbose)
    {
      // Record to skipped list
      m_skipped_tests.push_back(tc->full_name());
    }
  }
  else
  if (tc->state() != BTS_NOT_RUN)
  {
    // Initialize
    event_item eit;

    bool has_lnum = false;
    std::string line_str, type_str, result_str;
    std::size_t lsz = tc->event_log().size();

    // Test name leader
    std::string tn_str;
    if (m_testname_leader) tn_str = tc->full_name() + TC_OUTPUT_SEP;

    // Build a condition result string
    for(std::size_t n = 0; n < lsz; ++n)
    {
      eit = tc->event_log()[n];

      // Write failures only or everything if verbose is true
      if (m_verbose || eit.item_type == ET_FAIL || eit.item_type == ET_ERROR)
      {
        // Build upto "ucd_tests::surrogates : FAIL"
        type_str = s_event_str(eit.item_type);
        line_str = type_str;

        if (!type_str.empty() && !eit.msg_str.empty())
        {
          // Build upto "ucd_tests::surrogates : FAIL - "
          line_str += TC_SEP;
        }

        if (!eit.msg_str.empty())
        {
          // Build upto "ucd_tests::surrogates : FAIL - fail message"
          line_str += eit.msg_str;
        }

        if (m_report_loc && eit.line_num > 0)
        {
          // Build upto "ucd_tests::surrogates : FAIL - fail message [368]"
          has_lnum = true;

          if (!eit.msg_str.empty() || !type_str.empty())
          {
            line_str += " ";
          }

          line_str += "[" + int_to_str(eit.line_num) + "]";
        }

        if (!line_str.empty())
        {
          // EOL
          result_str += tn_str + line_str + "\n";
        }
      }
    }

    // Write suite header (verbose only)
    std::string tc_suite = tc->suite_name();
    if (m_multi_suite && tc_suite.empty()) tc_suite = DEF_SUITE_NAME;

    if (tc_suite != m_current_suite)
    {
      // Suite breaks
      m_current_suite = tc_suite;

      if (m_verbose && m_suite_breaks)
      {
        m_write_txt_break(os);
        os << SUITE_LEADER << tc_suite << "\n";
        m_write_txt_break(os);
      }
    }

    if (m_verbose)
    {
      // Write test case header (verbose only)
      os << tn_str << TEST_STARTED_LEADER << iso_time(tc->start_time()) << "\n";
      if (!tc->author().empty()) os << tn_str << AUTHOR_LEADER << tc->author() << "\n";
    }

    if (has_lnum)
    {
      // Write filename if we have line number information
      os << tn_str << FILENAME_LEADER << tc->filename() << "\n";
    }

    // Write main result section
    os << result_str;

    if (m_verbose)
    {
      // Duration
      os << tn_str << TEST_END_LEADER << duration_str(tc->test_duration()) << "\n";
    }

    // Final result
    os << tn_str << s_rslt_str(tc) << "\n";

    if (m_verbose) os << "\n";
  }

  return os;
}
//---------------------------------------------------------------------------
std::ostream& text_reporter::gen_end(std::ostream& os)
{
  // Write footer to stream
  std::size_t sk_sz = m_skipped_tests.size();

  if (m_verbose && sk_sz > 0)
  {
    // Build list of disabled tests
    os << "\n";
    m_write_txt_break(os);
    os << SKIP_SECTION << "\n";
    m_write_txt_break(os);

    for(std::size_t n = 0; n < sk_sz; ++n)
    {
      os << m_skipped_tests[n] << "\n";
    }

    os << "\n";
  }

  // Statistics
  os << "\n";
  m_write_txt_break(os);
  os << STAT_SECTION << "\n";
  m_write_txt_break(os);

  os << STAT_RAN_LEADER << m_runner_ptr->stat_result(ST_RAN) << "\n";
  os << STAT_SKIPPED_LEADER << m_runner_ptr->stat_result(ST_SKIPPED) << "\n";
  os << STAT_PASSED_LEADER << m_runner_ptr->stat_result(ST_PASSED) << "\n";
  os << STAT_FAILED_LEADER << m_runner_ptr->stat_result(ST_FAILED) << "\n";
  os << STAT_ERRORS_LEADER << m_runner_ptr->stat_result(ST_ERRORS) << "\n";
  os << STAT_PERC_LEADER << m_runner_ptr->stat_result(ST_PASS_RATE) << "%\n";
  m_write_txt_break(os);

  os << END_TIME_LEADER << iso_time(m_runner_ptr->end_time()) << "\n";
  os << DURATION_LEADER << duration_str(m_runner_ptr->duration()) << " (approx.)\n";
  m_write_txt_break(os);
  os << "\n";

  return os;
}
//---------------------------------------------------------------------------
