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
# Target rules for targets named main

# Build rule for target.
main: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 main
.PHONY : main

# fast build rule for target.
main/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/build
.PHONY : main/fast

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
# Target rules for targets named Physical_Engine

# Build rule for target.
Physical_Engine: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 Physical_Engine
.PHONY : Physical_Engine

# fast build rule for target.
Physical_Engine/fast:
	$(MAKE) $(MAKESILENT) -f include/Physical_Engine/CMakeFiles/Physical_Engine.dir/build.make include/Physical_Engine/CMakeFiles/Physical_Engine.dir/build
.PHONY : Physical_Engine/fast

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/main.dir/build.make CMakeFiles/main.dir/main.cpp.s
.PHONY : main.cpp.s

src/Physical_Engine.o: src/Physical_Engine.cpp.o
.PHONY : src/Physical_Engine.o

# target to build an object file
src/Physical_Engine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-object.dir/build.make CMakeFiles/test-physical-object.dir/src/Physical_Engine.cpp.o
.PHONY : src/Physical_Engine.cpp.o

src/Physical_Engine.i: src/Physical_Engine.cpp.i
.PHONY : src/Physical_Engine.i

# target to preprocess a source file
src/Physical_Engine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-object.dir/build.make CMakeFiles/test-physical-object.dir/src/Physical_Engine.cpp.i
.PHONY : src/Physical_Engine.cpp.i

src/Physical_Engine.s: src/Physical_Engine.cpp.s
.PHONY : src/Physical_Engine.s

# target to generate assembly for a file
src/Physical_Engine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-object.dir/build.make CMakeFiles/test-physical-object.dir/src/Physical_Engine.cpp.s
.PHONY : src/Physical_Engine.cpp.s

tests/test-physical-object.o: tests/test-physical-object.cpp.o
.PHONY : tests/test-physical-object.o

# target to build an object file
tests/test-physical-object.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-object.dir/build.make CMakeFiles/test-physical-object.dir/tests/test-physical-object.cpp.o
.PHONY : tests/test-physical-object.cpp.o

tests/test-physical-object.i: tests/test-physical-object.cpp.i
.PHONY : tests/test-physical-object.i

# target to preprocess a source file
tests/test-physical-object.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-object.dir/build.make CMakeFiles/test-physical-object.dir/tests/test-physical-object.cpp.i
.PHONY : tests/test-physical-object.cpp.i

tests/test-physical-object.s: tests/test-physical-object.cpp.s
.PHONY : tests/test-physical-object.s

# target to generate assembly for a file
tests/test-physical-object.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/test-physical-object.dir/build.make CMakeFiles/test-physical-object.dir/tests/test-physical-object.cpp.s
.PHONY : tests/test-physical-object.cpp.s

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
	@echo "... Physical_Engine"
	@echo "... main"
	@echo "... test-physical-object"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... src/Physical_Engine.o"
	@echo "... src/Physical_Engine.i"
	@echo "... src/Physical_Engine.s"
	@echo "... tests/test-physical-object.o"
	@echo "... tests/test-physical-object.i"
	@echo "... tests/test-physical-object.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
