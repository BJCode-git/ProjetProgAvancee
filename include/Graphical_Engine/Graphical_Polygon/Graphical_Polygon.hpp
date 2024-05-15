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

		/**
		 * @brief GraphicalPolygon constructor.
		 * @param Polygon The Convex_Polygon object to be drawn.
		 * @param texture The texture to be applied to the Convex_Polygon object.
		 */
		GraphicalPolygon(std::shared_ptr<Convex_Polygon> Polygon, 
						 std::shared_ptr<SDL_Texture> texture = std::shared_ptr<SDL_Texture>(nullptr));
		/**
		 * @brief GraphicalPolygon destructor.
		 */
		~GraphicalPolygon();

		/**
		 * @brief Draws the Convex_Polygon object to the screen.
		 * @param renderer The SDL_Renderer object to draw the Convex_Polygon object with.
		 */
		virtual void draw(std::shared_ptr<SDL_Renderer> renderer) const override;

	private:
		// On va dessiner l'objet selon sa forme et sa position
		std::shared_ptr<Convex_Polygon> PhyObject;
};


#endif // GRAPHICAL_POLYGON_HPP