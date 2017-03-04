//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : xml_reporter.hpp
// DESCRIPTION  : Concrete XML reporting class.
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
#ifndef TDOG_XML_REPORTER_H
#define TDOG_XML_REPORTER_H

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------
#include "basic_reporter.hpp"
#include "testdog/private/basic_test.hpp"
#include <string>
#include <ostream>
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

//---------------------------------------------------------------------------
// CLASS xml_reporter
//---------------------------------------------------------------------------
class xml_reporter : public basic_reporter
{
protected:

  // Protected members
  bool m_report_loc;
  int m_indent_step;
  int m_indent_cnt;
  bool m_suite_added;
  std::string m_current_suite;
  inline std::string m_indent() const;
  static std::string s_timestamp(std::time_t t, const std::string& t_name = "");
  static std::string s_duration(int sec, const std::string& t_name = "");
  static std::string s_rslt_str(const basic_test* tc);
  static std::string s_event_str(const event_item& eit, bool rep_loc);
public:

  // Constructor
  xml_reporter(const runner* owner = 0);

  // Properties
  int indent_step() const;
  void set_indent_step(int is);
  bool report_loc() const;
  void set_report_loc(bool rl);

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
