#ifndef GRAPHICAL_CIRCLE_HPP
#define GRAPHICAL_CIRCLE_HPP

#include <iostream>
#include <memory>
#include <chrono>
#include <ctime>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include "Physical_Engine/Circle/Circle.hpp"
#include "Graphical_Engine/Graphical_Object/Graphical_Object.hpp"
#include "debug.hpp"


// Algorithme de Bresenham pour dessiner un cercle rempli
/**
 * @brief Draw a filled circle.
 * @param renderer The SDL_Renderer object to draw the circle with.
 * @param x The x coordinate of the center of the circle.
 * @param y The y coordinate of the center of the circle.
 * @param radius The radius of the circle.
 */
void drawFilledCircle(SDL_Renderer* renderer, float x, float y, float radius);

// Algorithme de Bresenham pour dessiner un cercle
/**
 * @brief Draw a circle.
 * @param renderer The SDL_Renderer object to draw the circle with.
 * @param x The x coordinate of the center of the circle.
 * @param y The y coordinate of the center of the circle.
 * @param radius The radius of the circle.
 */
void drawCircle(SDL_Renderer* renderer, float x, float y, float radius);


/**
 * @brief GraphicalCircle class which represents a graphical circle entity.
 */
class GraphicalCircle : public Graphical_Object{

	public:

		/**
		 * @brief GraphicalCircle constructor.
		 * @param Circle The Circle object to be drawn.
		 * @param texture The texture to be applied to the Circle object.
		 */
		GraphicalCircle(std::shared_ptr<Circle> Circle, 
						std::shared_ptr<SDL_Texture> texture = std::shared_ptr<SDL_Texture>(nullptr));
		/**
		 * @brief GraphicalCircle destructor.
		 */
		~GraphicalCircle();

		/**
		 * @brief Draws the Circle object to the screen.
		 * @param renderer The SDL_Renderer object to draw the Circle object with.
		 */
		virtual void draw(std::shared_ptr<SDL_Renderer> renderer) const override;

	private:
		std::shared_ptr<Circle> PhyObject;
};

#endif // GRAPHICAL_CIRCLE_HPP