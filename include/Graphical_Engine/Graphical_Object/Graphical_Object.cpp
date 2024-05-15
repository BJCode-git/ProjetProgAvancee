#include "Graphical_Engine/Graphical_Object/Graphical_Object.hpp"

/********************
 * Graphical_Object *
 ********************/

Graphical_Object::Graphical_Object(std::shared_ptr<Physical_Object> PhyObject, std::shared_ptr<SDL_Texture> texture) : 
	color(BLACK),
	PhyObject(PhyObject),
	texture(texture)
{
}

Graphical_Object::~Graphical_Object() {}

int Graphical_Object::PhyObjLife() const {
	return PhyObject == nullptr ? 0 : PhyObject->getLife();
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

	if(PhyObject == nullptr)
		return;

	SDL_SetRenderDrawColor(renderer.get(), RED.r, RED.g, RED.b, RED.a);
	Point2DF topLeft     = PhyObject->getBoundingBox().getTopLeft(),
			 topRight    = PhyObject->getBoundingBox().getTopRight(),
			 bottomRight = PhyObject->getBoundingBox().getBottomRight();
			

	SDL_FRect dest = {topLeft[0], topLeft[1], topRight[0] - topLeft[0], bottomRight[1] - topRight[1]};
	
	if(texture)
		SDL_RenderCopyF(renderer.get(), texture.get(), NULL, &dest);
	else
		SDL_RenderFillRectF(renderer.get(), &dest);
	
}
