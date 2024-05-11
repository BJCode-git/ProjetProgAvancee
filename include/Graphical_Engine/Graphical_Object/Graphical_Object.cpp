#include "Graphical_Engine/Graphical_Object/Graphical_Object.hpp"

/********************
 * Graphical_Object *
 ********************/

Graphical_Object::Graphical_Object(std::shared_ptr<Physical_Object> PhyObject, std::shared_ptr<SDL_Texture> texture) : 
	PhyObject(PhyObject),
	color(GREEN),
	texture(texture)
{}

Graphical_Object::~Graphical_Object() {}

int Graphical_Object::PhyObjLife() const {
	return PhyObject->getLife();
}

Color Graphical_Object::getColor() const {
	return color;
}

void Graphical_Object::setColor(Color color) {
	this->color = color;
}

std::shared_ptr<SDL_Texture> Graphical_Object::getTexture() const {
	return texture;
}

void Graphical_Object::setTexture(std::shared_ptr<SDL_Texture> texture) {
	this->texture = texture;
}

void Graphical_Object::draw(std::shared_ptr<SDL_Renderer> renderer) const {
	
		SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
		Point2DF topLeft     = PhyObject->getBoundingBox().getTopLeft(),
				 topRight    = PhyObject->getBoundingBox().getTopRight(),
				 bottomRight = PhyObject->getBoundingBox().getBottomRight(),
				 bottomLeft  = PhyObject->getBoundingBox().getBottomLeft();
				
		SDL_RenderDrawLineF(renderer.get(), topLeft[0], topLeft[1], topRight[0], topRight[1]);
		SDL_RenderDrawLineF(renderer.get(), topRight[0], topRight[1], bottomRight[0], bottomRight[1]);
		SDL_RenderDrawLineF(renderer.get(), bottomRight[0], bottomRight[1], bottomLeft[0], bottomLeft[1]);
		SDL_RenderDrawLineF(renderer.get(), bottomLeft[0], bottomLeft[1], topLeft[0], topLeft[1]);
	
}
