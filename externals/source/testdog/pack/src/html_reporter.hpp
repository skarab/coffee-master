//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : html_reporter.hpp
// DESCRIPTION  : Concrete HTML reporting class.
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
#ifndef TDOG_HTML_REPORTER_H
#define TDOG_HTML_REPORTER_H

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------
#include "basic_reporter.hpp"
#include "text_reporter.hpp"
#include <string>
#include <ctime>
#include <vector>
#include <ostream>
#include <sstream>

//---------------------------------------------------------------------------
// DOCUMENTATION
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------

// Namespace
namespace testdog {

//---------------------------------------------------------------------------
// CLASS html_reporter
//---------------------------------------------------------------------------
class html_reporter : public basic_reporter
{
public:

  enum style_t
  {
    HTML_STD = 0,
    HTML_VERBOSE,
    HTML_SUMMARY
  };

protected:

  // Protected members
  style_t m_style;
  int m_indent_step;
  bool m_html_report_author_col;
  int m_indent_cnt;
  bool m_suite_added;
  std::string m_current_suite;
  text_reporter* m_text_reporter_ptr;
  std::vector<std::string> m_pass_trace;
  std::vector<std::string> m_fail_trace;
  std::vector<std::string> m_error_trace;
  std::vector<std::string> m_skipped_tests;

  inline std::string m_indent(int chrs = -1) const;
  std::ostream& m_generate_css(std::ostream& os);
  static std::string s_clean_id(const std::string& id_str);
  static std::string s_page_link(const std::string& id_str,
    const std::string& name_str);
  static std::string s_page_anchor(const std::string& id_str);
  static std::string s_rslt_str(const basic_test* tc);
  static std::string s_th_str(const std::string& content,
    const std::string& width = "");
  static std::string s_td_str(const std::string& content, bool bold = false,
    const std::string& class_id = "");
  static std::string s_cond_classid(bool passed);
  void m_build_trace(std::ostream& os, const std::vector<std::string>& trace_vec,
    const std::string& title_elem);
public:

  // Constructor
  html_reporter(const runner* owner = 0, html_reporter::style_t rs = HTML_STD);
  ~html_reporter();

  // Properties
  html_reporter::style_t style() const;
  void set_style(html_reporter::style_t s);
  int indent_step() const;
  void set_indent_step(int is);
  bool report_loc() const;
  void set_report_loc(bool rl);
  bool html_report_author_col() const;
  void set_html_report_author_col(bool a);

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
