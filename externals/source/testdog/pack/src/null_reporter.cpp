//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : null_reporter.cpp
// DESCRIPTION  : Concrete null reporter class (a silent sink for messages).
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
#include "null_reporter.hpp"

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------
using namespace testdog;

//---------------------------------------------------------------------------
// CLASS null_reporter : PUBLIC MEMBERS
//---------------------------------------------------------------------------
std::ostream& null_reporter::gen_start(std::ostream& os)
{
  // Does nothing - just a silent sink
  return os;
}
//---------------------------------------------------------------------------
std::ostream& null_reporter::gen_test(std::ostream& os, const basic_test* tc)
{
  // Does nothing - just a silent sink
  // Checking tc prevent -W warning
  if (tc != 0) while(false){}

  return os;
}
//---------------------------------------------------------------------------
std::ostream& null_reporter::gen_end(std::ostream& os)
{
  // Does nothing - just a silent sink
  return os;
}
//---------------------------------------------------------------------------
void null_reporter::clear()
{
  // Does nothing - just a silent sink
}
//---------------------------------------------------------------------------
