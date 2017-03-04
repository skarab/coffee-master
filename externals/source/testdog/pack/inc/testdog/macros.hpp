//---------------------------------------------------------------------------
// PROJECT      : TEST-DOG
// FILENAME     : testdog/macros.hpp
// DESCRIPTION  : Test macros
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
#ifndef TDOG_MACROS_H
#define TDOG_MACROS_H

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------

#ifdef COFFEE_COMPILER_MINGW
    #include "stdint-gcc.h"
#endif

#include <string>
#include "private/test_case.hpp"
#include "private/test_fixture.hpp"

//---------------------------------------------------------------------------
// DOCUMENTATION
//---------------------------------------------------------------------------
//! \file testdog/macros.hpp
//! \brief TEST-DOG test macros.

//---------------------------------------------------------------------------
// DECLARATIONS
//---------------------------------------------------------------------------

// Auto registration flag
namespace testdog {
#ifdef TDOG_DISABLE_AUTO_REG
  const bool AUTO_REG = false;
#else
  const bool AUTO_REG = true;
#endif
}

// Default namespaced suite name
namespace testdog_suite {
  const char* const SUITE_NAME = "";
}

//---------------------------------------------------------------------------
// TEST MACROS
//---------------------------------------------------------------------------

//! @name Test Case Declaration & Setup Macros
//! @{

//! \brief Creates a test case and registers it with a global instance of
//! of the TEST-DOG test runner class.
//! \details A test can be created as follows:
//!
//! \code
//! TDOG_TEST_CASE(number_test)
//! {
//!   int num_beast = 665;
//!   TDOG_ASSERT_EQUAL(666, ++num_beast); // Passes
//! }
//! \endcode
//!
//! The test code should not return any result.
//!
//! The test name should not contain spaces, as it will be used internally to
//! form the basis of a C++ data type.
//!
//! The test case will automatically be register* with the global
//! testdog::runner class, and the test can then be executed by calling the
//! runner::run() method.
//!
//! Tests are normally executed in the runner in the order that they
//! are declared. However, tests can also be executed individually, as follows:
//!
//! \code
//! testdog::runner::global().run(RUN_TEST, "number_test");
//! \endcode
//!
//! Additionally, tests can be grouped together within "test suites" as follows:
//!
//! \code
//! TDOG_TEST_SUITE(beast_suite)
//! {
//!   TDOG_TEST_CASE(number_test)
//!   {
//!     int num_beast = 665;
//!     TDOG_ASSERT_EQUAL(666, ++num_beast); // Passes
//!   }
//! }
//! \endcode
//!
//! Test suites allow test cases to be run or disabled as a group.
//!
//! *It is also possible to disable the automatic registration of test cases.
//! See the runner::register_test() method for further information.
//! \param[in] test_name The test name
//! \sa TDOG_TEST_SUITE(), TDOG_TEST_FIXTURE()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_TEST_CASE(test_name)
#else
  // Actual
  #define TDOG_TEST_CASE(test_name) \
  class test_name##_tdog_test_class : public testdog::test_case \
  { \
  private: \
    virtual void m_run_impl(); \
  public: \
    test_name##_tdog_test_class() \
      : test_case(#test_name, testdog_suite::SUITE_NAME, __FILE__, \
        testdog::AUTO_REG) {} \
  }; /*test_name##_tdog_test_inst;*/ \
  void test_name##_tdog_test_class::m_run_impl()
#endif

//! \brief Creates a test with custom data and setup/teardown functionality.
//! \details This macro is similar to TDOG_TEST_CASE(), except that it that it
//! requires a data type which it will instantiate when the test is executed.
//! Test setup and teardown code can, therefore, be implemented in the data
//! type's constructor and destructor.
//!
//! For example:
//!
//! \code
//! // Declare fixture type
//! struct person_t
//! {
//!   std::string name;
//!   int age;
//!   person_t() : name("unknown"), age(25) {} // setup
//!   ~person_t() {} // teardown
//! };
//!
//! // Create test fixture
//! TDOG_TEST_FIXTURE(test_person, person_t)
//! {
//!   TDOG_ASSERT_STR_EQUAL_MSG("unknown", name, "Person name test");
//!   TDOG_ASSERT_EQUAL_MSG(25, age, "Default age");
//! }
//! \endcode
//!
//! Note, in the example, how the fixture's data members are accessible in
//! the test implementation. Also note that the fixture's constructor will
//! be called when the test starts, and it's destructor called when the test
//! ends.
//!
//! In the event that either the constructor or destructor throw an exception,
//! an error condition will be recorded and the test case will be deemed to
//! have failed.
//! \param[in] test_name The test name
//! \param[in] fixture_type The fixture type
//! \sa TDOG_TEST_CASE(), TDOG_TEST_SUITE()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_TEST_FIXTURE(test_name, fixture_type)
#else
  // Actual
  #define TDOG_TEST_FIXTURE(test_name, fixture_type) \
  class test_name##_tdog_test_class : public testdog::test_case, fixture_type \
  { \
  protected: \
    virtual void m_run_impl(); \
  public: \
    test_name##_tdog_test_class() \
      : test_case(#test_name, testdog_suite::SUITE_NAME, __FILE__, false), \
        fixture_type() {} \
  }; \
  testdog::test_fixture<test_name##_tdog_test_class> \
     test_name##_tdog_test_inst(#test_name, testdog_suite::SUITE_NAME, \
    __FILE__, testdog::AUTO_REG); \
  void test_name##_tdog_test_class::m_run_impl()
#endif

//! \brief Allows test cases to be grouped into "suites".
//! \details A test suite allows test cases to be run or disabled in groups.
//! The suite name will be used directly as a C++ namespace around test cases,
//! so it should not contain spaces or conflict with existing namespaces.
//! Declaring tests within namespaced suites also allows the same test name
//! can be used in multiple contexts.
//!
//! In the following example, two test cases are defined inside a test suite:
//!
//! \code
//! TDOG_TEST_SUITE(beast_suite)
//! {
//!   TDOG_TEST_CASE(number_test)
//!   {
//!     int num_beast = 665;
//!     TDOG_ASSERT_EQUAL(666, ++num_beast); // Passes
//!   }
//!
//!   TDOG_TEST_CASE(string_test)
//!   {
//!     std::string neighbor_of_beast = "668";
//!     TDOG_ASSERT_STR_EQUAL("668", neighbor_of_beast); // Passes
//!   }
//! }
//! \endcode
//!
//! When accessing test cases with the testdog::runnner class, test cases
//! belonging to suites should always be referred to using the suite name
//! as a prefix.
//!
//! For example:
//!
//! \code
//! // Disable running of suite
//! testdog::runner::global().set_test_enabled("beast_suite::number_test", false);
//! \endcode
//!
//! \param[in] suite_name
//! \sa TDOG_TEST_CASE()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_TEST_SUITE(suite_name)
#else
  // Actual
  #define TDOG_TEST_SUITE(suite_name) \
  namespace suite_name { \
    namespace testdog_suite { \
      const char* const SUITE_NAME = #suite_name; \
    } \
  } \
  namespace suite_name
#endif

//! \brief Allows an author name to be associated with the test case.
//! \details This macro is intended to be applicable in multi-programmer
//! environments, and provides a means of associating an author name with a
//! test. The author name will be displayed in test reports where applicable.
//!
//! It should be used within the test implementation as follows:
//!
//! \code
//! TDOG_TEST_CASE(some_test)
//! {
//!   TDOG_SET_AUTHOR("Employee 24601");
//!   ...
//! }
//! \endcode
//!
//! The underlying input type is std::string.
//! \param[in] author_str Author name (std::string or char*)
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_SET_AUTHOR(author_str)
#else
  // Actual
  #define TDOG_SET_AUTHOR(author_str) \
  test_case::internal_downcast().set_author(author_str)
#endif

//! \brief Sets a time limit (in seconds) for the test execution.
//! \details If the time taken to execute the test exceeds this value, the
//! test will fail.
//!
//! For example:
//!
//! \code
//! TDOG_TEST_CASE(is_prime_func)
//! {
//!   TDOG_SET_TIME_LIMIT(5); // 5 second timeout
//!   TDOG_ASSERT(is_prime(HUGE_PRIME_NUM));
//! }
//! \endcode
//!
//! A value of 0 (the default) disables the time limit.
//!
//! Note that the test execution will not be interrupted should if the time
//! exceeds the specified limit. However, the test will enter the failed
//! state when it has finished executing, even if all its test conditions pass.
//!
//! Where a test case defines its own local time limit, the global time
//! limit (if set) will not apply to that test.
//!
//! Note. This macro can only be used within the scope of a test case.
//! \param[in] sec Time limit in seconds
//! \sa TDOG_SET_GLOBAL_LIMIT_EXEMPT()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_SET_TIME_LIMIT(sec)
#else
  // Actual
  #define TDOG_SET_TIME_LIMIT(sec) \
  test_case::internal_downcast().set_time_limit(sec)
#endif

//! \brief Designates the test as being exempt from the global
//! time limit setting.
//! \details In addition to setting local time limits for test cases
//! using the TDOG_SET_TIME_LIMIT() macro, it is possible to specify a
//! global time limit in the test runner (this will be applied to all tests).
//! For certain tests, however, it may be desirable to exempt them from the
//! global time limit.
//!
//! This can be achieved with the TDOG_SET_GLOBAL_LIMIT_EXEMPT() as follows:
//!
//! \code
//! TDOG_TEST_CASE(is_prime_func)
//! {
//!   TDOG_SET_GLOBAL_LIMIT_EXEMPT();
//!   TDOG_ASSERT(is_prime(HUGE_PRIME_NUM));
//! }
//! \endcode
//!
//! Note also that where a test case defines its own local time limit,
//! the global time limit (if set) will not apply to that test.
//!
//! Note. This macro can only be used within the scope of a test case.
//! \sa TDOG_SET_TIME_LIMIT(), testdog::runner::set_global_time_limit()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_SET_GLOBAL_LIMIT_EXEMPT()
#else
  // Actual
  #define TDOG_SET_GLOBAL_LIMIT_EXEMPT() \
  test_case::internal_downcast().set_global_limit_exempt(true)
#endif

//! \brief Provides the fully qualified name of the test case to the
//! test's own implementation code.
//! \details The TDOG_TEST_NAME() returns a "const char*" value type which
//! points to a name value for the test case.
//!
//! For example:
//!
//! \code
//! TDOG_TEST_CASE(some_test)
//! {
//!   printf("TEST NAME: %s", TDOG_TEST_NAME());
//!   ...
//! }
//! \endcode
//!
//! The result of TDOG_TEST_NAME() is valid for the duration of the
//! test execution.
//!
//! Note. This macro can only be used within the scope of a test case.
//! \return The test name as a "const char*" type
//! \sa TDOG_HAS_TEST_FAILED()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_TEST_NAME()
#else
  // Actual
  #define TDOG_TEST_NAME() \
  test_case::internal_downcast().full_name_cstr()
#endif

//! \brief Allows direct reference to the underlying implementation instance of
//! a test case.
//! \details You would not normally need to refer to a test's underlying
//! class instance directly, as tests self-register with the global testdog::runner
//! class. However, if you wish to register test cases explicitly* with the
//! runner yourself by calling its register_test() method, then you will need
//! a mechanism by which to refer to the underlying test instance, and
//! the TDOG_TEST_REFINST() macro provides this.
//!
//! Below is an example of how to register a test case explicitly with the
//! runner using this macro:
//!
//! \code
//! #include <testdog/unit_test.hpp>
//!
//! // Define test
//! TDOG_TEST_CASE(some_test)
//! {
//!   ...
//! }
//!
//! int main(int argc, char **argv)
//! {
//!   // Explicitly register the test
//!   testdog::runner::global().register_test(TDOG_TEST_REFINST(some_test));
//!   ...
//! }
//! \endcode
//!
//! If the test case belongs within a test suite, you should use the
//! the suite name as a namespaced prefix. For example:
//!
//! \code
//! testdog::runner::global().register_test(TDOG_TEST_REFINST(suite_name::some_test));
//! \endcode
//!
//! *You must pre-define the TDOG_DISABLE_AUTO_REG macro to disable to the
//! automatic registration of test cases. See the runner::register_test()
//! method for more information.
//! \param[in] test_name Test name
//! \sa runner::register_test()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_TEST_REFINST(test_name)
#else
  // Actual
  #define TDOG_TEST_REFINST(test_name) \
  test_name##_tdog_test_inst
#endif

//! @}
//! @name Test Assertion Macros
//! @{

//! \brief Asserts that the test condition "a" is true (the test fails if
//! it is not).
//! \details The test's failure condition count is incremented if "a" is false,
//! thus ensuring that the test fails.
//!
//! Example:
//!
//! \code
//! TDOG_TEST_CASE(is_prime_func)
//! {
//!   TDOG_SET_GLOBAL_LIMIT_EXEMPT();
//!   TDOG_TEST_MSG("Go for coffee - this is going to take a long time.");
//!
//!   TDOG_ASSERT(is_prime(HUGE_PRIME_NUM));
//! }
//! \endcode
//!
//! Where the condition is false, it will be recorded in the test report
//! as a test "fail condition". Pass conditions will also be recored
//! in the reports where the condition is true, but only for
//! "verbose test reports".
//!
//! Note. This macro can only be used within the scope of a test case.
//! \param[in] a The test condition
//! \sa TDOG_ASSERT_MSG(), TDOG_ASSERT_EQUAL()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT(a)
#else
  // Actual
  #define TDOG_ASSERT(a) \
  test_case::m_assert(a, std::string("ASSERT(") + #a + \
    std::string(")"), __LINE__)
#endif

//! \brief Asserts that "a" is true (the test fails if it is not) and records
//! the custom message in the test report.
//! \details This macro is equivalent to TDOG_ASSERT() except that a custom
//! message can be supplied for use in the test report output.
//! \param[in] a The test condition
//! \param[in] msg Message passed as a std::string or C-style string
//! \sa TDOG_ASSERT(), TDOG_ASSERT_EQUAL()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_MSG(a, msg)
#else
  // Actual
  #define TDOG_ASSERT_MSG(a, msg) \
  test_case::m_assert(a, msg, __LINE__)
#endif

//! \brief Asserts that "a" equals "b" (the test fails if they are not).
//! \details Both "a" and "b" must support the equality operator. The test's
//! failure condition count is incremented if they are not equal.
//!
//! This macro is synonymous with calling:
//!
//! \code
//! TDOG_ASSERT((a == b));
//! \endcode
//!
//! Where the terms are not equal, it will recorded in the test report
//! as a test "fail condition". Pass conditions will also be recored
//! in the reports where the terms are equal, but only for "verbose test reports".
//!
//! When comparing the C-style strings (i.e. char arrays), you may
//! wish to consider using TDOG_ASSERT_STR_EQUAL() instead, unless you
//! specifically wish to test for pointer value equality, rather than
//! content.
//!
//! Note. This macro can only be used within the scope of a test case.
//! \param[in] a Parameter "a"
//! \param[in] b Parameter "b"
//! \sa TDOG_ASSERT_EQUAL_MSG(), TDOG_ASSERT_STR_EQUAL()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_EQUAL(a, b)
#else
  // Actual
  #define TDOG_ASSERT_EQUAL(a, b) \
  test_case::m_assert((a == b), std::string("EQUAL(") + #a + std::string(",") + \
    #b + std::string(")"), __LINE__)
#endif

//! \brief Asserts that "a" equals "b" (the test fails if they are not) and
//! records the custom message in the test report.
//! \details This macro is equivalent to TDOG_ASSERT_EQUAL() except that a
//! custom message can be supplied for use in the test report output.
//! \param[in] a Parameter "a"
//! \param[in] b Parameter "b"
//! \param[in] msg Message passed as a std::string or C-style string
//! \sa TDOG_ASSERT_EQUAL(), TDOG_ASSERT_STR_EQUAL_MSG()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_EQUAL_MSG(a, b, msg)
#else
  // Actual
  #define TDOG_ASSERT_EQUAL_MSG(a, b, msg) \
  TDOG_ASSERT_MSG((a == b), msg)
#endif

//! \brief Asserts that strings "a" and "b" are equal (the test fails if they
//! are not).
//! \details The parameters "a" and "b" are overloaded for the std::string
//! and std::wstring types. Because these types support C-style strings
//! in their constructors, literal strings can be used as input values.
//!
//! Example:
//!
//! \code
//! TDOG_TEST_CASE(case_conversion_test)
//! {
//!   std::string low_str = my_lower_case_func("Hello World");
//!   TDOG_ASSERT_STR_EQUAL("hello world" low_str);
//!
//!   std::wstring low_wstr = my_wide_lower_case_func(L"Hello World");
//!   TDOG_ASSERT_STR_EQUAL(L"hello world" low_wstr);
//! }
//! \endcode
//!
//! Consider using the TDOG_ASSERT_STRIC_EQUAL() macro instead where case
//! insensitive comparisons are required.
//!
//! Note. This macro can only be used within the scope of a test case.
//! \param[in] a String "a" passed as std::string or std::wstring
//! \param[in] b String "b" passed as std::string or std::wstring
//! \sa TDOG_ASSERT_EQUAL(), TDOG_ASSERT_STRIC_EQUAL(), TDOG_ASSERT_STR_EQUAL_MSG()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_STR_EQUAL(a, b)
#else
  // Actual
  #define TDOG_ASSERT_STR_EQUAL(a, b) \
  test_case::m_assert_str_equal(a, b, std::string("STR_EQUAL(") + #a + \
    std::string(",") + #b + std::string(")"), __LINE__)
#endif

//! \brief Asserts that strings "a" and "b" are equal (the test fails if they
//! are not) and records the custom message in the test report.
//! \details This macro is equivalent to TDOG_ASSERT_STR_EQUAL() except that a
//! custom message can be supplied for use in the test report output.
//! \param[in] a String "a" passed as std::string or std::wstring
//! \param[in] b String "b" passed as std::string or std::wstring
//! \param[in] msg Message passed as a std::string or C-style string
//! \sa TDOG_ASSERT_EQUAL_MSG(), TDOG_ASSERT_STRIC_EQUAL_MSG(), TDOG_ASSERT_STR_EQUAL()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_STR_EQUAL_MSG(a, b, msg)
#else
  // Actual
  #define TDOG_ASSERT_STR_EQUAL_MSG(a, b, msg) \
  test_case::m_assert_str_equal(a, b, msg, __LINE__)
#endif

//! \brief Compares strings "a" and "b" case insensitively and asserts that
//! they are equal (the test fails if they are not).
//! \details The parameters "a" and "b" are overloaded for the std::string
//! and std::wstring types. Because these types support C-style strings
//! in their constructors, literal strings can be used as input values.
//!
//! IMPORTANT: Only ASCII characters are compared case insensitively.
//!
//! Note. This macro can only be used within the scope of a test case.
//! \param[in] a String "a" passed as std::string or std::wstring
//! \param[in] b String "b" passed as std::string or std::wstring
//! \sa TDOG_ASSERT_EQUAL(), TDOG_ASSERT_STR_EQUAL(), TDOG_ASSERT_STRIC_EQUAL_MSG()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_STRIC_EQUAL(a, b)
#else
  // Actual
  #define TDOG_ASSERT_STRIC_EQUAL(a, b) \
  test_case::m_assert_stric_equal(a, b, std::string("STRIC_EQUAL(") + #a + \
    std::string(",") + #b + std::string(")"), __LINE__)
#endif

//! \brief Compares strings "a" and "b" case insensitively and asserts that
//! they are equal (the test fails if they are not) and records the custom
//! message in the test report.
//! \details This macro is equivalent to TDOG_ASSERT_STRIC_EQUAL() except that a
//! custom message can be supplied for use in the test report output. Note that
//! only ASCII characters are compared case insensitively.
//! \param[in] a String "a" passed as std::string or std::wstring
//! \param[in] b String "b" passed as std::string or std::wstring
//! \param[in] msg Message passed as a std::string or C-style string
//! \sa TDOG_ASSERT_EQUAL_MSG(), TDOG_ASSERT_STRIC_EQUAL_MSG(), TDOG_ASSERT_STR_EQUAL()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_STRIC_EQUAL_MSG(a, b, msg)
#else
  // Actual
  #define TDOG_ASSERT_STRIC_EQUAL_MSG(a, b, msg) \
  test_case::m_assert_stric_equal(a, b, msg, __LINE__)
#endif

//! \brief Asserts that integer values "a" and "b" are equal.
//! \details For example:
//!
//! \code
//! TDOG_TEST_CASE(test_result)
//! {
//!   TDOG_ASSERT_INT_EQUAL(3, my_sqrt_func(9));
//! }
//! \endcode
//!
//! Note. This macro can only be used within the scope of a test case.
//! \param[in] a Integer (long) value "a"
//! \param[in] b Integer (long) value "b"
//! \sa TDOG_ASSERT_EQUAL(), TDOG_ASSERT_INT_EQUAL_MSG()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_INT_EQUAL(a, b)
#else
  // Actual
  #define TDOG_ASSERT_INT_EQUAL(a, b) \
  test_case::m_assert_int_equal(a, b, \
    std::string("INT_EQUAL(") + #a + std::string(",") + \
    #b + std::string(")"), __LINE__)
#endif

//! \brief Asserts that integer values "a" and "b" are equal and records the custom
//! message in the test report.
//! \details This macro is equivalent to TDOG_ASSERT_INT_EQUAL() except that a
//! custom message can be supplied for use in the test report output.
//! \param[in] a Integer (long) value "a"
//! \param[in] b Integer (long) value "b"
//! \param[in] msg Message passed as a std::string or C-style string
//! \sa TDOG_ASSERT_EQUAL(), TDOG_ASSERT_DOUBLE_EQUAL()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_INT_EQUAL_MSG(a, b, msg)
#else
  // Actual
  #define TDOG_ASSERT_INT_EQUAL_MSG(a, b, msg) \
  test_case::m_assert_int_equal(a, b, msg, __LINE__)
#endif

//! \brief Asserts that floating point (double) values "a" and "b" are equal
//! to within the range +/- delta.
//! \details This macro asserts that:
//! <em>(a - delta) <= b <= (a + delta)</em>.
//!
//! It may be used to compare floating point values in cases where equality
//! is subject to precision considerations.
//!
//! For example:
//!
//! \code
//! TDOG_TEST_CASE(test_sqrt)
//! {
//!   TDOG_ASSERT_DOUBLE_EQUAL(1.77245, my_sqrt_func(M_PI), 0.00001);
//! }
//! \endcode
//!
//! Note. This macro can only be used within the scope of a test case.
//! \param[in] a Double value "a"
//! \param[in] b Double value "b"
//! \param[in] delta Range double value
//! \sa TDOG_ASSERT_EQUAL(), TDOG_ASSERT_DOUBLE_EQUAL_MSG()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_DOUBLE_EQUAL(a, b, delta)
#else
  // Actual
  #define TDOG_ASSERT_DOUBLE_EQUAL(a, b, delta) \
  test_case::m_assert_double_equal(a, b, delta, \
    std::string("DOUBLE_EQUAL(") + #a + std::string(",") + \
    #b + std::string(")"), __LINE__)
#endif

//! \brief Asserts that floating point (double) values "a" and "b" are equal
//! to within the range +/- delta and records the custom
//! message in the test report.
//! \details This macro is equivalent to TDOG_ASSERT_DOUBLE_EQUAL() except that a
//! custom message can be supplied for use in the test report output.
//! \param[in] a Double value "a"
//! \param[in] b Double value "b"
//! \param[in] delta Range double value
//! \param[in] msg Message passed as a std::string or C-style string
//! \sa TDOG_ASSERT_EQUAL(), TDOG_ASSERT_DOUBLE_EQUAL()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_DOUBLE_EQUAL_MSG(a, b, delta, msg)
#else
  // Actual
  #define TDOG_ASSERT_DOUBLE_EQUAL_MSG(a, b, delta, msg) \
  test_case::m_assert_double_equal(a, b, delta, msg, __LINE__)
#endif

//! \brief Asserts that the content of arrays "a" and "b" are equal (the test
//!  fails if they are not).
//! \details This macro will compare up to "cnt" array items individually, and
//! the array item type must support the equality operator to facilitate the
//! comparision.
//!
//! For example:
//!
//! \code
//! int my_sqr(int x) { return x * x; }
//!
//! TDOG_TEST_CASE(test_array)
//! {
//!   int a[] = {1, 4, 9};
//!   int b[] = {my_sqr(1), my_sqr(2), my_sqr(3)};
//!   TDOG_ASSERT_ARRAY_EQUAL(a, b, 3);
//! }
//! \endcode
//!
//! Both arrays must contain at least cnt items.
//!
//! Any data type which which can be indexed using the [] operator,
//! such as std::vector, can be compared using this macro.
//!
//! Note. This macro can only be used within the scope of a test case.
//! \param[in] a Array item "a"
//! \param[in] b Array item "b"
//! \param[in] cnt Number of items to be compared
//! \sa TDOG_ASSERT_EQUAL(), TDOG_ASSERT_ARRAY_EQUAL_MSG()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_ARRAY_EQUAL(a, b, cnt)
#else
  // Actual
  #define TDOG_ASSERT_ARRAY_EQUAL(a, b, cnt) \
  test_case::m_assert_array_equal(a, b, cnt, std::string("ARRAY_EQUAL(") + #a + \
    std::string(",") + #b + std::string(")"), __LINE__)
#endif

//! \brief Asserts that the content of arrays "a" and "b" are equal (the test
//!  fails if they are not) and records the custom message in the test report.
//! \details This macro is equivalent to TDOG_ASSERT_ARRAY_EQUAL() except that a
//! custom message can be supplied for use in the test report output.
//! \param[in] a Array item "a"
//! \param[in] b Array item "b"
//! \param[in] cnt Number of items to be compared
//! \param[in] msg Message passed as a std::string or C-style string
//! \sa TDOG_ASSERT_EQUAL(), TDOG_ASSERT_ARRAY_EQUAL()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_ARRAY_EQUAL_MSG(a, b, cnt, msg)
#else
  // Actual
  #define TDOG_ASSERT_ARRAY_EQUAL_MSG(a, b, cnt, msg) \
  test_case::m_assert_array_equal(a, b, cnt, msg, __LINE__)
#endif

//! \brief Asserts that the expression throws an exception of the
//! specified type.
//! \param[in] exprn Test expression
//! \param[in] e_type Test exception type
//! \sa TDOG_ASSERT_NO_THROW()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_THROW(exprn, e_type)
#else
  // Actual
  #define TDOG_ASSERT_THROW(exprn, e_type) \
  do { \
    bool ethrown = false; \
    try {  exprn; } \
    catch(const e_type&) { ethrown = true; } \
    test_case::m_assert(ethrown, \
      std::string("ASSERT(") + #exprn + \
      std::string(") THROWS: ") + #e_type, __LINE__); \
  } while(false)
#endif

//! \brief Asserts that the expression does not throw an exception.
//! \param[in] exprn Test expression
//! \sa TDOG_ASSERT_THROW()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_ASSERT_NO_THROW(exprn)
#else
  // Actual
  #define TDOG_ASSERT_NO_THROW(exprn) \
  do { \
    bool ethrown = false; \
    try {  exprn; } \
    catch(...) { ethrown = true; } \
    test_case::m_assert(!ethrown, \
      std::string("Assert: \"") + #exprn + \
      std::string("\" DOES NOT THROW"), __LINE__); \
  } while(false)
#endif

//! @}
//! @name Other Message and States Macros
//! @{

//! \brief Writes a information message string to the test report.
//! \details Information messages appear only in verbose style reports,
//! such as RS_TEXT_VERBOSE. They are ignored for reports which are not
//! considered to be verbose.
//!
//! For example:
//!
//! \code
//! TDOG_TEST_CASE(is_prime_func)
//! {
//!   TDOG_SET_GLOBAL_LIMIT_EXEMPT();
//!   TDOG_TEST_MSG("Go for coffee - this is going to take a long time.");
//!
//!   TDOG_ASSERT(is_prime(HUGE_PRIME_NUM));
//! }
//! \endcode
//!
//! To write out a formatted value to the report, use TDOG_TEST_VAL() instead.
//!
//! Note. This macro can only be used within the scope of a test case.
//! \param[in] msg Message passed as a std::string or C-style string
//! \sa TDOG_TEST_VAL(), TDOG_TEST_PASS(), TDOG_TEST_ERROR(), TDOG_ASSERT_MSG()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_TEST_MSG(msg)
#else
  // Actual
  #define TDOG_TEST_MSG(msg) \
  test_case::m_msg(msg, __LINE__)
#endif

//! \brief Writes a formatted value information string to the test report.
//! \details This is macro is similar to TDOG_TEST_MSG(), except that it is
//! possible to supply an additional value which will appear in a formatted
//! message. The format is similar to that used in the C printf() function,
//! although syntax and restrictions differ.
//!
//! The "val" parameter may be of one of the types below.
//!
//! Integer:
//! - long
//! - unsigned long
//! - int
//! - unsigned int
//! - short
//! - unsigned short
//! - bool
//! .
//! Floating Point:
//! - float
//! - double
//! - long double
//! .
//! String:
//! - const char*
//! - const wchar_t*
//! - std::string
//! - std::wstring
//! .
//! To identify the location and format of the value in the output, the
//! string "str" should contain one (or more) of the tag specifiers below.
//!
//! Integer:
//! - %(i) - Signed decimal
//! - %(u) - Unsigned decimal
//! - %(c) - Character
//! - %(o) - Signed octal
//! - %(x) - Unsigned hex (lower case)
//! - %(02x) - 2 digit hex (lower case)
//! - %(04x) - 4 digit hex (lower case)
//! - %(08x) - 8 digit hex (lower case)
//! - %(16x) - 16 digit hex (lower case)
//! - %(X) - Unsigned hex (upper case)
//! - %(02X) - 2 digit hex (upper case)
//! - %(04X) - 4 digit hex (upper case)
//! - %(08X) - 8 digit hex (upper case)
//! - %(16X) - 16 digit hex (upper case)
//! - %(b) - Boolean ("true", or "false")
//! .
//! Floating Point:
//! - %(f) - Floating point
//! .
//! String:
//! - %(s) - String value
//! - %(k) - Escaped string value
//! .
//! For example:
//!
//! \code
//! TDOG_TEST_VAL("final result is 0x%(08X))", rslt);
//! \endcode
//!
//! The supported tag specifiers are not unlike those used in the C printf()
//! function, however, the TDOG_TEST_VAL() macro does not
//! support a variable number of arguments, and the available tag
//! specifiers are restricted to the exact forms above.
//!
//! Additionally, the "%(b)" and "%(k)" tags have no equivalent in the
//! C printf() function. The "%(b)" is used to represent a boolean value,
//! and is substituted with either "true" or "false". Whereas, the %(k) tag is
//! a string tag, but unlike %(s), ASCII characters less than 0x20
//! (space) in value will be substitued with "escaped" characters.
//!
//! These include: "\t", "\n", "\v", "\f" and "\r".
//!
//! For example, the tab character (0x09) will be replaced with "\t".
//! For other characters, hex digits will be used instead, such as "\x08"
//! for backspace.
//!
//! Furthermore, the input string "s" may contain multiple tag specifiers,
//! and in this case, all will be substituted with the same value.
//!
//! For example:
//!
//! \code
//! TDOG_TEST_VAL("final result: %(i), HEX: 0x%(08X), OCT:0%(o)", 34283);
//! \endcode
//!
//! Gives the following message output:
//! <b>"final result: 34283, HEX: 0x000085EB, OCT:0102753"</b>
//!
//! As with TDOG_TEST_MSG(), value formatted messages appear only in verbose
//! style reports, such as RS_TEXT_VERBOSE. They are ignored for reports which
//! are not considered to be verbose.
//!
//! Note. This macro can only be used within the scope of a test case.
//! \param[in] msg Message passed as a std::string or C-style string
//! \param[in] val Value
//! \sa TDOG_TEST_MSG(), TDOG_TEST_PASS(), TDOG_TEST_ERROR(), TDOG_ASSERT_MSG()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_TEST_VAL(msg, val)
#else
  // Actual
  #define TDOG_TEST_VAL(msg, val) \
  test_case::m_val(msg, val, __LINE__)
#endif

//! \brief Increments the test case's failure condition count, thus ensuring
//! that the test fails, and writes the supplied message to the test report.
//! \details This macro is synonymous with calling:
//!
//! \code
//!   TDOG_ASSERT_MSG(false, "A fail message");
//! \endcode
//!
//! Test execution continues after this call, as a test case may
//! implement multiple condition checks.
//!
//! Note that test case failure messages appear in all test reports,
//! irrespective of whether the report is verbose or not.
//!
//! Note. This macro can only be used within the scope of a test case.
//! \param[in] msg Message passed as a std::string or C-style string
//! \sa TDOG_TEST_MSG(), TDOG_TEST_PASS(), TDOG_TEST_ERROR(), TDOG_ASSERT_MSG()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_TEST_FAIL(msg)
#else
  // Actual
  #define TDOG_TEST_FAIL(msg) \
  test_case::m_fail(msg, __LINE__)
#endif

//! \brief Writes a "pass condition" informational message to the test report.
//! \details This macro is synonymous with calling:
//!
//! \code
//!   TDOG_ASSERT_MSG(true, "A pass message");
//! \endcode
//!
//! It simply outputs an informational message which has a "pass condition"
//! label associated with it--it will not force the test to pass if
//! it has already failed.
//!
//! As with informational messages written by calling TDOG_TEST_MSG(), "pass
//! messages" appear only in verbose style test reports. They are ignored for
//! reports which are not considered to be verbose.
//!
//! Note. This macro can only be used within the scope of a test case.
//! \param[in] msg Message passed as a std::string or C-style string
//! \sa TDOG_TEST_FAIL(), TDOG_TEST_MSG(), TDOG_TEST_ERROR(), TDOG_ASSERT_MSG()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_TEST_PASS(msg)
#else
  // Actual
  #define TDOG_TEST_PASS(msg) \
  test_case::m_pass(msg, __LINE__)
#endif

//! \brief Puts the test case into an error state and writes the supplied
//! message to the test report.
//! \details A test case will automically be placed in the "error state" if the
//! test implementation, or its fixture setup/teardown code, throws an unhandled
//! exception. The TDOG_TEST_ERROR() macro, however, can be used to explicitly
//! put the test into an error state from within the test code.
//!
//! This call is similar to TDOG_TEST_FAIL() in so much as it will effectively
//! prevents the test case from passing. However, a "test error" is considered
//! distinct from a "test failure" because it explicitly refers to a problem
//! in the test implementation code, rather than the code subject to
//! the test.
//!
//! While test execution will continue normally after a call to TDOG_TEST_ERROR(),
//! typically you would want to terminate the test at this point.
//!
//! \code
//! TDOG_TEST_CASE(customer_add_record)
//! {
//!   // Create initial DB records needed to perform test
//!   bool setup_ok = setup_customer_add_record_test();
//!
//!   if (!setup_ok)
//!   {
//!     TDOG_TEST_ERROR("Test setup failed - could not perform test");
//!     return; // <- Exit
//!   }
//!
//!   // Actual test
//!    TDOG_TEST_MSG("Test initialization ok - begin real part of test");
//!   ...
//! }
//! \endcode
//!
//! Note that test error messages are always written to the test report,
//! irrespective of whether the report is verbose or not.
//!
//! Note. This macro can only be used within the scope of a test case.
//! \param[in] msg Message passed as a std::string or C-style string
//! \sa TDOG_TEST_FAIL(), TDOG_TEST_MSG(), TDOG_TEST_PASS(), TDOG_ASSERT_MSG()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_TEST_ERROR(msg)
#else
  // Actual
  #define TDOG_TEST_ERROR(msg) \
  test_case::m_error(msg, __LINE__)
#endif

//! \brief Provides indication that the test has failed (or raised a
//! test error).
//! \details This macro can be used within a test implementation to determine
//! whether any preceeding assert conditions have failed. The result will be
//! true if the test has failed, or is in a test error state.
//!
//! For example:
//!
//! \code
//! TDOG_TEST_CASE(some_test)
//! {
//!   TDOG_ASSERT_EQUAL(1, 3); // <- Fail
//!
//!   if (TDOG_HAS_TEST_FAILED())
//!   {
//!     TDOG_TEST_MSG("Test already failed - stop here");
//!     return;
//!   }
//!
//!   // Continue testing
//!   ...
//! }
//! \endcode
//!
//! \return Boolean result indicating whether the test has failed
//! \sa TDOG_TEST_NAME()
#ifdef DOXYGEN
  // Doc dummy
  #define TDOG_HAS_TEST_FAILED()
#else
  // Actual
  #define TDOG_HAS_TEST_FAILED() \
  (test_case::internal_downcast().state() == testdog::BTS_FAILED || \
    test_case::internal_downcast().state() == testdog::BTS_TEST_ERROR)
#endif

//---------------------------------------------------------------------------
#endif // HEADER GUARD
//---------------------------------------------------------------------------
