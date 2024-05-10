cmake_minimum_required(VERSION 3.17)
# Définition de la bibliothèque Physical_Engine

# Ajout du dossier Physical_Engine pour les fichiers d'en-tête
include_directories(Physical_Engine)

# Ajout des fichiers source de la bibliothèque
set(SOURCES
    Physical_Engine.cpp
    Physical_Object/Physical_Object.cpp
	Convex_Polygon/Convex_Polygon.cpp
    Circle/Circle.cpp
    BoundingBox/BoundingBox.cpp
)

# Ajout des fichiers d'en-tête de la bibliothèque
set(HEADERS
    Physical_Engine.hpp
	Physical_Object/Physical_Object.hpp
    Convex_Polygon/Convex_Polygon.hpp
    Circle/Circle.hpp
    BoundingBox/BoundingBox.hpp
    NumericVector.hpp
)

# Création de la bibliothèque
add_library(Physical_Engine ${SOURCES} ${HEADERS})

# Recherche de la bibliothèque SDL2
find_package(SDL2 REQUIRED)

# Spécification des répertoires d'inclusion pour la bibliothèque
target_include_directories(Physical_Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Physical_Engine ${SDL2_INCLUDE_DIRS})
target_link_libraries(Physical_Engine ${SDL2_LIBRARIES})

# Définition des répertoires de sortie pour les binaires et les bibliothèques
set(EXECUTABLE_OUTPUT_PATH ../../bin)
set(LIBRARY_OUTPUT_PATH ../../lib)

# Installation de la bibliothèque
install(TARGETS  Physical_Engine
        LIBRARY  DESTINATION lib
        ARCHIVE  DESTINATION lib
        RUNTIME  DESTINATION bin
        INCLUDES DESTINATION include
)
