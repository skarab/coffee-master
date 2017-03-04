//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : basic_reporter.hpp
// DESCRIPTION  : A base class for generating test reports.
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
#ifndef TDOG_BASIC_REPORTER_H
#define TDOG_BASIC_REPORTER_H

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------
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

// Forward declarations
class runner;
class basic_test;

//---------------------------------------------------------------------------
// CLASS basic_reporter
//---------------------------------------------------------------------------
class basic_reporter
{
protected:

  // Protected members
  const runner* m_runner_ptr;

public:

  // Construction
  basic_reporter(const runner* owner = 0);
  virtual ~basic_reporter();

  // Access owner
  const runner& owner() const;

  // Report generator methods
  // Must be defined in concrete classes
  virtual void clear() = 0;
  virtual std::ostream& gen_start(std::ostream& os) = 0;
  virtual std::ostream& gen_test(std::ostream& os, const basic_test* tc) = 0;
  virtual std::ostream& gen_end(std::ostream& os) = 0;
};
//---------------------------------------------------------------------------
} // namespace
#endif // HEADER GUARD
//---------------------------------------------------------------------------
