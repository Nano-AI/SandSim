# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.3.4\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.3.4\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\adiba\CLionProjects\SandSim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\adiba\CLionProjects\SandSim\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SandSim.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SandSim.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SandSim.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SandSim.dir/flags.make

CMakeFiles/SandSim.dir/main.c.obj: CMakeFiles/SandSim.dir/flags.make
CMakeFiles/SandSim.dir/main.c.obj: C:/Users/adiba/CLionProjects/SandSim/main.c
CMakeFiles/SandSim.dir/main.c.obj: CMakeFiles/SandSim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\adiba\CLionProjects\SandSim\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/SandSim.dir/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.4\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/SandSim.dir/main.c.obj -MF CMakeFiles\SandSim.dir\main.c.obj.d -o CMakeFiles\SandSim.dir\main.c.obj -c C:\Users\adiba\CLionProjects\SandSim\main.c

CMakeFiles/SandSim.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/SandSim.dir/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.4\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\adiba\CLionProjects\SandSim\main.c > CMakeFiles\SandSim.dir\main.c.i

CMakeFiles/SandSim.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/SandSim.dir/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.4\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\adiba\CLionProjects\SandSim\main.c -o CMakeFiles\SandSim.dir\main.c.s

# Object files for target SandSim
SandSim_OBJECTS = \
"CMakeFiles/SandSim.dir/main.c.obj"

# External object files for target SandSim
SandSim_EXTERNAL_OBJECTS =

SandSim.exe: CMakeFiles/SandSim.dir/main.c.obj
SandSim.exe: CMakeFiles/SandSim.dir/build.make
SandSim.exe: CMakeFiles/SandSim.dir/linkLibs.rsp
SandSim.exe: CMakeFiles/SandSim.dir/objects1.rsp
SandSim.exe: CMakeFiles/SandSim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\adiba\CLionProjects\SandSim\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable SandSim.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\SandSim.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SandSim.dir/build: SandSim.exe
.PHONY : CMakeFiles/SandSim.dir/build

CMakeFiles/SandSim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\SandSim.dir\cmake_clean.cmake
.PHONY : CMakeFiles/SandSim.dir/clean

CMakeFiles/SandSim.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\adiba\CLionProjects\SandSim C:\Users\adiba\CLionProjects\SandSim C:\Users\adiba\CLionProjects\SandSim\cmake-build-debug C:\Users\adiba\CLionProjects\SandSim\cmake-build-debug C:\Users\adiba\CLionProjects\SandSim\cmake-build-debug\CMakeFiles\SandSim.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SandSim.dir/depend

