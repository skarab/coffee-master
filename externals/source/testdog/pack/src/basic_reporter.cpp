//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : basic_reporter.cpp
// DESCRIPTION  : A base class for generating test reports.
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
#include "basic_reporter.hpp"
#include "testdog/runner.hpp"

#include <stdexcept>

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------
using namespace testdog;

//---------------------------------------------------------------------------
// CLASS basic_reporter : PROTECTED MEMBERS
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// CLASS basic_reporter : PUBLIC MEMBERS
//---------------------------------------------------------------------------
basic_reporter::basic_reporter(const runner* owner)
{
  // Constructor
  if (owner != 0)
  {
    // Assign explicit owner
    m_runner_ptr = owner;
  }
  else
  {
    // Never allow to happen
    throw std::logic_error("Runner owner is null");
  }
}
//---------------------------------------------------------------------------
basic_reporter::~basic_reporter()
{
  // Destructor
}
//---------------------------------------------------------------------------
const runner& basic_reporter::owner() const
{
  // Runner owner (cannot be null pointer)
  return *m_runner_ptr;
}
//---------------------------------------------------------------------------
