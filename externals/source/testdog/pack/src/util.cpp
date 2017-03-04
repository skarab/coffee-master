//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : util.cpp
// DESCRIPTION  : Misc utility routines.
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
#include "util.hpp"
#include <cstdlib>
#include <cstdio>
#include <time.h>

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------
using namespace testdog;

//---------------------------------------------------------------------------
// INTERNAL ROUTINE
//---------------------------------------------------------------------------
template <class T>
static std::string s_sprintf(const char* format, T v)
{
  // INTERNAL STATIC ROUTINE
  // Wrapper for sprintf
  // Convert T to string, according to format_str,
  // where format_str has default "%d". Uses sprintf for
  // the conversion. For example, s_sprintf("0x%08X", 5)
  // will convert to 8 character hex string.

  // Format should be
  // %[flags][width][.precision][length]specifier
  // Where specifier is the most significant one and defines the type and
  // the interpretation of the value of the coresponding argument:

  // Specifier Output {Example}
  // d or i    Signed decimal integer {392}
  // e         Scientific notation (mantise/exponent) using e character {3.9265e+2}
  // E         Scientific notation (mantise/exponent) using E character {3.9265E+2}
  // f         Decimal floating point {392.65}
  // g         Use the shorter of %e or %f {392.65}
  // G         Use the shorter of %E or %f {392.65}
  // o         Signed octal {610}
  // u         Unsigned decimal integer {7235}
  // x         Unsigned hexadecimal integer {7fa}
  // X         Unsigned hexadecimal integer (capital letters) {7FA}
  // %         A % followed by another % character will write % to the string.
  static const std::size_t SPRINTF_BUF_SZ = 100;

  int sz;
  char buf[SPRINTF_BUF_SZ];

#if defined(_MSC_VER)
  // MS version
  sz = sprintf_s(buf, SPRINTF_BUF_SZ, format, v);
#elif (!COFFEE_COMPILER_MINGW && (__STDC_VERSION__ >= 199901L || __GNUC__ >= 3))
  // Safe version if we have it
  sz = std::snprintf(buf, SPRINTF_BUF_SZ, format, v);
#else
  sz = std::sprintf(buf, format, v);
#endif

  if (sz > 0 && sz < static_cast<int>(SPRINTF_BUF_SZ))
  {
    return std::string(buf, sz);
  }

  return "";
}
//---------------------------------------------------------------------------
// ROUTINES
//---------------------------------------------------------------------------
std::string testdog::trim_str(std::string s)
{
  // Trim left and right of spaces/control characters.
  std::size_t len = s.size();

  if (len > 0)
  {
    // Scan left
    for(std::size_t n = 0; ; ++n)
    {
      if (static_cast<unsigned char>(s[n]) > 0x20)
      {
        s.erase(0, n);
        break;
      }
      else
      if (n == len - 1)
      {
        s.clear();
        break;
      }
    }

    len = s.size();

    if (len > 0)
    {
      // Scan right
      for(std::size_t n = len - 1; ; --n)
      {
        if (static_cast<unsigned char>(s[n]) > 0x20)
        {
          if (n < len - 1)
          {
            s.erase(n + 1);
          }

          break;
        }
        else
        if (n == 0)
        {
          s.clear();
          break;
        }
      }
    }
  }

  return s;
}
//---------------------------------------------------------------------------
std::string testdog::int_to_str(int i, const std::string& format_str)
{
  // Convert integer to string, according to format_str.
  return s_sprintf<int>(format_str.c_str(), i);
}
//---------------------------------------------------------------------------
std::string testdog::double_to_str(double f, const std::string& format_str)
{
  // Convert integer to string
  return s_sprintf<double>(format_str.c_str(), f);
}
//---------------------------------------------------------------------------
std::string testdog::iso_time(std::time_t t, bool utc)
{
  // Returns ISO8601 local date/time as string of form: YYYY-MM-DD HH:MM:SS
  // Output is UTC if utc is true, or local otherwise.
  bool tm_ok;
  std::tm tm_rslt;

  // Initializing avoids warning
  tm_rslt.tm_year = 0;
  tm_rslt.tm_mon = 0;
  tm_rslt.tm_mday = 0;
  tm_rslt.tm_hour = 0;
  tm_rslt.tm_min = 0;
  tm_rslt.tm_sec = 0;

#if defined(_MSC_VER)

  // MSVC
  if (utc)
  {
    tm_ok = (gmtime_s(&tm_rslt, &t) == 0);
  }
  else
  {
    tm_ok = (localtime_s(&tm_rslt, &t) == 0);
  }

#elif defined(POSIX)

  // POSIX (included in "time.h")
  if (utc)
  {
    tm_ok = (gmtime_r(&t, &tm_rslt) != 0);
  }
  else
  {
    tm_ok = (localtime_r(&t, &tm_rslt) != 0);
  }

#else

  // Standard version (Used on MinGW)
  // NB. Generally, localtime()/gmtime() are not thread-safe.
  // Their results are a pointer to a static structure,
  // which means there won't be memory allocation
  // issues, but data could be overwritten at the same time
  // by concurrent threads. However, MinGW calls MSVC runtime,
  // and it appears this is threadsafe because the results point
  // to thread specific local buffers.
  // http://sources.redhat.com/ml/pthreads-win32/2005/msg00011.html
  // REF: http://old.nabble.com/Porting-localtime_r-and-gmtime_r-td15282276.html
  std::tm* t_ptr;

  if (utc)
  {
    t_ptr = std::gmtime(&t);
  }
  else
  {
    t_ptr = std::localtime(&t);
  }

  tm_ok = (t_ptr != 0);
  if (tm_ok) tm_rslt = *t_ptr;

#endif

  // Build result (or error)
  if (tm_ok)
  {
    return int_to_str(tm_rslt.tm_year + 1900, "%04d-") +
    int_to_str(tm_rslt.tm_mon + 1, "%02d-") +
    int_to_str(tm_rslt.tm_mday, "%02d ") +
    int_to_str(tm_rslt.tm_hour, "%02d:") +
    int_to_str(tm_rslt.tm_min, "%02d:") +
    int_to_str(tm_rslt.tm_sec, "%02d");
  }
  else
  {
    return "";
  }
}
//---------------------------------------------------------------------------
std::string testdog::duration_str(int sec)
{
  // Duration string, i.e. "5 min, 37 sec"
  std::string rslt;

  if (sec >= 0)
  {
    int sc = sec % 60; sec /= 60;
    int mn = sec % 60; sec /= 60;
    int hr = sec % 24; sec /= 24;
    int dy = sec;

    if (dy > 0) rslt += int_to_str(dy) + " day, ";
    if (dy > 0 || hr > 0) rslt += int_to_str(hr) + " hrs, ";
    if (dy > 0 || hr > 0 || mn > 0) rslt += int_to_str(mn) + " min, ";
    rslt += int_to_str(sc) + " sec";
  }

  return rslt;
}
//---------------------------------------------------------------------------
std::string testdog::str_replace(std::string src, const std::string& find,
  const std::string& rep)
{
  // Search & replace on src string
  if (!find.empty() && find.length() <= src.length() && find != rep)
  {
    std::size_t p = 0;
    std::size_t rl = rep.length();
    std::size_t fl = find.length();

    do
    {
      p = src.find(find, p);

      if (p != std::string::npos)
      {
        src.replace(p, fl, rep);
        p += rl;
      }
    } while(p != std::string::npos);
  }

  return src;
}
//---------------------------------------------------------------------------
std::string testdog::wide_to_str(const std::wstring& s)
{
  // Wide to narrow
  unsigned int c;
  std::size_t sz = s.size();

  std::string rslt;
  rslt.reserve(sz);

  for(std::size_t n = 0; n < sz; ++n)
  {
    c = static_cast<unsigned int>(s[n]);

    if (c < 0x80)
    {
      rslt += static_cast<char>(c);
    }
    else
    if (c <= 0xFFFF)
    {
      rslt += "\\u" + int_to_str(c, "%04X");
    }
    else
    {
      rslt += "\\U" + int_to_str(c, "%08X");
    }

  }

  return rslt;
}
//---------------------------------------------------------------------------
std::string testdog::encode_esc(const std::string& s)
{
  // Replaces common character values with escape sequences and
  // returns the result.
  unsigned char c;
  std::size_t sz = s.size();

  std::string rslt;
  rslt.reserve(sz);

  for(std::size_t n = 0; n < sz; ++n)
  {
    c = static_cast<unsigned char>(s[n]);

    if (c > 0x1F)
    {
      rslt += static_cast<char>(c);
    }
    else
    {
      switch(c)
      {
        case 0x09: rslt += "\\t"; break;
        case 0x0A: rslt += "\\n"; break;
        case 0x0B: rslt += "\\v"; break;
        case 0x0C: rslt += "\\f"; break;
        case 0x0D: rslt += "\\r"; break;
        default: rslt += "\\x" + int_to_str(c, "%02X"); break;
      }
    }
  }

  return rslt;
}
//---------------------------------------------------------------------------
std::string testdog::xml_esc(std::string s)
{
  // Escapse XML characters
  s = str_replace(s, "&", "&amp;");
  s = str_replace(s, "<", "&lt;");
  s = str_replace(s, ">", "&gt;");
  s = str_replace(s, "'", "&apos;");
  s = str_replace(s, "\"", "&quot;");
  return s;
}
//---------------------------------------------------------------------------
