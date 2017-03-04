//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : text_reporter.hpp
// DESCRIPTION  : Concrete text reporting class.
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
#ifndef TDOG_TEXT_REPORTER_H
#define TDOG_TEXT_REPORTER_H

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------
#include "basic_reporter.hpp"
#include "testdog/private/basic_test.hpp"
#include <string>
#include <vector>
#include <ostream>

//---------------------------------------------------------------------------
// DOCUMENTATION
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------

// Namespace
namespace testdog {

//---------------------------------------------------------------------------
// CLASS text_reporter
//---------------------------------------------------------------------------
class text_reporter : public basic_reporter
{
protected:

  // Protected members
  bool m_verbose;
  int m_break_text_width;
  bool m_report_loc;
  bool m_multi_suite;
  std::string m_current_suite;
  std::vector<std::string> m_skipped_tests;

  // For use by html_reporter
  bool m_testname_leader;
  bool m_suite_breaks;

  void m_write_txt_break(std::ostream& os) const;
  static std::string s_rslt_str(const basic_test* tc);
  static std::string s_event_str(event_type_t e);
public:

  // Constructor
  text_reporter(const runner* owner = 0, bool vbs = true);

  // Properties
  bool verbose() const;
  void set_verbose(bool v);
  int break_text_width() const;
  void set_break_text_width(int bw);
  bool report_loc() const;
  void set_report_loc(bool rl);
  bool testname_leader() const;
  void set_testname_leader(bool tn);
  bool suite_breaks() const;
  void set_suite_breaks(bool sb);

  // Report generator methods
  virtual void clear();
  virtual std::ostream& gen_start(std::ostream& os);
  virtual std::ostream& gen_test(std::ostream& os, const basic_test* tc);
  virtual std::ostream& gen_end(std::ostream& os);
};
//---------------------------------------------------------------------------
} // namespace
#endif // HEADER GUARD
//---------------------------------------------------------------------------
