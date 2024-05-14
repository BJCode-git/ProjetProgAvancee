# CMake generated Testfile for 
# Source directory: /home/julien/Cours2A/Prog_Avance/Projet
# Build directory: /home/julien/Cours2A/Prog_Avance/Projet
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test-circle-drawing "bin/test-circle-drawing")
set_tests_properties(test-circle-drawing PROPERTIES  _BACKTRACE_TRIPLES "/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;31;add_test;/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;0;")
add_test(test-image-drawing "bin/test-image-drawing")
set_tests_properties(test-image-drawing PROPERTIES  _BACKTRACE_TRIPLES "/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;32;add_test;/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;0;")
add_test(test-gif-drawing "bin/test-gif-drawing")
set_tests_properties(test-gif-drawing PROPERTIES  _BACKTRACE_TRIPLES "/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;33;add_test;/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;0;")
add_test(test-render-drawing "bin/test-render-drawing")
set_tests_properties(test-render-drawing PROPERTIES  _BACKTRACE_TRIPLES "/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;34;add_test;/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;0;")
add_test(test-shared-ptr "bin/test-shared-ptr")
set_tests_properties(test-shared-ptr PROPERTIES  _BACKTRACE_TRIPLES "/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;35;add_test;/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;0;")
add_test(test-physical-object "bin/test-physical-object")
set_tests_properties(test-physical-object PROPERTIES  _BACKTRACE_TRIPLES "/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;36;add_test;/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;0;")
add_test(test-physical-engine "bin/test-physical-engine")
set_tests_properties(test-physical-engine PROPERTIES  _BACKTRACE_TRIPLES "/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;37;add_test;/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;0;")
add_test(test-graphical-engine "bin/test-graphical-engine")
set_tests_properties(test-graphical-engine PROPERTIES  _BACKTRACE_TRIPLES "/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;38;add_test;/home/julien/Cours2A/Prog_Avance/Projet/CMakeLists.txt;0;")
subdirs("include/Physical_Engine")
subdirs("include/Graphical_Engine")
