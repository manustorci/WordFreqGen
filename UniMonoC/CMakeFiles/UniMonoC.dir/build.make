# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.29.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/emanuelestorci/Documents/UniMonoC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/emanuelestorci/Documents/UniMonoC

# Include any dependencies generated for this target.
include CMakeFiles/UniMonoC.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/UniMonoC.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/UniMonoC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/UniMonoC.dir/flags.make

CMakeFiles/UniMonoC.dir/main.c.o: CMakeFiles/UniMonoC.dir/flags.make
CMakeFiles/UniMonoC.dir/main.c.o: main.c
CMakeFiles/UniMonoC.dir/main.c.o: CMakeFiles/UniMonoC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emanuelestorci/Documents/UniMonoC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/UniMonoC.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/UniMonoC.dir/main.c.o -MF CMakeFiles/UniMonoC.dir/main.c.o.d -o CMakeFiles/UniMonoC.dir/main.c.o -c /Users/emanuelestorci/Documents/UniMonoC/main.c

CMakeFiles/UniMonoC.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/UniMonoC.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/emanuelestorci/Documents/UniMonoC/main.c > CMakeFiles/UniMonoC.dir/main.c.i

CMakeFiles/UniMonoC.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/UniMonoC.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/emanuelestorci/Documents/UniMonoC/main.c -o CMakeFiles/UniMonoC.dir/main.c.s

CMakeFiles/UniMonoC.dir/text_analysis.c.o: CMakeFiles/UniMonoC.dir/flags.make
CMakeFiles/UniMonoC.dir/text_analysis.c.o: text_analysis.c
CMakeFiles/UniMonoC.dir/text_analysis.c.o: CMakeFiles/UniMonoC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emanuelestorci/Documents/UniMonoC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/UniMonoC.dir/text_analysis.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/UniMonoC.dir/text_analysis.c.o -MF CMakeFiles/UniMonoC.dir/text_analysis.c.o.d -o CMakeFiles/UniMonoC.dir/text_analysis.c.o -c /Users/emanuelestorci/Documents/UniMonoC/text_analysis.c

CMakeFiles/UniMonoC.dir/text_analysis.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/UniMonoC.dir/text_analysis.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/emanuelestorci/Documents/UniMonoC/text_analysis.c > CMakeFiles/UniMonoC.dir/text_analysis.c.i

CMakeFiles/UniMonoC.dir/text_analysis.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/UniMonoC.dir/text_analysis.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/emanuelestorci/Documents/UniMonoC/text_analysis.c -o CMakeFiles/UniMonoC.dir/text_analysis.c.s

CMakeFiles/UniMonoC.dir/text_generation.c.o: CMakeFiles/UniMonoC.dir/flags.make
CMakeFiles/UniMonoC.dir/text_generation.c.o: text_generation.c
CMakeFiles/UniMonoC.dir/text_generation.c.o: CMakeFiles/UniMonoC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emanuelestorci/Documents/UniMonoC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/UniMonoC.dir/text_generation.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/UniMonoC.dir/text_generation.c.o -MF CMakeFiles/UniMonoC.dir/text_generation.c.o.d -o CMakeFiles/UniMonoC.dir/text_generation.c.o -c /Users/emanuelestorci/Documents/UniMonoC/text_generation.c

CMakeFiles/UniMonoC.dir/text_generation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/UniMonoC.dir/text_generation.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/emanuelestorci/Documents/UniMonoC/text_generation.c > CMakeFiles/UniMonoC.dir/text_generation.c.i

CMakeFiles/UniMonoC.dir/text_generation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/UniMonoC.dir/text_generation.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/emanuelestorci/Documents/UniMonoC/text_generation.c -o CMakeFiles/UniMonoC.dir/text_generation.c.s

CMakeFiles/UniMonoC.dir/utilities.c.o: CMakeFiles/UniMonoC.dir/flags.make
CMakeFiles/UniMonoC.dir/utilities.c.o: utilities.c
CMakeFiles/UniMonoC.dir/utilities.c.o: CMakeFiles/UniMonoC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emanuelestorci/Documents/UniMonoC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/UniMonoC.dir/utilities.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/UniMonoC.dir/utilities.c.o -MF CMakeFiles/UniMonoC.dir/utilities.c.o.d -o CMakeFiles/UniMonoC.dir/utilities.c.o -c /Users/emanuelestorci/Documents/UniMonoC/utilities.c

CMakeFiles/UniMonoC.dir/utilities.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/UniMonoC.dir/utilities.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/emanuelestorci/Documents/UniMonoC/utilities.c > CMakeFiles/UniMonoC.dir/utilities.c.i

CMakeFiles/UniMonoC.dir/utilities.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/UniMonoC.dir/utilities.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/emanuelestorci/Documents/UniMonoC/utilities.c -o CMakeFiles/UniMonoC.dir/utilities.c.s

# Object files for target UniMonoC
UniMonoC_OBJECTS = \
"CMakeFiles/UniMonoC.dir/main.c.o" \
"CMakeFiles/UniMonoC.dir/text_analysis.c.o" \
"CMakeFiles/UniMonoC.dir/text_generation.c.o" \
"CMakeFiles/UniMonoC.dir/utilities.c.o"

# External object files for target UniMonoC
UniMonoC_EXTERNAL_OBJECTS =

UniMonoC: CMakeFiles/UniMonoC.dir/main.c.o
UniMonoC: CMakeFiles/UniMonoC.dir/text_analysis.c.o
UniMonoC: CMakeFiles/UniMonoC.dir/text_generation.c.o
UniMonoC: CMakeFiles/UniMonoC.dir/utilities.c.o
UniMonoC: CMakeFiles/UniMonoC.dir/build.make
UniMonoC: CMakeFiles/UniMonoC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/emanuelestorci/Documents/UniMonoC/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable UniMonoC"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/UniMonoC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/UniMonoC.dir/build: UniMonoC
.PHONY : CMakeFiles/UniMonoC.dir/build

CMakeFiles/UniMonoC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/UniMonoC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/UniMonoC.dir/clean

CMakeFiles/UniMonoC.dir/depend:
	cd /Users/emanuelestorci/Documents/UniMonoC && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/emanuelestorci/Documents/UniMonoC /Users/emanuelestorci/Documents/UniMonoC /Users/emanuelestorci/Documents/UniMonoC /Users/emanuelestorci/Documents/UniMonoC /Users/emanuelestorci/Documents/UniMonoC/CMakeFiles/UniMonoC.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/UniMonoC.dir/depend

