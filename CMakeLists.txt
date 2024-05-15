cmake_minimum_required(VERSION 3.17)
project(Casse-brique-BRELOT)



# Configuration du standard C++ à utiliser
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-std=c++20 -O3 -g -Wall -Werror -Wextra -pedantic -pthread")

set(CACHE PATH ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

# Configuration des répertoires source et binaire
set(PROJECT_SOURCE_DIR src)
set(PROJECT_BINARY_DIR build)
set(SDL2_IMAGE_LIBRARY "/usr/local/lib/libSDL2_image.so")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/Build)

# Ajout du dossier include/indicators pour les fichiers d'en-tête
include_directories(include include/indicators/include)


# Ajout du dossier pour les bibliothèques
link_directories(lib/)

# Activer les tests
enable_testing()

# Configuration des tests
add_test(test-circle-drawing bin/test-circle-drawing)
add_test(test-image-drawing bin/test-image-drawing)
add_test(test-gif-drawing bin/test-gif-drawing)
add_test(test-render-drawing bin/test-render-drawing)
add_test(test-shared-ptr bin/test-shared-ptr)
add_test(test-physical-object bin/test-physical-object)
add_test(test-physical-engine bin/test-physical-engine)
add_test(test-graphical-engine bin/test-graphical-engine)


# Configuration du type de build
set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

# Configuration du dossier de sortie pour les exécutables
set(EXECUTABLE_OUTPUT_PATH bin)

# Ajout des sous-répertoire Physical_Engine et Graphical_Engine
add_subdirectory(include/Physical_Engine)
add_subdirectory(include/Graphical_Engine)
add_subdirectory(EmptyDoxygenCMake)

# Ajout de la librairie Physical_Engine
#add_library(Physical_Engine STATIC lib/libPhysical_Engine.a)

# Configuration des exécutables
add_executable(BrickBreaker src/main.cpp src/Game_Engine.cpp)

# Configuration des tests
add_executable(test-physical-object src/tests/test-physical-object.cpp)
add_executable(test-circle-drawing  src/tests/test-circle-drawing.cpp)
add_executable(test-image-drawing   src/tests/test-image-drawing.cpp)
add_executable(test-gif-drawing     src/tests/test-gif-drawing.cpp)
add_executable(test-render-drawing  src/tests/test-render-drawing.cpp)
add_executable(test-shared-ptr     src/tests/test-shared-ptr.cpp)
add_executable(test-physical-engine src/tests/test-physical-engine.cpp)
add_executable(test-graphical-engine src/tests/test-graphical-engine.cpp)


# Configuration des bibliothèques SDL
find_package(SDL2 REQUIRED)
# Configuration des bibliothèques SDL_image
find_package(SDL2_image REQUIRED)
# Configuration des bibliothèques SDL_ttf
find_package(SDL2_ttf REQUIRED)
# Configuration des bibliothèques SDL_mixer
find_package(SDL2_mixer REQUIRED)


# Ajout des dépendances pour les exécutables

# Lier votre l'exécutable avec la bibliothèque Physical_Engine
target_link_libraries(test-physical-object Physical_Engine)

# Lier les exécutables avec les bibliothèques SDL
target_include_directories(test-circle-drawing PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(test-circle-drawing PRIVATE ${SDL2_LIBRARIES})

# Lier les exécutables avec les bibliothèques SDL_image
target_include_directories(test-image-drawing PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(test-image-drawing PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

target_include_directories(test-gif-drawing PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(test-gif-drawing PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

target_include_directories(test-render-drawing PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(test-render-drawing PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

target_link_libraries(test-graphical-engine PRIVATE Physical_Engine Graphical_Engine)
target_link_libraries(test-physical-engine PRIVATE Physical_Engine)


# Lier les exécutables avec les bibliothèques SDL_ttf
target_include_directories(BrickBreaker PRIVATE ${SDL2_MIXER_INCLUDE_DIRS})
target_link_libraries(BrickBreaker PRIVATE Physical_Engine Graphical_Engine ${SDL2_MIXER_LIBRARIES})




# Installer l'exécutable main
install(TARGETS BrickBreaker DESTINATION bin)
