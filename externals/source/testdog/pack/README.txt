TEST-DOG C++ Unit Test Framework
Version: 1.3.0

INTRODUCTION
TEST-DOG is a lightweight, portable and open source C++ Unit Testing
Framework.

Features include:

  * Test Cases, Suites & Fixtures
  * Report Generators (Text, XML and HTML)
  * Macros for easy test case and suite declaration
  * Time Limits
  * Exceptions
  * Test Runner
  * Automated, or Manual, Test Registration
  * Cross Platform & Lightweight with few Dependencies
  * Supports MinGW, MSVC & Linux
  * Full Documentation


DOCUMENTATION
For documentation, see the "index.html" file in the "doc" subdirectory.


WEBSITE
The TEST-DOG Website is:

http://www.BigAngryDog.com/testdog/unit_testing.xhtml


COPYRIGHT & LICENSE
Copyright (C) Andy Thomas 2011

TEST-DOG is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version. TEST-DOG is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
details. You should have received a copy of the GNU General Public License
along with TEST-DOG. If not, see <http://www.gnu.org/licenses/>.


SUBDIRECTORY STRUCTURE
Subdirectories are used as follows:

- bin  : Output for test executables
- doc  : Documentation (html)
- inc  : Project include files
- lib  : Output for library files
- mvc  : MS Visual C++ Express 2010 project files
- obj  : Intermediary directory for obj files
- src  : Project source Cpp files


BUILDING TEST-DOG
The TEST-DOG Framework comprises a static library file and related header
files.

To build the static library:

1. On Windows (with MinGW*)

  mingw32-make.exe release

2. On Linux (with g++*)

  make release

3. On Windows (with MS Visual C++) - See the "mvc" subdirectory and open the
solution sln workspace file. Compile "lib" project.

These will generate a release build of the TEST-DOG static library in the
"lib" subdirectory.

You can also build a test executable which will perform a self-test of the
framework. This will be generated in the "bin" subdirectory if you make the
file "makefile.test" or build the "test" project in MSVC.

I.e.

  make -f makefile.test release


*The makefile should auto-detect between MinGW and Linux platforms. If not,
you can specify the platform explicitly, as follows:

  mingw32-make.exe release TARG_PLATFORM=MINGW

or

  make release TARG_PLATFORM=LINUX

A debug version of the library can also be built by using the "debug" target.


LINKING AGAINST TEST-DOG

1. Link against: "lib/testdog.a" (or testdog.lib with MSVC)

2. Include the "inc/" (but not "inc/testdog/") subdirectory in your include
path.

3. Use: "include <testdog/unit_test.hpp>" in your source files

See the "index.htm" file in the "doc" subdirectory for introductory examples.


PLATFORMS & COMPILERS
TEST-DOG has been built on the following development platforms:

*Linux with g++ 4.4.1
*Windows with MinGW with g++ 4.4.1, 4.4.2 and 4.5.0
*Windows with MSVC 2010 Express

Other platforms should be possible, and the makefiles are designed to be
extensible. At the time of writing, the code has been tested with 32 bit platforms
only.


VERSION HISTORY

1.3.0
* Changes made to output format of "ASSERT_EQUAL" macros.
* MVC projects now use MD (multi-threaded DLL) code generation option.
* Makefiles updated.

1.2.0
* New TDOG() and TDOG_TEST_VAL() macros added.
* Minor change to output message formats.
* Tidied up documentation a little.
* Updates to makefiles.

1.1.1
* Lib output name changed to include "lib" prefix under GCC.
* Change to makefile to allow compile with MSYS in the path.
* Other changes to makefiles.

1.1.0
* Change of namespace.
* Change of facade header filename.
* Bug fix in the makefile.
* Tidying up of internal code.

1.0.0
* Initial Release.

Andy Thomas
BigAngryDog.com
