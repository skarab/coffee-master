//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : testdog/private/test_case.hpp
// DESCRIPTION  : Underlying assertion implementation for test cases.
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
#ifndef TDOG_TEST_CASE_H
#define TDOG_TEST_CASE_H

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------
#include "basic_test.hpp"

#include <string>

//---------------------------------------------------------------------------
// DOCUMENTATION
//---------------------------------------------------------------------------

// NOTES. In this class, we derive a class from basic_test and provide assert
// calls for use by the test macros. These will link to the basic_test event
// log. We intentionally provide this functionality separately and inherit
// basic_test privately so as to hide all methods of basic_test from the
// test macro implementation code.

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------

// Namespace
namespace testdog {

//---------------------------------------------------------------------------
// CLASS test_case
//---------------------------------------------------------------------------
class test_case : private basic_test
{
private:

  // Private members
  template <typename T>
  static T s_ascii_lower(T s)
  {
    // ASCII lower case template function
    std::size_t sz = s.size();

    for(std::size_t n = 0; n < sz; ++n)
    {
      if (s[n] >= 'A' && s[n] <= 'Z')
      {
        s[n] += 0x20;
      }
    }

    return s;
  }

protected:

  // Protected members
  // Need to keep m_run_impl() in protected scope.
  virtual void m_run_impl() = 0;

  // Main status outputs
  void m_fail(const std::string& s, int lnum)
    { m_push_msg(s, ET_FAIL, lnum); }
  void m_pass(const std::string& s, int lnum)
    { m_push_msg(s, ET_PASS, lnum); }
  void m_error(const std::string& s, int lnum)
    { m_push_msg(s, ET_ERROR, lnum); }

  // Message and value outputs
  void m_msg(const std::string& s, int lnum)
    { m_push_msg(s, ET_MSG, lnum); }
  void m_val(const std::string& s, const long& val, int lnum)
    { m_push_val(s, val, lnum); }
  void m_val(const std::string& s, const double& val, int lnum)
    { m_push_val(s, val, lnum); }
  void m_val(const std::string& s, const long double& val, int lnum)
    { m_push_val(s, val, lnum); }
  void m_val(const std::string& s, const std::string& val, int lnum)
    { m_push_val(s, val, lnum); }
  void m_val(const std::string& s, const std::wstring& val, int lnum)
    { m_push_val(s, val, lnum); }

  // Overloaded value outputs covering all basic types
  void m_val(const std::string& s, const unsigned long& val, int lnum)
    { m_push_val(s, static_cast<const long&>(val), lnum); }
  void m_val(const std::string& s, const int& val, int lnum)
    { m_push_val(s, static_cast<const long&>(val), lnum); }
  void m_val(const std::string& s, const unsigned int& val, int lnum)
    { m_push_val(s, static_cast<const long&>(val), lnum); }
  void m_val(const std::string& s, const short& val, int lnum)
    { m_push_val(s, static_cast<const long&>(val), lnum); }
  void m_val(const std::string& s, const unsigned short& val, int lnum)
    { m_push_val(s, static_cast<const long&>(val), lnum); }
  void m_val(const std::string& s, const bool& val, int lnum)
    { m_push_val(s, static_cast<const long&>(val), lnum); }
  void m_val(const std::string& s, const float& val, int lnum)
    { m_push_val(s, static_cast<const double&>(val), lnum); }
  void m_val(const std::string& s, const char* val, int lnum)
    { if (val != 0) m_push_val(s, static_cast<std::string>(val), lnum);
      else m_push_msg(s, ET_MSG, lnum); }
  void m_val(const std::string& s, const wchar_t* val, int lnum)
    { if (val != 0) m_push_val(s, static_cast<std::wstring>(val), lnum);
      else m_push_msg(s, ET_MSG, lnum); }

  // Assert
  template<typename T>
  bool m_assert(T condition, const std::string& s, int lnum)
    { if (!condition) m_push_msg(s, ET_FAIL, lnum);
      else m_push_msg(s, ET_PASS, lnum);
	  return condition; }

  // String assert equal assert
  void m_assert_str_equal(const std::string& a, const std::string& b,
	  const std::string& s, int lnum) {
      if (!m_assert((a == b), s, lnum))
      { m_push_val("a: %(s)", a, 0); m_push_val("b: %(s)", b, 0); }
  }

  void m_assert_str_equal(const std::wstring& a, const std::wstring& b,
    const std::string& s, int lnum) {
      if (!m_assert((a == b), s, lnum))
      { m_val("a: %(s)", a, 0); m_val("b: %(s)", b, 0); }
  }

  // String insensitive case assert
  void m_assert_stric_equal(const std::string& a, const std::string& b,
    const std::string& s, int lnum) {
      if (!m_assert((s_ascii_lower(a) == s_ascii_lower(b)), s, lnum))
      { m_val("a: %(s)", a, 0); m_val("b: %(s)", b, 0); }
  }
      
  void m_assert_stric_equal(const std::wstring& a, const std::wstring& b,
    const std::string& s, int lnum) {
      if (!m_assert((s_ascii_lower(a) == s_ascii_lower(b)), s, lnum))
      { m_val("a: %(s)", a, 0); m_val("b: %(s)", b, 0); }
  }

  // Integer assert equal
  void m_assert_int_equal(const long& a, const long& b, const std::string& s, int lnum) {
    if (!m_assert((a == b), s, lnum)) { m_val("a: %(i)", a, 0); m_val("b: %(i)", b, 0); }
  }

  // Floating point assert equal
  void m_assert_double_equal(const double& a, const double& b,
    const double& delta, const std::string& s, int lnum) {
      if (!m_assert(((b >= (a - delta)) && (b <= (a + delta))), s, lnum))
      { m_val("a: %(f)", a, 0); m_val("b: %(f)", b, 0); }
  }

  // Array assert equal
  template<typename TA, typename TB>
  void m_assert_array_equal(TA a, TB b, std::size_t cnt,
    const std::string& s, int lnum)
  {
    bool eq = true;
    for(std::size_t n = 0; n < cnt; ++n)
      if (a[n] != b[n]) {eq = false; break; }
    m_assert(eq, s, lnum);
  }

public:

  // Constructor
  test_case(const std::string& tname, const std::string& sname,
    const std::string& fname, bool auto_reg)
    : basic_test(tname, sname, fname, auto_reg) {}

  // Internal method to allow access to underlying
  // class type. The test_fixture class needs this.
  basic_test& internal_downcast() { return *this; }
};
//---------------------------------------------------------------------------
} // namespace
#endif // HEADER GUARD
//---------------------------------------------------------------------------
