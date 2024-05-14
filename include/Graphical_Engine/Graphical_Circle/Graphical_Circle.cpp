#include "Graphical_Engine/Graphical_Circle/Graphical_Circle.hpp"


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



/******************
 * GraphicalCircle *
 ******************/

GraphicalCircle::GraphicalCircle(std::shared_ptr<Circle> Circle, std::shared_ptr<SDL_Texture> texture) :
	Graphical_Object(Circle, texture),
	PhyObject(Circle)
{}

GraphicalCircle::~GraphicalCircle() {}

void GraphicalCircle::draw(std::shared_ptr<SDL_Renderer> renderer) const {

	if(texture) {
		SDL_FRect dest = {PhyObject->getPosition()[0] - PhyObject->getRadius(), 
						  PhyObject->getPosition()[1] - PhyObject->getRadius(), 
						  2 * PhyObject->getRadius(), 
						  2 * PhyObject->getRadius()};

		SDL_RenderCopyF(renderer.get(), texture.get(), NULL, &dest);
	}
	SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
	drawFilledCircle(renderer.get(), PhyObject->getPosition()[0], PhyObject->getPosition()[1], PhyObject->getRadius());

	Graphical_Object::draw(renderer);
}

