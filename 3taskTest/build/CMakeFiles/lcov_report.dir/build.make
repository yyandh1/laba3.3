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

# Utility rule file for lcov_report.

# Include any custom commands dependencies for this target.
include CMakeFiles/lcov_report.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lcov_report.dir/progress.make

CMakeFiles/lcov_report:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Generating lcov coverage report"
	/usr/bin/lcov --capture --directory . --output-file coverage.info
	/usr/bin/lcov --remove coverage.info '/usr/*' '*/test/*' --output-file coverage_filtered.info
	/usr/bin/lcov --list coverage_filtered.info
	genhtml coverage_filtered.info --output-directory out

lcov_report: CMakeFiles/lcov_report
lcov_report: CMakeFiles/lcov_report.dir/build.make
.PHONY : lcov_report

# Rule to build all files generated by this target.
CMakeFiles/lcov_report.dir/build: lcov_report
.PHONY : CMakeFiles/lcov_report.dir/build

CMakeFiles/lcov_report.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lcov_report.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lcov_report.dir/clean

CMakeFiles/lcov_report.dir/depend:
	cd "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest" "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest" "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/build" "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/build" "/mnt/c/Users/nikru/OneDrive/Desktop/Работы прога/2semLabaRudk/Laba-3-semestr-3/3taskTest/build/CMakeFiles/lcov_report.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/lcov_report.dir/depend
