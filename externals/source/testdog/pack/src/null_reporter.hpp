//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : null_reporter.hpp
// DESCRIPTION  : Concrete null reporter class (a silent sink for messages).
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
#ifndef TDOG_NULL_REPORTER_H
#define TDOG_NULL_REPORTER_H

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------
#include "basic_reporter.hpp"
#include <string>
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
// CLASS null_reporter
//---------------------------------------------------------------------------
class null_reporter : public basic_reporter
{
protected:

  // Protected members

public:

  // Constructor
  null_reporter(const runner* owner = 0)
    : basic_reporter(owner) {}

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
