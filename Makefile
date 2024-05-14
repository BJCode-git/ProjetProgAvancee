# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target test
test:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running tests..."
	/home/julien/.local/lib/python3.10/site-packages/cmake/data/bin/ctest --force-new-ctest-process $(ARGS)
.PHONY : test

# Special rule for the target test
test/fast: test
.PHONY : test/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/home/julien/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/home/julien/.local/lib/python3.10/site-packages/cmake/data/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components
.PHONY : list_install_components/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/home/julien/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/home/julien/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/home/julien/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/home/julien/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/home/julien/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/home/julien/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles /home/julien/Cours2A/Prog_Avance/Projet//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/julien/Cours2A/Prog_Avance/Projet/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named BrickBreaker

# Build rule for target.
BrickBreaker: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 BrickBreaker
.PHONY : BrickBreaker

# fast build rule for target.
BrickBreaker/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/BrickBreaker.dir/build.make CMakeFiles/BrickBreaker.dir/build
.PHONY : BrickBreaker/fast

#=============================================================================
# Target rules for targets named test-physical-object

# Build rule for target.
test-physical-object: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test-physical-object
.PHONY : test-physical-object

# fast build rule for target.
test-physical-object/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-object.dir/build.make CMakeFiles/test-physical-object.dir/build
.PHONY : test-physical-object/fast

#=============================================================================
# Target rules for targets named test-circle-drawing

# Build rule for target.
test-circle-drawing: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test-circle-drawing
.PHONY : test-circle-drawing

# fast build rule for target.
test-circle-drawing/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-circle-drawing.dir/build.make CMakeFiles/test-circle-drawing.dir/build
.PHONY : test-circle-drawing/fast

#=============================================================================
# Target rules for targets named test-image-drawing

# Build rule for target.
test-image-drawing: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test-image-drawing
.PHONY : test-image-drawing

# fast build rule for target.
test-image-drawing/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-image-drawing.dir/build.make CMakeFiles/test-image-drawing.dir/build
.PHONY : test-image-drawing/fast

#=============================================================================
# Target rules for targets named test-gif-drawing

# Build rule for target.
test-gif-drawing: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test-gif-drawing
.PHONY : test-gif-drawing

# fast build rule for target.
test-gif-drawing/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-gif-drawing.dir/build.make CMakeFiles/test-gif-drawing.dir/build
.PHONY : test-gif-drawing/fast

#=============================================================================
# Target rules for targets named test-render-drawing

# Build rule for target.
test-render-drawing: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test-render-drawing
.PHONY : test-render-drawing

# fast build rule for target.
test-render-drawing/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-render-drawing.dir/build.make CMakeFiles/test-render-drawing.dir/build
.PHONY : test-render-drawing/fast

#=============================================================================
# Target rules for targets named test-shared-ptr

# Build rule for target.
test-shared-ptr: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test-shared-ptr
.PHONY : test-shared-ptr

# fast build rule for target.
test-shared-ptr/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-shared-ptr.dir/build.make CMakeFiles/test-shared-ptr.dir/build
.PHONY : test-shared-ptr/fast

#=============================================================================
# Target rules for targets named test-physical-engine

# Build rule for target.
test-physical-engine: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test-physical-engine
.PHONY : test-physical-engine

# fast build rule for target.
test-physical-engine/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-engine.dir/build.make CMakeFiles/test-physical-engine.dir/build
.PHONY : test-physical-engine/fast

#=============================================================================
# Target rules for targets named test-graphical-engine

# Build rule for target.
test-graphical-engine: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 test-graphical-engine
.PHONY : test-graphical-engine

# fast build rule for target.
test-graphical-engine/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-graphical-engine.dir/build.make CMakeFiles/test-graphical-engine.dir/build
.PHONY : test-graphical-engine/fast

#=============================================================================
# Target rules for targets named Physical_Engine

# Build rule for target.
Physical_Engine: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Physical_Engine
.PHONY : Physical_Engine

# fast build rule for target.
Physical_Engine/fast:
	$(MAKE) $(MAKESILENT) -f include/Physical_Engine/CMakeFiles/Physical_Engine.dir/build.make include/Physical_Engine/CMakeFiles/Physical_Engine.dir/build
.PHONY : Physical_Engine/fast

#=============================================================================
# Target rules for targets named Graphical_Engine

# Build rule for target.
Graphical_Engine: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Graphical_Engine
.PHONY : Graphical_Engine

# fast build rule for target.
Graphical_Engine/fast:
	$(MAKE) $(MAKESILENT) -f include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/build.make include/Graphical_Engine/CMakeFiles/Graphical_Engine.dir/build
.PHONY : Graphical_Engine/fast

src/Game_Engine.o: src/Game_Engine.cpp.o
.PHONY : src/Game_Engine.o

# target to build an object file
src/Game_Engine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/BrickBreaker.dir/build.make CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.o
.PHONY : src/Game_Engine.cpp.o

src/Game_Engine.i: src/Game_Engine.cpp.i
.PHONY : src/Game_Engine.i

# target to preprocess a source file
src/Game_Engine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/BrickBreaker.dir/build.make CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.i
.PHONY : src/Game_Engine.cpp.i

src/Game_Engine.s: src/Game_Engine.cpp.s
.PHONY : src/Game_Engine.s

# target to generate assembly for a file
src/Game_Engine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/BrickBreaker.dir/build.make CMakeFiles/BrickBreaker.dir/src/Game_Engine.cpp.s
.PHONY : src/Game_Engine.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/BrickBreaker.dir/build.make CMakeFiles/BrickBreaker.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/BrickBreaker.dir/build.make CMakeFiles/BrickBreaker.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/BrickBreaker.dir/build.make CMakeFiles/BrickBreaker.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

src/tests/test-circle-drawing.o: src/tests/test-circle-drawing.cpp.o
.PHONY : src/tests/test-circle-drawing.o

# target to build an object file
src/tests/test-circle-drawing.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-circle-drawing.dir/build.make CMakeFiles/test-circle-drawing.dir/src/tests/test-circle-drawing.cpp.o
.PHONY : src/tests/test-circle-drawing.cpp.o

src/tests/test-circle-drawing.i: src/tests/test-circle-drawing.cpp.i
.PHONY : src/tests/test-circle-drawing.i

# target to preprocess a source file
src/tests/test-circle-drawing.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-circle-drawing.dir/build.make CMakeFiles/test-circle-drawing.dir/src/tests/test-circle-drawing.cpp.i
.PHONY : src/tests/test-circle-drawing.cpp.i

src/tests/test-circle-drawing.s: src/tests/test-circle-drawing.cpp.s
.PHONY : src/tests/test-circle-drawing.s

# target to generate assembly for a file
src/tests/test-circle-drawing.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-circle-drawing.dir/build.make CMakeFiles/test-circle-drawing.dir/src/tests/test-circle-drawing.cpp.s
.PHONY : src/tests/test-circle-drawing.cpp.s

src/tests/test-gif-drawing.o: src/tests/test-gif-drawing.cpp.o
.PHONY : src/tests/test-gif-drawing.o

# target to build an object file
src/tests/test-gif-drawing.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-gif-drawing.dir/build.make CMakeFiles/test-gif-drawing.dir/src/tests/test-gif-drawing.cpp.o
.PHONY : src/tests/test-gif-drawing.cpp.o

src/tests/test-gif-drawing.i: src/tests/test-gif-drawing.cpp.i
.PHONY : src/tests/test-gif-drawing.i

# target to preprocess a source file
src/tests/test-gif-drawing.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-gif-drawing.dir/build.make CMakeFiles/test-gif-drawing.dir/src/tests/test-gif-drawing.cpp.i
.PHONY : src/tests/test-gif-drawing.cpp.i

src/tests/test-gif-drawing.s: src/tests/test-gif-drawing.cpp.s
.PHONY : src/tests/test-gif-drawing.s

# target to generate assembly for a file
src/tests/test-gif-drawing.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-gif-drawing.dir/build.make CMakeFiles/test-gif-drawing.dir/src/tests/test-gif-drawing.cpp.s
.PHONY : src/tests/test-gif-drawing.cpp.s

src/tests/test-graphical-engine.o: src/tests/test-graphical-engine.cpp.o
.PHONY : src/tests/test-graphical-engine.o

# target to build an object file
src/tests/test-graphical-engine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-graphical-engine.dir/build.make CMakeFiles/test-graphical-engine.dir/src/tests/test-graphical-engine.cpp.o
.PHONY : src/tests/test-graphical-engine.cpp.o

src/tests/test-graphical-engine.i: src/tests/test-graphical-engine.cpp.i
.PHONY : src/tests/test-graphical-engine.i

# target to preprocess a source file
src/tests/test-graphical-engine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-graphical-engine.dir/build.make CMakeFiles/test-graphical-engine.dir/src/tests/test-graphical-engine.cpp.i
.PHONY : src/tests/test-graphical-engine.cpp.i

src/tests/test-graphical-engine.s: src/tests/test-graphical-engine.cpp.s
.PHONY : src/tests/test-graphical-engine.s

# target to generate assembly for a file
src/tests/test-graphical-engine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-graphical-engine.dir/build.make CMakeFiles/test-graphical-engine.dir/src/tests/test-graphical-engine.cpp.s
.PHONY : src/tests/test-graphical-engine.cpp.s

src/tests/test-image-drawing.o: src/tests/test-image-drawing.cpp.o
.PHONY : src/tests/test-image-drawing.o

# target to build an object file
src/tests/test-image-drawing.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-image-drawing.dir/build.make CMakeFiles/test-image-drawing.dir/src/tests/test-image-drawing.cpp.o
.PHONY : src/tests/test-image-drawing.cpp.o

src/tests/test-image-drawing.i: src/tests/test-image-drawing.cpp.i
.PHONY : src/tests/test-image-drawing.i

# target to preprocess a source file
src/tests/test-image-drawing.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-image-drawing.dir/build.make CMakeFiles/test-image-drawing.dir/src/tests/test-image-drawing.cpp.i
.PHONY : src/tests/test-image-drawing.cpp.i

src/tests/test-image-drawing.s: src/tests/test-image-drawing.cpp.s
.PHONY : src/tests/test-image-drawing.s

# target to generate assembly for a file
src/tests/test-image-drawing.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-image-drawing.dir/build.make CMakeFiles/test-image-drawing.dir/src/tests/test-image-drawing.cpp.s
.PHONY : src/tests/test-image-drawing.cpp.s

src/tests/test-physical-engine.o: src/tests/test-physical-engine.cpp.o
.PHONY : src/tests/test-physical-engine.o

# target to build an object file
src/tests/test-physical-engine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-engine.dir/build.make CMakeFiles/test-physical-engine.dir/src/tests/test-physical-engine.cpp.o
.PHONY : src/tests/test-physical-engine.cpp.o

src/tests/test-physical-engine.i: src/tests/test-physical-engine.cpp.i
.PHONY : src/tests/test-physical-engine.i

# target to preprocess a source file
src/tests/test-physical-engine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-engine.dir/build.make CMakeFiles/test-physical-engine.dir/src/tests/test-physical-engine.cpp.i
.PHONY : src/tests/test-physical-engine.cpp.i

src/tests/test-physical-engine.s: src/tests/test-physical-engine.cpp.s
.PHONY : src/tests/test-physical-engine.s

# target to generate assembly for a file
src/tests/test-physical-engine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-engine.dir/build.make CMakeFiles/test-physical-engine.dir/src/tests/test-physical-engine.cpp.s
.PHONY : src/tests/test-physical-engine.cpp.s

src/tests/test-physical-object.o: src/tests/test-physical-object.cpp.o
.PHONY : src/tests/test-physical-object.o

# target to build an object file
src/tests/test-physical-object.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-object.dir/build.make CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.o
.PHONY : src/tests/test-physical-object.cpp.o

src/tests/test-physical-object.i: src/tests/test-physical-object.cpp.i
.PHONY : src/tests/test-physical-object.i

# target to preprocess a source file
src/tests/test-physical-object.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-object.dir/build.make CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.i
.PHONY : src/tests/test-physical-object.cpp.i

src/tests/test-physical-object.s: src/tests/test-physical-object.cpp.s
.PHONY : src/tests/test-physical-object.s

# target to generate assembly for a file
src/tests/test-physical-object.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-object.dir/build.make CMakeFiles/test-physical-object.dir/src/tests/test-physical-object.cpp.s
.PHONY : src/tests/test-physical-object.cpp.s

src/tests/test-render-drawing.o: src/tests/test-render-drawing.cpp.o
.PHONY : src/tests/test-render-drawing.o

# target to build an object file
src/tests/test-render-drawing.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-render-drawing.dir/build.make CMakeFiles/test-render-drawing.dir/src/tests/test-render-drawing.cpp.o
.PHONY : src/tests/test-render-drawing.cpp.o

src/tests/test-render-drawing.i: src/tests/test-render-drawing.cpp.i
.PHONY : src/tests/test-render-drawing.i

# target to preprocess a source file
src/tests/test-render-drawing.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-render-drawing.dir/build.make CMakeFiles/test-render-drawing.dir/src/tests/test-render-drawing.cpp.i
.PHONY : src/tests/test-render-drawing.cpp.i

src/tests/test-render-drawing.s: src/tests/test-render-drawing.cpp.s
.PHONY : src/tests/test-render-drawing.s

# target to generate assembly for a file
src/tests/test-render-drawing.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-render-drawing.dir/build.make CMakeFiles/test-render-drawing.dir/src/tests/test-render-drawing.cpp.s
.PHONY : src/tests/test-render-drawing.cpp.s

src/tests/test-shared-ptr.o: src/tests/test-shared-ptr.cpp.o
.PHONY : src/tests/test-shared-ptr.o

# target to build an object file
src/tests/test-shared-ptr.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-shared-ptr.dir/build.make CMakeFiles/test-shared-ptr.dir/src/tests/test-shared-ptr.cpp.o
.PHONY : src/tests/test-shared-ptr.cpp.o

src/tests/test-shared-ptr.i: src/tests/test-shared-ptr.cpp.i
.PHONY : src/tests/test-shared-ptr.i

# target to preprocess a source file
src/tests/test-shared-ptr.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-shared-ptr.dir/build.make CMakeFiles/test-shared-ptr.dir/src/tests/test-shared-ptr.cpp.i
.PHONY : src/tests/test-shared-ptr.cpp.i

src/tests/test-shared-ptr.s: src/tests/test-shared-ptr.cpp.s
.PHONY : src/tests/test-shared-ptr.s

# target to generate assembly for a file
src/tests/test-shared-ptr.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-shared-ptr.dir/build.make CMakeFiles/test-shared-ptr.dir/src/tests/test-shared-ptr.cpp.s
.PHONY : src/tests/test-shared-ptr.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... install"
	@echo "... install/local"
	@echo "... install/strip"
	@echo "... list_install_components"
	@echo "... rebuild_cache"
	@echo "... test"
	@echo "... BrickBreaker"
	@echo "... Graphical_Engine"
	@echo "... Physical_Engine"
	@echo "... test-circle-drawing"
	@echo "... test-gif-drawing"
	@echo "... test-graphical-engine"
	@echo "... test-image-drawing"
	@echo "... test-physical-engine"
	@echo "... test-physical-object"
	@echo "... test-render-drawing"
	@echo "... test-shared-ptr"
	@echo "... src/Game_Engine.o"
	@echo "... src/Game_Engine.i"
	@echo "... src/Game_Engine.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/tests/test-circle-drawing.o"
	@echo "... src/tests/test-circle-drawing.i"
	@echo "... src/tests/test-circle-drawing.s"
	@echo "... src/tests/test-gif-drawing.o"
	@echo "... src/tests/test-gif-drawing.i"
	@echo "... src/tests/test-gif-drawing.s"
	@echo "... src/tests/test-graphical-engine.o"
	@echo "... src/tests/test-graphical-engine.i"
	@echo "... src/tests/test-graphical-engine.s"
	@echo "... src/tests/test-image-drawing.o"
	@echo "... src/tests/test-image-drawing.i"
	@echo "... src/tests/test-image-drawing.s"
	@echo "... src/tests/test-physical-engine.o"
	@echo "... src/tests/test-physical-engine.i"
	@echo "... src/tests/test-physical-engine.s"
	@echo "... src/tests/test-physical-object.o"
	@echo "... src/tests/test-physical-object.i"
	@echo "... src/tests/test-physical-object.s"
	@echo "... src/tests/test-render-drawing.o"
	@echo "... src/tests/test-render-drawing.i"
	@echo "... src/tests/test-render-drawing.s"
	@echo "... src/tests/test-shared-ptr.o"
	@echo "... src/tests/test-shared-ptr.i"
	@echo "... src/tests/test-shared-ptr.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

