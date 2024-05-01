# CMake generated Testfile for 
# Source directory: /home/julien/Cours2A/Prog_Avance/Projet
# Build directory: /home/julien/Cours2A/Prog_Avance/Projet
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test-physical-object "bin/test-physical-object")
set_tests_properties(test-physical-object PROPERTIES  _BACKTRACE_TRIPLES "/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;18;add_test;/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;0;")
subdirs("include/Physical_Engine")
