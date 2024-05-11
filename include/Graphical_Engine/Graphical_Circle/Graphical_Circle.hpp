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


// Algrithme de Bresenham pour dessiner un cercle rempli
void drawFilledCircle(SDL_Renderer* renderer, float x, float y, float radius);

// Algorithme de Bresenham pour dessiner un cercle
void drawCircle(SDL_Renderer* renderer, float x, float y, float radius);


class GraphicalCircle : public Graphical_Object{

	public:

		GraphicalCircle(std::shared_ptr<Circle> Circle, 
						std::shared_ptr<SDL_Texture> texture = std::shared_ptr<SDL_Texture>(nullptr));
		~GraphicalCircle();

		virtual void draw(std::shared_ptr<SDL_Renderer> renderer) const override;

	private:
		std::shared_ptr<Circle> PhyObject;
};

#endif // GRAPHICAL_CIRCLE_HPP