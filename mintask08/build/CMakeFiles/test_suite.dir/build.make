# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/natalia/programmingCplusplus/mintask08

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/natalia/programmingCplusplus/mintask08/build

# Include any dependencies generated for this target.
include CMakeFiles/test_suite.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_suite.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_suite.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_suite.dir/flags.make

CMakeFiles/test_suite.dir/tests/test_suite.cpp.o: CMakeFiles/test_suite.dir/flags.make
CMakeFiles/test_suite.dir/tests/test_suite.cpp.o: ../tests/test_suite.cpp
CMakeFiles/test_suite.dir/tests/test_suite.cpp.o: CMakeFiles/test_suite.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/natalia/programmingCplusplus/mintask08/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_suite.dir/tests/test_suite.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_suite.dir/tests/test_suite.cpp.o -MF CMakeFiles/test_suite.dir/tests/test_suite.cpp.o.d -o CMakeFiles/test_suite.dir/tests/test_suite.cpp.o -c /home/natalia/programmingCplusplus/mintask08/tests/test_suite.cpp

CMakeFiles/test_suite.dir/tests/test_suite.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_suite.dir/tests/test_suite.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/natalia/programmingCplusplus/mintask08/tests/test_suite.cpp > CMakeFiles/test_suite.dir/tests/test_suite.cpp.i

CMakeFiles/test_suite.dir/tests/test_suite.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_suite.dir/tests/test_suite.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/natalia/programmingCplusplus/mintask08/tests/test_suite.cpp -o CMakeFiles/test_suite.dir/tests/test_suite.cpp.s

# Object files for target test_suite
test_suite_OBJECTS = \
"CMakeFiles/test_suite.dir/tests/test_suite.cpp.o"

# External object files for target test_suite
test_suite_EXTERNAL_OBJECTS =

test_suite: CMakeFiles/test_suite.dir/tests/test_suite.cpp.o
test_suite: CMakeFiles/test_suite.dir/build.make
test_suite: lib/libgtest_main.a
test_suite: lib/libgtest.a
test_suite: CMakeFiles/test_suite.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/natalia/programmingCplusplus/mintask08/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_suite"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_suite.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -D TEST_TARGET=test_suite -D TEST_EXECUTABLE=/home/natalia/programmingCplusplus/mintask08/build/test_suite -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/natalia/programmingCplusplus/mintask08/build -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=test_suite_TESTS -D CTEST_FILE=/home/natalia/programmingCplusplus/mintask08/build/test_suite[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.22/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/test_suite.dir/build: test_suite
.PHONY : CMakeFiles/test_suite.dir/build

CMakeFiles/test_suite.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_suite.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_suite.dir/clean

CMakeFiles/test_suite.dir/depend:
	cd /home/natalia/programmingCplusplus/mintask08/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/natalia/programmingCplusplus/mintask08 /home/natalia/programmingCplusplus/mintask08 /home/natalia/programmingCplusplus/mintask08/build /home/natalia/programmingCplusplus/mintask08/build /home/natalia/programmingCplusplus/mintask08/build/CMakeFiles/test_suite.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_suite.dir/depend

