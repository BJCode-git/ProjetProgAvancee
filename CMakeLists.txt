cmake_minimum_required(VERSION 3.17)
project(Casse-brique-BRELOT)

# Configuration du standard C++ à utiliser
set(CMAKE_CXX_STANDARD 26)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Configuration des répertoires source et binaire
set(PROJECT_SOURCE_DIR src)
set(PROJECT_BINARY_DIR build)

# Ajout du dossier include/indicators pour les fichiers d'en-tête
include_directories(include include/indicators/include)

# Ajout du dossier pour les bibliothèques
link_directories(lib/)

# Activer les tests
enable_testing()

# Configuration des tests
add_test(test-physical-object bin/test-physical-object)
add_test(test-circle-drawing bin/test-circle-drawing)
add_test(test-image-drawing bin/test-image-drawing)

# Configuration du type de build
set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

# Configuration du dossier de sortie pour les exécutables
set(EXECUTABLE_OUTPUT_PATH bin)

# Ajout de la sous-répertoire Physical_Engine
add_subdirectory(include/Physical_Engine)

# Ajout de la librairie Physical_Engine
#add_library(Physical_Engine STATIC lib/libPhysical_Engine.a)

# Configuration des exécutables
add_executable(main main.cpp)

add_executable(test-physical-object tests/test-physical-object.cpp)
add_executable(test-circle-drawing tests/test-circle-drawing.cpp)
add_executable(test-image-drawing tests/test-image-drawing.cpp)

# Configuration des bibliothèques SDL
find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    #target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})
    #target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS})
    target_include_directories(test-circle-drawing PRIVATE ${SDL2_INCLUDE_DIRS})
    
    # Configuration des bibliothèques pour les tests
    #target_link_libraries(main PRIVATE ${SDL2_LIBRARIES})
    target_link_libraries(test-circle-drawing PRIVATE ${SDL2_LIBRARIES})
    #target_link_libraries(test-image-drawing PRIVATE ${SDL2_LIBRARIES})
else()
    message(FATAL_ERROR "SDL2 not found")
endif()


# Configuration des bibliothèques SDL_image
find_package(SDL2_image REQUIRED)
if(SDL2_IMAGE_FOUND)

    target_include_directories(main PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
    target_link_libraries(main PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
    target_link_libraries(test-image-drawing PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
else()
    message(FATAL_ERROR "SDL2_image not found")
endif()

# Lier votre exécutable avec la bibliothèque Physical_Engine
target_link_libraries(test-physical-object Physical_Engine)


# Installer l'exécutable main
#install(TARGETS main DESTINATION bin)
