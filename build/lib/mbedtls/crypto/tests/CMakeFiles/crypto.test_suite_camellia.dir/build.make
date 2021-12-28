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

# Include any dependencies generated for this target.
include lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/depend.make

# Include the progress variables for this target.
include lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/progress.make

# Include the compile flags for this target's objects.
include lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/flags.make

lib/mbedtls/crypto/tests/test_suite_camellia.c: ../lib/mbedtls/crypto/tests/scripts/generate_test_code.py
lib/mbedtls/crypto/tests/test_suite_camellia.c: lib/mbedtls/crypto/library/libmbedcrypto.a
lib/mbedtls/crypto/tests/test_suite_camellia.c: ../lib/mbedtls/crypto/tests/suites/helpers.function
lib/mbedtls/crypto/tests/test_suite_camellia.c: ../lib/mbedtls/crypto/tests/suites/main_test.function
lib/mbedtls/crypto/tests/test_suite_camellia.c: ../lib/mbedtls/crypto/tests/suites/host_test.function
lib/mbedtls/crypto/tests/test_suite_camellia.c: ../lib/mbedtls/crypto/tests/suites/test_suite_camellia.function
lib/mbedtls/crypto/tests/test_suite_camellia.c: ../lib/mbedtls/crypto/tests/suites/test_suite_camellia.data
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating test_suite_camellia.c"
	cd /home/chase511/code/yoroi/build/lib/mbedtls/crypto/tests && /usr/bin/python3 /home/chase511/code/yoroi/lib/mbedtls/crypto/tests/scripts/generate_test_code.py -f /home/chase511/code/yoroi/lib/mbedtls/crypto/tests/suites/test_suite_camellia.function -d /home/chase511/code/yoroi/lib/mbedtls/crypto/tests/suites/test_suite_camellia.data -t /home/chase511/code/yoroi/lib/mbedtls/crypto/tests/suites/main_test.function -p /home/chase511/code/yoroi/lib/mbedtls/crypto/tests/suites/host_test.function -s /home/chase511/code/yoroi/lib/mbedtls/crypto/tests/suites --helpers-file /home/chase511/code/yoroi/lib/mbedtls/crypto/tests/suites/helpers.function -o .

lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/test_suite_camellia.c.o: lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/flags.make
lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/test_suite_camellia.c.o: lib/mbedtls/crypto/tests/test_suite_camellia.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/test_suite_camellia.c.o"
	cd /home/chase511/code/yoroi/build/lib/mbedtls/crypto/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/crypto.test_suite_camellia.dir/test_suite_camellia.c.o   -c /home/chase511/code/yoroi/build/lib/mbedtls/crypto/tests/test_suite_camellia.c

lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/test_suite_camellia.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/crypto.test_suite_camellia.dir/test_suite_camellia.c.i"
	cd /home/chase511/code/yoroi/build/lib/mbedtls/crypto/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chase511/code/yoroi/build/lib/mbedtls/crypto/tests/test_suite_camellia.c > CMakeFiles/crypto.test_suite_camellia.dir/test_suite_camellia.c.i

lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/test_suite_camellia.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/crypto.test_suite_camellia.dir/test_suite_camellia.c.s"
	cd /home/chase511/code/yoroi/build/lib/mbedtls/crypto/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chase511/code/yoroi/build/lib/mbedtls/crypto/tests/test_suite_camellia.c -o CMakeFiles/crypto.test_suite_camellia.dir/test_suite_camellia.c.s

# Object files for target crypto.test_suite_camellia
crypto_test_suite_camellia_OBJECTS = \
"CMakeFiles/crypto.test_suite_camellia.dir/test_suite_camellia.c.o"

# External object files for target crypto.test_suite_camellia
crypto_test_suite_camellia_EXTERNAL_OBJECTS =

lib/mbedtls/crypto/tests/crypto.test_suite_camellia: lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/test_suite_camellia.c.o
lib/mbedtls/crypto/tests/crypto.test_suite_camellia: lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/build.make
lib/mbedtls/crypto/tests/crypto.test_suite_camellia: lib/mbedtls/crypto/library/libmbedcrypto.a
lib/mbedtls/crypto/tests/crypto.test_suite_camellia: lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable crypto.test_suite_camellia"
	cd /home/chase511/code/yoroi/build/lib/mbedtls/crypto/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crypto.test_suite_camellia.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/build: lib/mbedtls/crypto/tests/crypto.test_suite_camellia

.PHONY : lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/build

lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/clean:
	cd /home/chase511/code/yoroi/build/lib/mbedtls/crypto/tests && $(CMAKE_COMMAND) -P CMakeFiles/crypto.test_suite_camellia.dir/cmake_clean.cmake
.PHONY : lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/clean

lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/depend: lib/mbedtls/crypto/tests/test_suite_camellia.c
	cd /home/chase511/code/yoroi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chase511/code/yoroi /home/chase511/code/yoroi/lib/mbedtls/crypto/tests /home/chase511/code/yoroi/build /home/chase511/code/yoroi/build/lib/mbedtls/crypto/tests /home/chase511/code/yoroi/build/lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/mbedtls/crypto/tests/CMakeFiles/crypto.test_suite_camellia.dir/depend

