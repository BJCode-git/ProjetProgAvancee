#ifndef GRAPHICAL_POLYGON_HPP
#define GRAPHICAL_POLYGON_HPP

#include <iostream>
#include <memory>
#include <chrono>
#include <ctime>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include "Physical_Engine/Convex_Polygon/Convex_Polygon.hpp"
#include "Graphical_Engine/Graphical_Object/Graphical_Object.hpp"
#include "debug.hpp"


class GraphicalPolygon : public Graphical_Object{

	public:

		GraphicalPolygon(std::shared_ptr<Convex_Polygon> Polygon, 
						 std::shared_ptr<SDL_Texture> texture = std::shared_ptr<SDL_Texture>(nullptr));
		~GraphicalPolygon();

		virtual void draw(std::shared_ptr<SDL_Renderer> renderer) const override;

	private:
		// On va dessiner l'objet selon sa forme et sa position
		std::shared_ptr<Convex_Polygon> PhyObject;
};


#endif // GRAPHICAL_POLYGON_HPP