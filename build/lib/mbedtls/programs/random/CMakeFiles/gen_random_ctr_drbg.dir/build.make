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
include lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/depend.make

# Include the progress variables for this target.
include lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/progress.make

# Include the compile flags for this target's objects.
include lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/flags.make

lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/gen_random_ctr_drbg.c.o: lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/flags.make
lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/gen_random_ctr_drbg.c.o: ../lib/mbedtls/programs/random/gen_random_ctr_drbg.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/gen_random_ctr_drbg.c.o"
	cd /home/chase511/code/yoroi/build/lib/mbedtls/programs/random && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gen_random_ctr_drbg.dir/gen_random_ctr_drbg.c.o   -c /home/chase511/code/yoroi/lib/mbedtls/programs/random/gen_random_ctr_drbg.c

lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/gen_random_ctr_drbg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gen_random_ctr_drbg.dir/gen_random_ctr_drbg.c.i"
	cd /home/chase511/code/yoroi/build/lib/mbedtls/programs/random && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chase511/code/yoroi/lib/mbedtls/programs/random/gen_random_ctr_drbg.c > CMakeFiles/gen_random_ctr_drbg.dir/gen_random_ctr_drbg.c.i

lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/gen_random_ctr_drbg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gen_random_ctr_drbg.dir/gen_random_ctr_drbg.c.s"
	cd /home/chase511/code/yoroi/build/lib/mbedtls/programs/random && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chase511/code/yoroi/lib/mbedtls/programs/random/gen_random_ctr_drbg.c -o CMakeFiles/gen_random_ctr_drbg.dir/gen_random_ctr_drbg.c.s

# Object files for target gen_random_ctr_drbg
gen_random_ctr_drbg_OBJECTS = \
"CMakeFiles/gen_random_ctr_drbg.dir/gen_random_ctr_drbg.c.o"

# External object files for target gen_random_ctr_drbg
gen_random_ctr_drbg_EXTERNAL_OBJECTS =

lib/mbedtls/programs/random/gen_random_ctr_drbg: lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/gen_random_ctr_drbg.c.o
lib/mbedtls/programs/random/gen_random_ctr_drbg: lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/build.make
lib/mbedtls/programs/random/gen_random_ctr_drbg: lib/mbedtls/library/libmbedtls.a
lib/mbedtls/programs/random/gen_random_ctr_drbg: lib/mbedtls/library/libmbedx509.a
lib/mbedtls/programs/random/gen_random_ctr_drbg: lib/mbedtls/crypto/library/libmbedcrypto.a
lib/mbedtls/programs/random/gen_random_ctr_drbg: lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable gen_random_ctr_drbg"
	cd /home/chase511/code/yoroi/build/lib/mbedtls/programs/random && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gen_random_ctr_drbg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/build: lib/mbedtls/programs/random/gen_random_ctr_drbg

.PHONY : lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/build

lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/clean:
	cd /home/chase511/code/yoroi/build/lib/mbedtls/programs/random && $(CMAKE_COMMAND) -P CMakeFiles/gen_random_ctr_drbg.dir/cmake_clean.cmake
.PHONY : lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/clean

lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/depend:
	cd /home/chase511/code/yoroi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chase511/code/yoroi /home/chase511/code/yoroi/lib/mbedtls/programs/random /home/chase511/code/yoroi/build /home/chase511/code/yoroi/build/lib/mbedtls/programs/random /home/chase511/code/yoroi/build/lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/mbedtls/programs/random/CMakeFiles/gen_random_ctr_drbg.dir/depend

