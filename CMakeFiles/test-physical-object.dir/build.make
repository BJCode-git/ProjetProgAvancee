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
include CMakeFiles/test-physical-object.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test-physical-object.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test-physical-object.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test-physical-object.dir/flags.make

CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.o: CMakeFiles/test-physical-object.dir/flags.make
CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.o: src/tests/test-physical-object.cpp
CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.o: CMakeFiles/test-physical-object.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.o -MF CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.o.d -o CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.o -c /home/julien/Cours2A/Prog_Avance/Projet/src/tests/test-physical-object.cpp

CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/julien/Cours2A/Prog_Avance/Projet/src/tests/test-physical-object.cpp > CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.i

CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/julien/Cours2A/Prog_Avance/Projet/src/tests/test-physical-object.cpp -o CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.s

# Object files for target test-physical-object
test__physical__object_OBJECTS = \
"CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.o"

# External object files for target test-physical-object
test__physical__object_EXTERNAL_OBJECTS =

bin/test-physical-object: CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.o
bin/test-physical-object: CMakeFiles/test-physical-object.dir/build.make
bin/test-physical-object: lib/libPhysical_Engine.a
bin/test-physical-object: /usr/local/lib/libSDL2.so
bin/test-physical-object: CMakeFiles/test-physical-object.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/test-physical-object"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-physical-object.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test-physical-object.dir/build: bin/test-physical-object
.PHONY : CMakeFiles/test-physical-object.dir/build

CMakeFiles/test-physical-object.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test-physical-object.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test-physical-object.dir/clean

CMakeFiles/test-physical-object.dir/depend:
	cd /home/julien/Cours2A/Prog_Avance/Projet && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/julien/Cours2A/Prog_Avance/Projet /home/julien/Cours2A/Prog_Avance/Projet /home/julien/Cours2A/Prog_Avance/Projet /home/julien/Cours2A/Prog_Avance/Projet /home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles/test-physical-object.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test-physical-object.dir/depend

