cmake_minimum_required(VERSION 3.17)
project(Graphical_Engine)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-std=c++20 -O3 -g -Wall -Wextra -pedantic -pthread -Werror")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/Build)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ../../cmake_modules/)

# Ajout du dossier Physical_Engine pour les fichiers d'en-tête
include_directories(Graphical_Engine)

# Ajout des fichiers source de la bibliothèque
set(SOURCES
    debug-SDL.cpp
    Graphical_Engine.cpp
    Graphical_Object/Graphical_Object.cpp
    Graphical_Circle/Graphical_Circle.cpp
    Graphical_Polygon/Graphical_Polygon.cpp
    Window/Window.cpp
)

# Ajout des fichiers d'en-tête de la bibliothèque
set(HEADERS
    debug-SDL.hpp
    Graphical_Engine.hpp
    Graphical_Object/Graphical_Object.hpp
    Graphical_Circle/Graphical_Circle.hpp
    Graphical_Polygon/Graphical_Polygon.hpp
    Window/Window.hpp
)

# Création de la bibliothèque
add_library(Graphical_Engine ${SOURCES} ${HEADERS})

# Recherche des bibliothèque SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Spécification des répertoires d'inclusion pour la bibliothèque
target_include_directories(Graphical_Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Graphical_Engine ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(Graphical_Engine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} Physical_Engine)

# Définition des répertoires de sortie pour les binaires et les bibliothèques
set(EXECUTABLE_OUTPUT_PATH ../../bin)
set(LIBRARY_OUTPUT_PATH ../../lib)

# Installation de la bibliothèque
install(TARGETS  Graphical_Engine
        LIBRARY  DESTINATION lib
        ARCHIVE  DESTINATION lib
        RUNTIME  DESTINATION bin
        INCLUDES DESTINATION include
)
