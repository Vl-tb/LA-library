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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/sources/main.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/sources/main.cpp.o: ../sources/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.dir/sources/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/sources/main.cpp.o -c /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/sources/main.cpp

CMakeFiles/test.dir/sources/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/sources/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/sources/main.cpp > CMakeFiles/test.dir/sources/main.cpp.i

CMakeFiles/test.dir/sources/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/sources/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/sources/main.cpp -o CMakeFiles/test.dir/sources/main.cpp.s

CMakeFiles/test.dir/sources/ex.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/sources/ex.cpp.o: ../sources/ex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test.dir/sources/ex.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/sources/ex.cpp.o -c /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/sources/ex.cpp

CMakeFiles/test.dir/sources/ex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/sources/ex.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/sources/ex.cpp > CMakeFiles/test.dir/sources/ex.cpp.i

CMakeFiles/test.dir/sources/ex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/sources/ex.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/sources/ex.cpp -o CMakeFiles/test.dir/sources/ex.cpp.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/sources/main.cpp.o" \
"CMakeFiles/test.dir/sources/ex.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

test: CMakeFiles/test.dir/sources/main.cpp.o
test: CMakeFiles/test.dir/sources/ex.cpp.o
test: CMakeFiles/test.dir/build.make
test: /opt/homebrew/lib/libtbb.12.5.dylib
test: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: test
.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	cd /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/cmake-build-release /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/cmake-build-release /Users/vladprotsenko/Documents/ACS/project/LA-library/LAlibrary/cmake-build-release/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.dir/depend

