#ifndef GRAPHICAL_OBJECT_HPP

#include <iostream>
#include <memory>

#include <SDL2/SDL.h>

#include "Physical_Engine.hpp"


// Algrithme de Bresenham pour dessiner un cercle rempli
void drawFilledCircle(SDL_Renderer* renderer, float x, float y, float radius) {
	float dx = radius - 1;
	float dy = 0;
	float err = 1 - dx;

	while (dx >= dy) {
		SDL_RenderDrawLineF(renderer, x - dx, y + dy, x + dx, y + dy);
		SDL_RenderDrawLineF(renderer, x - dx, y - dy, x + dx, y - dy);
		SDL_RenderDrawLineF(renderer, x - dy, y + dx, x + dy, y + dx);
		SDL_RenderDrawLineF(renderer, x - dy, y - dx, x + dy, y - dx);

		dy++;
		if (err < 0) {
			err += 2 * dy + 1;
		} else {
			dx--;
			err += 2 * (dy - dx) + 1;
		}
	}
}
// Algorithme de Bresenham pour dessiner un cercle
void drawCircle(SDL_Renderer* renderer, float x, float y, float radius) {
	int dx = radius - 1;
	int dy = 0;
	int err = 1 - dx;

	while (dx >= dy) {
		SDL_RenderDrawPointF(renderer, x + dx, y + dy);
		SDL_RenderDrawPointF(renderer, x - dx, y + dy);
		SDL_RenderDrawPointF(renderer, x + dx, y - dy);
		SDL_RenderDrawPointF(renderer, x - dx, y - dy);
		SDL_RenderDrawPointF(renderer, x + dy, y + dx);
		SDL_RenderDrawPointF(renderer, x - dy, y + dx);
		SDL_RenderDrawPointF(renderer, x + dy, y - dx);
		SDL_RenderDrawPointF(renderer, x - dy, y - dx);

		dy++;
		if (err < 0) {
			err += 2 * dy + 1;
		} else {
			dx--;
			err += 2 * (dy - dx) + 1;
		}
	}
}


struct Color{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

using BLUE  = Color{  0,   0, 255, 255};
using RED   = Color{255,   0,   0, 255};
using GREEN = Color{  0, 255,   0, 255};
using BLACK = Color{  0,   0,   0, 255};
using WHITE = Color{255, 255, 255, 255};

class Graphical_Object : public Graphical_Object{

	public:

		Graphical_Object_SDL(std::shared_ptr<Physical_object> PhyObject);
		~Graphical_Object_SDL();

		void draw(std::shared_ptr<SDL_Renderer>> renderer);
		void setColor(Color color);
		void getColor();
		

	private:
		Color color;
		std::shared_ptr<SDL_Renderer> renderer;
		// On va dessiner l'objet selon sa forme et sa position
		std::shared_ptr<Physical_object> PhyObject;
};


class GraphicalEngine{

	public:

		GraphicalEngine(SDL_Renderer* renderer);
		~GraphicalEngine();

		void draw();
		void clear();
		void addObject(std::shared_ptr<Graphical_Object> object);
		void removeObject(std::shared_ptr<Graphical_Object> object);


	private:
		std::vector<std::shared_ptr<Graphical_Object>> objects;
	
};





#endif // GRAPHICAL_OBJECT_HPP