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
include CMakeFiles/BrickBreaker.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/BrickBreaker.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BrickBreaker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BrickBreaker.dir/flags.make

CMakeFiles/BrickBreaker.dir/src/main.cpp.o: CMakeFiles/BrickBreaker.dir/flags.make
CMakeFiles/BrickBreaker.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/BrickBreaker.dir/src/main.cpp.o: CMakeFiles/BrickBreaker.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BrickBreaker.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BrickBreaker.dir/src/main.cpp.o -MF CMakeFiles/BrickBreaker.dir/src/main.cpp.o.d -o CMakeFiles/BrickBreaker.dir/src/main.cpp.o -c /home/julien/Cours2A/Prog_Avance/Projet/src/main.cpp

CMakeFiles/BrickBreaker.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BrickBreaker.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/julien/Cours2A/Prog_Avance/Projet/src/main.cpp > CMakeFiles/BrickBreaker.dir/src/main.cpp.i

CMakeFiles/BrickBreaker.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BrickBreaker.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/julien/Cours2A/Prog_Avance/Projet/src/main.cpp -o CMakeFiles/BrickBreaker.dir/src/main.cpp.s

CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.o: CMakeFiles/BrickBreaker.dir/flags.make
CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.o: src/Game_Engine.cpp
CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.o: CMakeFiles/BrickBreaker.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.o -MF CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.o.d -o CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.o -c /home/julien/Cours2A/Prog_Avance/Projet/src/Game_Engine.cpp

CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/julien/Cours2A/Prog_Avance/Projet/src/Game_Engine.cpp > CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.i

CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/julien/Cours2A/Prog_Avance/Projet/src/Game_Engine.cpp -o CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.s

CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.o: CMakeFiles/BrickBreaker.dir/flags.make
CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.o: src/Graphical_Engine.cpp
CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.o: CMakeFiles/BrickBreaker.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.o -MF CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.o.d -o CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.o -c /home/julien/Cours2A/Prog_Avance/Projet/src/Graphical_Engine.cpp

CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/julien/Cours2A/Prog_Avance/Projet/src/Graphical_Engine.cpp > CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.i

CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/julien/Cours2A/Prog_Avance/Projet/src/Graphical_Engine.cpp -o CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.s

CMakeFiles/BrickBreaker.dir/src/Windows.cpp.o: CMakeFiles/BrickBreaker.dir/flags.make
CMakeFiles/BrickBreaker.dir/src/Windows.cpp.o: src/Windows.cpp
CMakeFiles/BrickBreaker.dir/src/Windows.cpp.o: CMakeFiles/BrickBreaker.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/BrickBreaker.dir/src/Windows.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BrickBreaker.dir/src/Windows.cpp.o -MF CMakeFiles/BrickBreaker.dir/src/Windows.cpp.o.d -o CMakeFiles/BrickBreaker.dir/src/Windows.cpp.o -c /home/julien/Cours2A/Prog_Avance/Projet/src/Windows.cpp

CMakeFiles/BrickBreaker.dir/src/Windows.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BrickBreaker.dir/src/Windows.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/julien/Cours2A/Prog_Avance/Projet/src/Windows.cpp > CMakeFiles/BrickBreaker.dir/src/Windows.cpp.i

CMakeFiles/BrickBreaker.dir/src/Windows.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BrickBreaker.dir/src/Windows.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/julien/Cours2A/Prog_Avance/Projet/src/Windows.cpp -o CMakeFiles/BrickBreaker.dir/src/Windows.cpp.s

# Object files for target BrickBreaker
BrickBreaker_OBJECTS = \
"CMakeFiles/BrickBreaker.dir/src/main.cpp.o" \
"CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.o" \
"CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.o" \
"CMakeFiles/BrickBreaker.dir/src/Windows.cpp.o"

# External object files for target BrickBreaker
BrickBreaker_EXTERNAL_OBJECTS =

bin/BrickBreaker: CMakeFiles/BrickBreaker.dir/src/main.cpp.o
bin/BrickBreaker: CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.o
bin/BrickBreaker: CMakeFiles/BrickBreaker.dir/src/Graphical_Engine.cpp.o
bin/BrickBreaker: CMakeFiles/BrickBreaker.dir/src/Windows.cpp.o
bin/BrickBreaker: CMakeFiles/BrickBreaker.dir/build.make
bin/BrickBreaker: lib/libPhysical_Engine.a
bin/BrickBreaker: /usr/local/lib/libSDL2.so
bin/BrickBreaker: /usr/local/lib/libSDL2_image.so
bin/BrickBreaker: /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
bin/BrickBreaker: /usr/lib/x86_64-linux-gnu/libSDL2_mixer.so
bin/BrickBreaker: /usr/local/lib/libSDL2.so
bin/BrickBreaker: CMakeFiles/BrickBreaker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable bin/BrickBreaker"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BrickBreaker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BrickBreaker.dir/build: bin/BrickBreaker
.PHONY : CMakeFiles/BrickBreaker.dir/build

CMakeFiles/BrickBreaker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BrickBreaker.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BrickBreaker.dir/clean

CMakeFiles/BrickBreaker.dir/depend:
	cd /home/julien/Cours2A/Prog_Avance/Projet && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/julien/Cours2A/Prog_Avance/Projet /home/julien/Cours2A/Prog_Avance/Projet /home/julien/Cours2A/Prog_Avance/Projet /home/julien/Cours2A/Prog_Avance/Projet /home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles/BrickBreaker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/BrickBreaker.dir/depend

