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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.3.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.3.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\mihai\CLionProjects\test-project-gra-c

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\mihai\CLionProjects\test-project-gra-c\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/untitled2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/untitled2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/untitled2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/untitled2.dir/flags.make

CMakeFiles/untitled2.dir/main.c.obj: CMakeFiles/untitled2.dir/flags.make
CMakeFiles/untitled2.dir/main.c.obj: C:/Users/mihai/CLionProjects/test-project-gra-c/main.c
CMakeFiles/untitled2.dir/main.c.obj: CMakeFiles/untitled2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\mihai\CLionProjects\test-project-gra-c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/untitled2.dir/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/untitled2.dir/main.c.obj -MF CMakeFiles\untitled2.dir\main.c.obj.d -o CMakeFiles\untitled2.dir\main.c.obj -c C:\Users\mihai\CLionProjects\test-project-gra-c\main.c

CMakeFiles/untitled2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/untitled2.dir/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\mihai\CLionProjects\test-project-gra-c\main.c > CMakeFiles\untitled2.dir\main.c.i

CMakeFiles/untitled2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/untitled2.dir/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\mihai\CLionProjects\test-project-gra-c\main.c -o CMakeFiles\untitled2.dir\main.c.s

CMakeFiles/untitled2.dir/image_processing.c.obj: CMakeFiles/untitled2.dir/flags.make
CMakeFiles/untitled2.dir/image_processing.c.obj: C:/Users/mihai/CLionProjects/test-project-gra-c/image_processing.c
CMakeFiles/untitled2.dir/image_processing.c.obj: CMakeFiles/untitled2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\mihai\CLionProjects\test-project-gra-c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/untitled2.dir/image_processing.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/untitled2.dir/image_processing.c.obj -MF CMakeFiles\untitled2.dir\image_processing.c.obj.d -o CMakeFiles\untitled2.dir\image_processing.c.obj -c C:\Users\mihai\CLionProjects\test-project-gra-c\image_processing.c

CMakeFiles/untitled2.dir/image_processing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/untitled2.dir/image_processing.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\mihai\CLionProjects\test-project-gra-c\image_processing.c > CMakeFiles\untitled2.dir\image_processing.c.i

CMakeFiles/untitled2.dir/image_processing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/untitled2.dir/image_processing.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\mihai\CLionProjects\test-project-gra-c\image_processing.c -o CMakeFiles\untitled2.dir\image_processing.c.s

CMakeFiles/untitled2.dir/image.c.obj: CMakeFiles/untitled2.dir/flags.make
CMakeFiles/untitled2.dir/image.c.obj: C:/Users/mihai/CLionProjects/test-project-gra-c/image.c
CMakeFiles/untitled2.dir/image.c.obj: CMakeFiles/untitled2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\mihai\CLionProjects\test-project-gra-c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/untitled2.dir/image.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/untitled2.dir/image.c.obj -MF CMakeFiles\untitled2.dir\image.c.obj.d -o CMakeFiles\untitled2.dir\image.c.obj -c C:\Users\mihai\CLionProjects\test-project-gra-c\image.c

CMakeFiles/untitled2.dir/image.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/untitled2.dir/image.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\mihai\CLionProjects\test-project-gra-c\image.c > CMakeFiles\untitled2.dir\image.c.i

CMakeFiles/untitled2.dir/image.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/untitled2.dir/image.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\mihai\CLionProjects\test-project-gra-c\image.c -o CMakeFiles\untitled2.dir\image.c.s

CMakeFiles/untitled2.dir/simplemath.c.obj: CMakeFiles/untitled2.dir/flags.make
CMakeFiles/untitled2.dir/simplemath.c.obj: C:/Users/mihai/CLionProjects/test-project-gra-c/simplemath.c
CMakeFiles/untitled2.dir/simplemath.c.obj: CMakeFiles/untitled2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\mihai\CLionProjects\test-project-gra-c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/untitled2.dir/simplemath.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/untitled2.dir/simplemath.c.obj -MF CMakeFiles\untitled2.dir\simplemath.c.obj.d -o CMakeFiles\untitled2.dir\simplemath.c.obj -c C:\Users\mihai\CLionProjects\test-project-gra-c\simplemath.c

CMakeFiles/untitled2.dir/simplemath.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/untitled2.dir/simplemath.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\mihai\CLionProjects\test-project-gra-c\simplemath.c > CMakeFiles\untitled2.dir\simplemath.c.i

CMakeFiles/untitled2.dir/simplemath.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/untitled2.dir/simplemath.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\mihai\CLionProjects\test-project-gra-c\simplemath.c -o CMakeFiles\untitled2.dir\simplemath.c.s

CMakeFiles/untitled2.dir/benchmark.c.obj: CMakeFiles/untitled2.dir/flags.make
CMakeFiles/untitled2.dir/benchmark.c.obj: C:/Users/mihai/CLionProjects/test-project-gra-c/benchmark.c
CMakeFiles/untitled2.dir/benchmark.c.obj: CMakeFiles/untitled2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\mihai\CLionProjects\test-project-gra-c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/untitled2.dir/benchmark.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/untitled2.dir/benchmark.c.obj -MF CMakeFiles\untitled2.dir\benchmark.c.obj.d -o CMakeFiles\untitled2.dir\benchmark.c.obj -c C:\Users\mihai\CLionProjects\test-project-gra-c\benchmark.c

CMakeFiles/untitled2.dir/benchmark.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/untitled2.dir/benchmark.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\mihai\CLionProjects\test-project-gra-c\benchmark.c > CMakeFiles\untitled2.dir\benchmark.c.i

CMakeFiles/untitled2.dir/benchmark.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/untitled2.dir/benchmark.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\mihai\CLionProjects\test-project-gra-c\benchmark.c -o CMakeFiles\untitled2.dir\benchmark.c.s

# Object files for target untitled2
untitled2_OBJECTS = \
"CMakeFiles/untitled2.dir/main.c.obj" \
"CMakeFiles/untitled2.dir/image_processing.c.obj" \
"CMakeFiles/untitled2.dir/image.c.obj" \
"CMakeFiles/untitled2.dir/simplemath.c.obj" \
"CMakeFiles/untitled2.dir/benchmark.c.obj"

# External object files for target untitled2
untitled2_EXTERNAL_OBJECTS =

untitled2.exe: CMakeFiles/untitled2.dir/main.c.obj
untitled2.exe: CMakeFiles/untitled2.dir/image_processing.c.obj
untitled2.exe: CMakeFiles/untitled2.dir/image.c.obj
untitled2.exe: CMakeFiles/untitled2.dir/simplemath.c.obj
untitled2.exe: CMakeFiles/untitled2.dir/benchmark.c.obj
untitled2.exe: CMakeFiles/untitled2.dir/build.make
untitled2.exe: CMakeFiles/untitled2.dir/linkLibs.rsp
untitled2.exe: CMakeFiles/untitled2.dir/objects1.rsp
untitled2.exe: CMakeFiles/untitled2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\mihai\CLionProjects\test-project-gra-c\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable untitled2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\untitled2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/untitled2.dir/build: untitled2.exe
.PHONY : CMakeFiles/untitled2.dir/build

CMakeFiles/untitled2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\untitled2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/untitled2.dir/clean

CMakeFiles/untitled2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\mihai\CLionProjects\test-project-gra-c C:\Users\mihai\CLionProjects\test-project-gra-c C:\Users\mihai\CLionProjects\test-project-gra-c\cmake-build-debug C:\Users\mihai\CLionProjects\test-project-gra-c\cmake-build-debug C:\Users\mihai\CLionProjects\test-project-gra-c\cmake-build-debug\CMakeFiles\untitled2.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/untitled2.dir/depend
