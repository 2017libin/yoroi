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

# Utility rule file for lcov.

# Include the progress variables for this target.
include lib/mbedtls/CMakeFiles/lcov.dir/progress.make

lib/mbedtls/CMakeFiles/lcov:
	cd /home/chase511/code/yoroi/build/lib/mbedtls && rm -rf Coverage
	cd /home/chase511/code/yoroi/build/lib/mbedtls && lcov --capture --initial --directory library/CMakeFiles/mbedtls.dir -o files.info
	cd /home/chase511/code/yoroi/build/lib/mbedtls && lcov --capture --directory library/CMakeFiles/mbedtls.dir -o tests.info
	cd /home/chase511/code/yoroi/build/lib/mbedtls && lcov --add-tracefile files.info --add-tracefile tests.info -o all.info
	cd /home/chase511/code/yoroi/build/lib/mbedtls && lcov --remove all.info -o final.info '*.h'
	cd /home/chase511/code/yoroi/build/lib/mbedtls && gendesc tests/Descriptions.txt -o descriptions
	cd /home/chase511/code/yoroi/build/lib/mbedtls && genhtml --title mbed\ TLS --description-file descriptions --keep-descriptions --legend --no-branch-coverage -o Coverage final.info
	cd /home/chase511/code/yoroi/build/lib/mbedtls && rm -f files.info tests.info all.info final.info descriptions

lcov: lib/mbedtls/CMakeFiles/lcov
lcov: lib/mbedtls/CMakeFiles/lcov.dir/build.make

.PHONY : lcov

# Rule to build all files generated by this target.
lib/mbedtls/CMakeFiles/lcov.dir/build: lcov

.PHONY : lib/mbedtls/CMakeFiles/lcov.dir/build

lib/mbedtls/CMakeFiles/lcov.dir/clean:
	cd /home/chase511/code/yoroi/build/lib/mbedtls && $(CMAKE_COMMAND) -P CMakeFiles/lcov.dir/cmake_clean.cmake
.PHONY : lib/mbedtls/CMakeFiles/lcov.dir/clean

lib/mbedtls/CMakeFiles/lcov.dir/depend:
	cd /home/chase511/code/yoroi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chase511/code/yoroi /home/chase511/code/yoroi/lib/mbedtls /home/chase511/code/yoroi/build /home/chase511/code/yoroi/build/lib/mbedtls /home/chase511/code/yoroi/build/lib/mbedtls/CMakeFiles/lcov.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/mbedtls/CMakeFiles/lcov.dir/depend

