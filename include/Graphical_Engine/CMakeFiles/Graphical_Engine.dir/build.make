# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /home/julien/.local/lib/python3.10/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/julien/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/julien/Cours2A/Prog_Avance/Projet

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/julien/Cours2A/Prog_Avance/Projet

# Include any dependencies generated for this target.
include include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/compiler_depend.make

# Include the progress variables for this target.
include include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/progress.make

# Include the compile flags for this target's objects.
include include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/flags.make

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.o: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/flags.make
include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.o: include/Graphical_Engine/Graphical_Engine.cpp
include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.o: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.o"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.o -MF CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.o.d -o CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.o -c /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Graphical_Engine.cpp

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.i"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Graphical_Engine.cpp > CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.i

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.s"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Graphical_Engine.cpp -o CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.s

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.o: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/flags.make
include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.o: include/Graphical_Engine/Graphical_Object/Graphical_Object.cpp
include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.o: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.o"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.o -MF CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.o.d -o CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.o -c /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Graphical_Object/Graphical_Object.cpp

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.i"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Graphical_Object/Graphical_Object.cpp > CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.i

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.s"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Graphical_Object/Graphical_Object.cpp -o CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.s

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.o: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/flags.make
include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.o: include/Graphical_Engine/Graphical_Circle/Graphical_Circle.cpp
include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.o: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.o"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.o -MF CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.o.d -o CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.o -c /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Graphical_Circle/Graphical_Circle.cpp

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.i"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Graphical_Circle/Graphical_Circle.cpp > CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.i

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.s"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Graphical_Circle/Graphical_Circle.cpp -o CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.s

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.o: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/flags.make
include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.o: include/Graphical_Engine/Graphical_Polygon/Graphical_Polygon.cpp
include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.o: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.o"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.o -MF CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.o.d -o CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.o -c /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Graphical_Polygon/Graphical_Polygon.cpp

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.i"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Graphical_Polygon/Graphical_Polygon.cpp > CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.i

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.s"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Graphical_Polygon/Graphical_Polygon.cpp -o CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.s

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.o: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/flags.make
include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.o: include/Graphical_Engine/Window/Window.cpp
include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.o: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.o"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.o -MF CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.o.d -o CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.o -c /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Window/Window.cpp

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.i"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Window/Window.cpp > CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.i

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.s"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/Window/Window.cpp -o CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.s

# Object files for target Graphical_Engine
Graphical_Engine_OBJECTS = \
"CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.o" \
"CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.o" \
"CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.o" \
"CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.o" \
"CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.o"

# External object files for target Graphical_Engine
Graphical_Engine_EXTERNAL_OBJECTS =

lib/libGraphical_Engine.a: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Engine.cpp.o
lib/libGraphical_Engine.a: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Object/Graphical_Object.cpp.o
lib/libGraphical_Engine.a: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Circle/Graphical_Circle.cpp.o
lib/libGraphical_Engine.a: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Graphical_Polygon/Graphical_Polygon.cpp.o
lib/libGraphical_Engine.a: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/Window/Window.cpp.o
lib/libGraphical_Engine.a: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/build.make
lib/libGraphical_Engine.a: include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library ../../lib/libGraphical_Engine.a"
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && $(CMAKE_COMMAND) -P CMakeFiles/Graphical_Engine.dir/cmake_clean_target.cmake
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Graphical_Engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/build: lib/libGraphical_Engine.a
.PHONY : include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/build

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/clean:
	cd /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine && $(CMAKE_COMMAND) -P CMakeFiles/Graphical_Engine.dir/cmake_clean.cmake
.PHONY : include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/clean

include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/depend:
	cd /home/julien/Cours2A/Prog_Avance/Projet && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/julien/Cours2A/Prog_Avance/Projet /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine /home/julien/Cours2A/Prog_Avance/Projet /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine /home/julien/Cours2A/Prog_Avance/Projet/include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/depend

