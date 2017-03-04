//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : testdog/private/basic_test.hpp
// DESCRIPTION  : Base class for all test cases.
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
#ifndef TDOG_BASIC_TEST_H
#define TDOG_BASIC_TEST_H

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include <ctime>

//---------------------------------------------------------------------------
// DOCUMENTATION
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------

// Namespace
namespace testdog {

// Enum for result state
enum basic_test_state_t
{
  BTS_NOT_RUN = 0,
  BTS_SKIPPED,
  BTS_PASSED,
  BTS_FAILED,
  BTS_TEST_ERROR
};

// Enumerator designating the type of log item
enum event_type_t {
  ET_PASS,        // <- pass message
  ET_FAIL,        // <- fail message
  ET_MSG,         // <- informational message
  ET_ERROR        // <- unexpected error in test case (i.e. unhandled exception)
};

// Structure type hold details of an event
struct event_item
{
  // Public members
  std::string msg_str;    // <- message string
  event_type_t item_type; // <- type of item
  int line_num;           // <- line no. where msg was generated

  // Constructor
  event_item(const std::string& mstr = "", event_type_t t = ET_MSG, int lnum = 0)
    : msg_str(mstr), item_type(t), line_num(lnum) {}
};

// A vector type to hold an array of events
typedef std::vector<event_item> event_vector;

//---------------------------------------------------------------------------
// CLASS basic_test
//---------------------------------------------------------------------------
class basic_test
{
protected:

  // Protected data
  bool m_enabled;
  int m_fail_cnt;
  basic_test_state_t m_state;
  std::string m_test_name;
  std::string m_suite_name;
  std::string m_full_name;
  std::string m_filename;
  std::string m_author;
  std::time_t m_start_time;
  int m_test_duration;
  int m_time_limit;
  bool m_global_limit_exempt;
  event_vector m_log;

  // We use this to hold a list
  // mapping our own integer tag
  // specifiers to standard printf ones
  // See init_tags()
  struct itag
  {
    std::string tag;
    std::string spec;
    itag(const std::string& t, const std::string& s)
      : tag(t), spec(s) {}
  };

  std::vector<itag> m_itag_vect;

  // Protected methods
  void m_initialize(const std::string& tname, const std::string& sname,
    const std::string& fname, bool reg);
  void m_init_tags();
  void m_push_msg(const std::string& s, event_type_t t, int lnum = 0);
  void m_push_val(const std::string& s, const long& val, int lnum = 0);
  void m_push_val(const std::string& s, const double& val, int lnum = 0);
  void m_push_val(const std::string& s, const long double& val, int lnum = 0);
  void m_push_val(const std::string& s, const std::string& val, int lnum = 0);
  void m_push_val(const std::string& s, const std::wstring& val, int lnum = 0);

  
  // Virtual run method. Must be defined by test macro.
  virtual void m_run_impl() = 0;

public:

  // Construction
  basic_test(const std::string& tname, const std::string& sname,
    const std::string& fname, bool auto_reg);
  virtual ~basic_test();

  // Properties
  std::string test_name() const;
  std::string suite_name() const;
  std::string full_name() const;
  const char* full_name_cstr();
  std::string filename() const;
  bool enabled() const;
  void set_enabled(bool e);

  std::string author() const;
  void set_author(const std::string& a);
  int time_limit() const;
  void set_time_limit(int secs);
  bool global_limit_exempt() const;
  void set_global_limit_exempt(bool e);

  // Run test - a wrapper for m_run_impl(). Returns true
  // if the test ran successfully without failure or error.
  virtual bool run(int gc_sec);
  void set_skipped();

  // Clear results
  void clear_results();

  // Test condition stats
  basic_test_state_t state() const;
  std::time_t start_time() const;
  int test_duration() const;
  int fail_cnt() const;

  // Access to test log
  const event_vector& event_log() const;
};
//---------------------------------------------------------------------------
} // namespace
#endif // HEADER GUARD
//---------------------------------------------------------------------------
