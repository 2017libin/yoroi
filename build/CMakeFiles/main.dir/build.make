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
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/sample/main.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/sample/main.c.o: ../sample/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/main.dir/sample/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/sample/main.c.o   -c /home/chase511/code/yoroi/sample/main.c

CMakeFiles/main.dir/sample/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/sample/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chase511/code/yoroi/sample/main.c > CMakeFiles/main.dir/sample/main.c.i

CMakeFiles/main.dir/sample/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/sample/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chase511/code/yoroi/sample/main.c -o CMakeFiles/main.dir/sample/main.c.s

CMakeFiles/main.dir/src/S_16.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/S_16.c.o: ../src/S_16.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/main.dir/src/S_16.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/src/S_16.c.o   -c /home/chase511/code/yoroi/src/S_16.c

CMakeFiles/main.dir/src/S_16.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/S_16.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chase511/code/yoroi/src/S_16.c > CMakeFiles/main.dir/src/S_16.c.i

CMakeFiles/main.dir/src/S_16.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/S_16.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chase511/code/yoroi/src/S_16.c -o CMakeFiles/main.dir/src/S_16.c.s

CMakeFiles/main.dir/src/T_tables.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/T_tables.c.o: ../src/T_tables.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/main.dir/src/T_tables.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/src/T_tables.c.o   -c /home/chase511/code/yoroi/src/T_tables.c

CMakeFiles/main.dir/src/T_tables.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/T_tables.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chase511/code/yoroi/src/T_tables.c > CMakeFiles/main.dir/src/T_tables.c.i

CMakeFiles/main.dir/src/T_tables.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/T_tables.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chase511/code/yoroi/src/T_tables.c -o CMakeFiles/main.dir/src/T_tables.c.s

CMakeFiles/main.dir/src/kdf_ctr.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/kdf_ctr.c.o: ../src/kdf_ctr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/main.dir/src/kdf_ctr.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/src/kdf_ctr.c.o   -c /home/chase511/code/yoroi/src/kdf_ctr.c

CMakeFiles/main.dir/src/kdf_ctr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/kdf_ctr.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chase511/code/yoroi/src/kdf_ctr.c > CMakeFiles/main.dir/src/kdf_ctr.c.i

CMakeFiles/main.dir/src/kdf_ctr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/kdf_ctr.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chase511/code/yoroi/src/kdf_ctr.c -o CMakeFiles/main.dir/src/kdf_ctr.c.s

CMakeFiles/main.dir/src/present_12.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/present_12.c.o: ../src/present_12.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/main.dir/src/present_12.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/src/present_12.c.o   -c /home/chase511/code/yoroi/src/present_12.c

CMakeFiles/main.dir/src/present_12.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/present_12.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chase511/code/yoroi/src/present_12.c > CMakeFiles/main.dir/src/present_12.c.i

CMakeFiles/main.dir/src/present_12.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/present_12.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chase511/code/yoroi/src/present_12.c -o CMakeFiles/main.dir/src/present_12.c.s

CMakeFiles/main.dir/src/yoroi.c.o: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/yoroi.c.o: ../src/yoroi.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/main.dir/src/yoroi.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.dir/src/yoroi.c.o   -c /home/chase511/code/yoroi/src/yoroi.c

CMakeFiles/main.dir/src/yoroi.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/yoroi.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/chase511/code/yoroi/src/yoroi.c > CMakeFiles/main.dir/src/yoroi.c.i

CMakeFiles/main.dir/src/yoroi.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/yoroi.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/chase511/code/yoroi/src/yoroi.c -o CMakeFiles/main.dir/src/yoroi.c.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/sample/main.c.o" \
"CMakeFiles/main.dir/src/S_16.c.o" \
"CMakeFiles/main.dir/src/T_tables.c.o" \
"CMakeFiles/main.dir/src/kdf_ctr.c.o" \
"CMakeFiles/main.dir/src/present_12.c.o" \
"CMakeFiles/main.dir/src/yoroi.c.o"

# External object files for target main
main_EXTERNAL_OBJECTS =

main: CMakeFiles/main.dir/sample/main.c.o
main: CMakeFiles/main.dir/src/S_16.c.o
main: CMakeFiles/main.dir/src/T_tables.c.o
main: CMakeFiles/main.dir/src/kdf_ctr.c.o
main: CMakeFiles/main.dir/src/present_12.c.o
main: CMakeFiles/main.dir/src/yoroi.c.o
main: CMakeFiles/main.dir/build.make
main: lib/mbedtls/library/libmbedtls.a
main: lib/mbedtls/library/libmbedx509.a
main: lib/mbedtls/crypto/library/libmbedcrypto.a
main: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chase511/code/yoroi/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable main"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	cd /home/chase511/code/yoroi/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chase511/code/yoroi /home/chase511/code/yoroi /home/chase511/code/yoroi/build /home/chase511/code/yoroi/build /home/chase511/code/yoroi/build/CMakeFiles/main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

