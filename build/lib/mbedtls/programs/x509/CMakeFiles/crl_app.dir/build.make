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
include lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/depend.make

# Include the progress variables for this target.
include lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/progress.make

# Include the compile flags for this target's objects.
include lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/flags.make

lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/crl_app.c.o: lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/flags.make
lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/crl_app.c.o: ../lib/mbedtls/programs/x509/crl_app.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/crl_app.c.o"
	cd /home/chase511/code/yoroi/build/lib/mbedtls/programs/x509 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/crl_app.dir/crl_app.c.o   -c /home/chase511/code/yoroi/lib/mbedtls/programs/x509/crl_app.c

lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/crl_app.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/crl_app.dir/crl_app.c.i"
	cd /home/chase511/code/yoroi/build/lib/mbedtls/programs/x509 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chase511/code/yoroi/lib/mbedtls/programs/x509/crl_app.c > CMakeFiles/crl_app.dir/crl_app.c.i

lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/crl_app.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/crl_app.dir/crl_app.c.s"
	cd /home/chase511/code/yoroi/build/lib/mbedtls/programs/x509 && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chase511/code/yoroi/lib/mbedtls/programs/x509/crl_app.c -o CMakeFiles/crl_app.dir/crl_app.c.s

# Object files for target crl_app
crl_app_OBJECTS = \
"CMakeFiles/crl_app.dir/crl_app.c.o"

# External object files for target crl_app
crl_app_EXTERNAL_OBJECTS =

lib/mbedtls/programs/x509/crl_app: lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/crl_app.c.o
lib/mbedtls/programs/x509/crl_app: lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/build.make
lib/mbedtls/programs/x509/crl_app: lib/mbedtls/library/libmbedtls.a
lib/mbedtls/programs/x509/crl_app: lib/mbedtls/library/libmbedx509.a
lib/mbedtls/programs/x509/crl_app: lib/mbedtls/crypto/library/libmbedcrypto.a
lib/mbedtls/programs/x509/crl_app: lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable crl_app"
	cd /home/chase511/code/yoroi/build/lib/mbedtls/programs/x509 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crl_app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/build: lib/mbedtls/programs/x509/crl_app

.PHONY : lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/build

lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/clean:
	cd /home/chase511/code/yoroi/build/lib/mbedtls/programs/x509 && $(CMAKE_COMMAND) -P CMakeFiles/crl_app.dir/cmake_clean.cmake
.PHONY : lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/clean

lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/depend:
	cd /home/chase511/code/yoroi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chase511/code/yoroi /home/chase511/code/yoroi/lib/mbedtls/programs/x509 /home/chase511/code/yoroi/build /home/chase511/code/yoroi/build/lib/mbedtls/programs/x509 /home/chase511/code/yoroi/build/lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/mbedtls/programs/x509/CMakeFiles/crl_app.dir/depend

