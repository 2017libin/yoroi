# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chase511/code/yoroi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chase511/code/yoroi/build

# Utility rule file for covtest.

# Include the progress variables for this target.
include lib/mbedtls/CMakeFiles/covtest.dir/progress.make

lib/mbedtls/CMakeFiles/covtest:
	cd /home/chase511/code/yoroi/build/lib/mbedtls && make test
	cd /home/chase511/code/yoroi/build/lib/mbedtls && programs/test/selftest
	cd /home/chase511/code/yoroi/build/lib/mbedtls && tests/compat.sh
	cd /home/chase511/code/yoroi/build/lib/mbedtls && tests/ssl-opt.sh

covtest: lib/mbedtls/CMakeFiles/covtest
covtest: lib/mbedtls/CMakeFiles/covtest.dir/build.make

.PHONY : covtest

# Rule to build all files generated by this target.
lib/mbedtls/CMakeFiles/covtest.dir/build: covtest

.PHONY : lib/mbedtls/CMakeFiles/covtest.dir/build

lib/mbedtls/CMakeFiles/covtest.dir/clean:
	cd /home/chase511/code/yoroi/build/lib/mbedtls && $(CMAKE_COMMAND) -P CMakeFiles/covtest.dir/cmake_clean.cmake
.PHONY : lib/mbedtls/CMakeFiles/covtest.dir/clean

lib/mbedtls/CMakeFiles/covtest.dir/depend:
	cd /home/chase511/code/yoroi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chase511/code/yoroi /home/chase511/code/yoroi/lib/mbedtls /home/chase511/code/yoroi/build /home/chase511/code/yoroi/build/lib/mbedtls /home/chase511/code/yoroi/build/lib/mbedtls/CMakeFiles/covtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/mbedtls/CMakeFiles/covtest.dir/depend

