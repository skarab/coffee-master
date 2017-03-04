//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : testdog/private/test_fixture.hpp
// DESCRIPTION  : Test fixture class.
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
#ifndef TDOG_TEST_FIXTURE_H
#define TDOG_TEST_FIXTURE_H

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------
#include "basic_test.hpp"

#include <exception>

//---------------------------------------------------------------------------
// DOCUMENTATION
//---------------------------------------------------------------------------

// NOTES. The "core_type" template type (below) is going to be a class derived
// from basic_test, which this class will sub-class in its run method.
// This purpose of this is to faciliate the wrapping of the user supplied
// object creation within a try-catch block in the public run() method.

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------

// Namespace
namespace testdog {

//---------------------------------------------------------------------------
// CLASS basic_test
//---------------------------------------------------------------------------
template <class core_type>
class test_fixture : public testdog::basic_test
{
protected:

  // Make concrete, but never called
  virtual void m_run_impl() {}

public:

  // Construction
  test_fixture(const std::string& tname, const std::string& sname,
    const std::string& fname, bool auto_reg)
    : basic_test(tname, sname, fname, auto_reg) {}

  // Run test override
  virtual bool run(int gc_sec)
  {
    // Run the test - wraps the run
    // method of a core basic_test  object
    bool rslt = false;

    if (m_enabled)
    {
      clear_results();

      try
      {
        // Mark time before creating core test
        // as its in constructor may fail.
        m_start_time = time(0);

        // Create unregistered test case which has
        // setup and tear-down construction.
        core_type test_core;

        // The core_type class inherits from
        // basic_test privately, so we need to use
        // a special method to downcast it to access
        // its hidden methods.
        basic_test& tc_ref = test_core.internal_downcast();

        // Run
        rslt = tc_ref.run(gc_sec);

        // Copy results back to owner
        m_fail_cnt = tc_ref.fail_cnt();
        m_state = tc_ref.state();
        m_start_time = tc_ref.start_time();
        m_test_duration = tc_ref.test_duration();

        // Must also copy any properties which could
        // be set during the test implementation
        m_time_limit = tc_ref.time_limit();
        m_global_limit_exempt = tc_ref.global_limit_exempt();
        m_log = tc_ref.event_log();
      }
      catch(const std::bad_alloc&)
      {
        // Unhandled bad_alloc
        // Note pushing LT_ERROR will set m_test_error
        m_push_msg("unhandled \"bad_alloc\" exception in test fixture", ET_ERROR);
      }
      catch(const std::exception& e)
      {
        // Unhandled std::exception
        m_push_msg("unhandled \"" + std::string(e.what()) +
          "\" exception in test fixture", ET_ERROR);
      }
      catch(...)
      {
        // Unhandled exception
        m_push_msg("unhandled exception in test fixture", ET_ERROR);
      }
    }

    return (rslt && m_state != BTS_TEST_ERROR);
  }
};
//---------------------------------------------------------------------------
} // namespace
#endif // HEADER GUARD
//---------------------------------------------------------------------------
