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
CMAKE_SOURCE_DIR = "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/build"

# Include any dependencies generated for this target.
include CMakeFiles/List2_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/List2_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/List2_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/List2_test.dir/flags.make

CMakeFiles/List2_test.dir/List2_test.cpp.o: CMakeFiles/List2_test.dir/flags.make
CMakeFiles/List2_test.dir/List2_test.cpp.o: ../List2_test.cpp
CMakeFiles/List2_test.dir/List2_test.cpp.o: CMakeFiles/List2_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/List2_test.dir/List2_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/List2_test.dir/List2_test.cpp.o -MF CMakeFiles/List2_test.dir/List2_test.cpp.o.d -o CMakeFiles/List2_test.dir/List2_test.cpp.o -c "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/List2_test.cpp"

CMakeFiles/List2_test.dir/List2_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/List2_test.dir/List2_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/List2_test.cpp" > CMakeFiles/List2_test.dir/List2_test.cpp.i

CMakeFiles/List2_test.dir/List2_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/List2_test.dir/List2_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/List2_test.cpp" -o CMakeFiles/List2_test.dir/List2_test.cpp.s

# Object files for target List2_test
List2_test_OBJECTS = \
"CMakeFiles/List2_test.dir/List2_test.cpp.o"

# External object files for target List2_test
List2_test_EXTERNAL_OBJECTS =

List2_test: CMakeFiles/List2_test.dir/List2_test.cpp.o
List2_test: CMakeFiles/List2_test.dir/build.make
List2_test: /usr/lib/x86_64-linux-gnu/libgtest.a
List2_test: CMakeFiles/List2_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable List2_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/List2_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/List2_test.dir/build: List2_test
.PHONY : CMakeFiles/List2_test.dir/build

CMakeFiles/List2_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/List2_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/List2_test.dir/clean

CMakeFiles/List2_test.dir/depend:
	cd "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest" "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest" "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/build" "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/build" "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/build/CMakeFiles/List2_test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/List2_test.dir/depend
