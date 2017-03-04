//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : basic_test.cpp
// DESCRIPTION  : Base class for all test cases.
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
#include "testdog/private/basic_test.hpp"
#include "testdog/runner.hpp"
#include "util.hpp"

#include <cfloat>
#include <climits>
#include <exception>

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------
using namespace testdog;

// Tags
const char* const SINT_TAG = "%(i)";
const char* UINT_TAG = "%(u)";
const char* CHAR_TAG = "%(c)";
const char* OCT_TAG = "%(o)";
const char* hex_TAG = "%(x)";
const char* hex2_TAG = "%(02x)";
const char* hex4_TAG = "%(04x)";
const char* hex8_TAG = "%(08x)";
const char* hex16_TAG = "%(16x)";
const char* HEX_TAG = "%(X)";
const char* HEX2_TAG = "%(02X)";
const char* HEX4_TAG = "%(04X)";
const char* HEX8_TAG = "%(08X)";
const char* HEX16_TAG = "%(16X)";

const char* BOOL_TAG = "%(b)";
const char* FLOAT_TAG = "%(f)";
const char* STR_TAG = "%(s)";
const char* ESC_TAG = "%(k)";

//---------------------------------------------------------------------------
// CLASS basic_test : PROTECTED MEMBERS
//---------------------------------------------------------------------------
void basic_test::m_initialize(const std::string& tname, const std::string& sname,
  const std::string& fname, bool auto_reg)
{
  // Initialize members
  m_enabled = true;
  m_test_name = trim_str(tname);
  m_suite_name = trim_str(sname);
  m_filename = trim_str(fname);
  m_time_limit = 0;
  m_global_limit_exempt = false;

  if (!m_suite_name.empty()) m_full_name = m_suite_name + "::";
  m_full_name += m_test_name;

  // Zero result counters
  clear_results();

  if (auto_reg)
  {
    // Register with test_runner if reg flag is true.
    // The ability NOT to auto-register is important
    // in the implementation of test fixtures.
    runner::global().register_test(*this);
  }
}
//---------------------------------------------------------------------------
void basic_test::m_init_tags()
{
  // Initialize tag mappings (done once only)
  if (m_itag_vect.size() == 0)
  {
    m_itag_vect.push_back(itag(SINT_TAG, "%i"));
    m_itag_vect.push_back(itag(UINT_TAG, "%u"));
    m_itag_vect.push_back(itag(CHAR_TAG, "%c"));
    m_itag_vect.push_back(itag(OCT_TAG, "%o"));
    m_itag_vect.push_back(itag(hex_TAG, "%x"));
    m_itag_vect.push_back(itag(hex2_TAG, "%02x"));
    m_itag_vect.push_back(itag(hex4_TAG, "%04x"));
    m_itag_vect.push_back(itag(hex8_TAG, "%08x"));
    m_itag_vect.push_back(itag(hex16_TAG, "%16x"));
    m_itag_vect.push_back(itag(HEX_TAG, "%X"));
    m_itag_vect.push_back(itag(HEX2_TAG, "%02X"));
    m_itag_vect.push_back(itag(HEX4_TAG, "%04X"));
    m_itag_vect.push_back(itag(HEX8_TAG, "%08X"));
    m_itag_vect.push_back(itag(HEX16_TAG, "%16X"));
  }
}
//---------------------------------------------------------------------------
void basic_test::m_push_msg(const std::string& s, event_type_t t, int lnum)
{
  // Push item onto the log vector
  m_log.push_back(event_item(trim_str(s), t, lnum));

  // Update stats
  switch(t)
  {
    case ET_FAIL:
      ++m_fail_cnt;
      if (m_state != BTS_TEST_ERROR) m_state = BTS_FAILED;
      break;
    case ET_ERROR:
      m_state = BTS_TEST_ERROR;
      break;
    default: break;
  }
}
//---------------------------------------------------------------------------
void basic_test::m_push_val(const std::string& s, const long& val, int lnum)
{
  // Push value string onto the log vector
  // Writes a long type integer value to the log.
  // We support a number of pre-selected integer tag values. These
  // are similar to those used by printf (i.e. "%d"). However, we
  // do not want to allow user input to reach our int_to_str()
  // call for type safety reasons, as it utilizes sprintf(). So
  // we perform an explicit search and replace on our mappings.
  std::string fs = s;

  // Initialize tags
  m_init_tags();

  // Enumerate through array
  std::size_t sz = m_itag_vect.size();

  for(std::size_t n = 0; n < sz; ++n)
  {
    if (s.find(m_itag_vect[n].tag) != std::string::npos)
    {
      // Translate if required
      fs = str_replace(fs, m_itag_vect[n].tag,
        int_to_str(val, m_itag_vect[n].spec));
    }
  }

  // Special "boolean" tag
  if (s.find(BOOL_TAG) != std::string::npos)
  {
    if (val != 0)
    {
      fs = str_replace(fs, BOOL_TAG, "true");
    }
    else
    {
      fs = str_replace(fs, BOOL_TAG, "false");
    }
  }

  m_push_msg(fs, ET_MSG, lnum);
}
//---------------------------------------------------------------------------
void basic_test::m_push_val(const std::string& s, const double& val, int lnum)
{
  // Push value string onto the log vector
  std::string fs = s;

  if (s.find(FLOAT_TAG) != std::string::npos)
  {
    // Replace
    std::string fs = str_replace(s, FLOAT_TAG, double_to_str(val));
  }

  if (val >= INT_MIN && val <= INT_MAX)
  {
    // Convert to integer
    m_push_val(fs, static_cast<const long&>(val), lnum);
  }

  m_push_msg(fs, ET_MSG, lnum);
}
//---------------------------------------------------------------------------
void basic_test::m_push_val(const std::string& s, const long double& val,
  int lnum)
{
  // Push value string onto the log vector
  if (val >= DBL_MIN && val <= DBL_MAX)
  {
    // Limit to double range
    m_push_val(s, static_cast<const double&>(val), lnum);
  }
  else
  {
    // Replace
    m_push_msg(str_replace(s, FLOAT_TAG, "ERANGE"), ET_MSG, lnum);
  }
}
//---------------------------------------------------------------------------
void basic_test::m_push_val(const std::string& s, const std::string& val,
  int lnum)
{
  // Push value string onto the log vector
  std::string fs = str_replace(s, STR_TAG, val);

  if (s.find(ESC_TAG) != std::string::npos) // < search in s, not fs
  {
    // Replace
    fs = str_replace(fs, ESC_TAG, encode_esc(val));
  }

  m_push_msg(fs, ET_MSG, lnum);
}
//---------------------------------------------------------------------------
void basic_test::m_push_val(const std::string& s, const std::wstring& val,
  int lnum)
{
  // Push value string onto the log vector
  m_push_val(s, wide_to_str(val), lnum);
}
//---------------------------------------------------------------------------
// CLASS basic_test : PUBLIC MEMBERS
//---------------------------------------------------------------------------
basic_test::basic_test(const std::string& tname, const std::string& sname,
  const std::string& fname, bool auto_reg)
{
  // Constructor
  m_initialize(tname, sname, fname, auto_reg);
}
//---------------------------------------------------------------------------
basic_test::~basic_test()
{
  // Destructor
}
//---------------------------------------------------------------------------
std::string basic_test::test_name() const
{
  // Accessor to test name
  return m_test_name;
}
//---------------------------------------------------------------------------
std::string basic_test::suite_name() const
{
  // Accessor to suite name
  return m_suite_name;
}
//---------------------------------------------------------------------------
std::string basic_test::full_name() const
{
  // The suite::test_name as a c-style string.
  return m_full_name;
}
//---------------------------------------------------------------------------
const char* basic_test::full_name_cstr()
{
  // The suite::test_name as a c-style string.
  return m_full_name.c_str();
}
//---------------------------------------------------------------------------
std::string basic_test::filename() const
{
  // Accessor to file name where test is defined
  return m_filename;
}
//---------------------------------------------------------------------------
bool basic_test::enabled() const
{
  // Accessor - enabled
  return m_enabled;
}
//---------------------------------------------------------------------------
void basic_test::set_enabled(bool e)
{
  // Mutator - enabled
  m_enabled = e;
}
//---------------------------------------------------------------------------
std::string basic_test::author() const
{
  // Accessor to author name
  return m_author;
}
//---------------------------------------------------------------------------
void basic_test::set_author(const std::string& a)
{
  // Mutator to author name
  m_author = trim_str(a);
}
//---------------------------------------------------------------------------
int basic_test::time_limit() const
{
  // Accessor to time contraint
  return m_time_limit;
}
//---------------------------------------------------------------------------
void basic_test::set_time_limit(int tc)
{
  // Mutator to time limit
  m_time_limit = tc;
}
//---------------------------------------------------------------------------
bool basic_test::global_limit_exempt() const
{
  // Accessor global time limit exemption
  return m_global_limit_exempt;
}
//---------------------------------------------------------------------------
void basic_test::set_global_limit_exempt(bool e)
{
  // Mutator to global time limit exemption
  m_global_limit_exempt = e;
}
//---------------------------------------------------------------------------
bool basic_test::run(int gc_sec)
{
  // Run the test - a wrapper for m_run() which must
  // be defined by a concrete test instance.
  if (m_enabled)
  {
    try
    {
      // Initialize
      clear_results();
      m_state = BTS_PASSED;
      m_start_time = std::time(0);

      // Run
      m_run_impl();
      m_test_duration = static_cast<int>(std::time(0) - m_start_time);

      // Time constraints
      if (m_time_limit > 0 && m_test_duration > m_time_limit)
      {
        // Local time constraint failure
        m_push_msg("local time limit of " + int_to_str(m_time_limit) + " sec exceeded", ET_FAIL);
      }

      if (gc_sec > 0 && m_time_limit <= 0 &&
        !m_global_limit_exempt && m_test_duration > gc_sec)
      {
        // Global time constraint failure
        m_push_msg("global time limit of " + int_to_str(gc_sec) + " sec exceeded", ET_FAIL);
      }
    }
    catch(const std::bad_alloc&)
    {
      // Unhandled bad_alloc
      // Note pushing ET_ERROR will set m_test_error
      m_push_msg("unhandled \"bad_alloc\" exception in test execution", ET_ERROR);
    }
    catch(const std::exception& e)
    {
      // Unhandled std::exception
      m_push_msg("unhandled \"" + std::string(e.what()) +
        "\" exception in test execution", ET_ERROR);
    }
    catch(...)
    {
      // Unhandled exception
      m_push_msg("unhandled exception in test execution", ET_ERROR);
    }
  }
  else
  {
    m_state = BTS_SKIPPED;
  }

  return (m_state == BTS_PASSED);
}
//---------------------------------------------------------------------------
void basic_test::set_skipped()
{
  // Set skipped state
  m_state = BTS_SKIPPED;
}
//---------------------------------------------------------------------------
void basic_test::clear_results()
{
  // Clear results
  m_fail_cnt = 0;
  m_state = BTS_NOT_RUN;
  m_start_time = 0;
  m_test_duration = 0;
  m_log.clear();
}
//---------------------------------------------------------------------------
basic_test_state_t basic_test::state() const
{
  // Test state
  return m_state;
}
//---------------------------------------------------------------------------
std::time_t basic_test::start_time() const
{
  // Test start time
  return m_start_time;
}
//---------------------------------------------------------------------------
int basic_test::test_duration() const
{
  // Test duration in ms
  return m_test_duration;
}
//---------------------------------------------------------------------------
int basic_test::fail_cnt() const
{
  // The number of fail conditions
  return m_fail_cnt;
}
//---------------------------------------------------------------------------
const event_vector& basic_test::event_log() const
{
  // Access to test log
  return m_log;
}
//---------------------------------------------------------------------------
