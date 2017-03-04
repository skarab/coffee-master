//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : util.hpp
// DESCRIPTION  : Misc utility routines.
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
#ifndef TDOG_UTIL_H
#define TDOG_UTIL_H

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------
#include <string>
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
// ROUTINES
//---------------------------------------------------------------------------
std::string trim_str(std::string s);
std::string int_to_str(int i, const std::string& format_str = "%d");
std::string double_to_str(double i, const std::string& format_str = "%f");
std::string iso_time(std::time_t t, bool utc = false);
std::string duration_str(int sec);
std::string str_replace(std::string src, const std::string& find,
  const std::string& rep);
std::string wide_to_str(const std::wstring& s);
std::string encode_esc(const std::string& s);
std::string xml_esc(std::string s);

//---------------------------------------------------------------------------
} // namespace
#endif // HEADER GUARD
//---------------------------------------------------------------------------
