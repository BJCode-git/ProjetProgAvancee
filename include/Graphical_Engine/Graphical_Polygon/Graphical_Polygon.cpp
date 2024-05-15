#include "Graphical_Polygon.hpp"
#include <cmath>

/********************
 * GraphicalPolygon *
 ********************/

GraphicalPolygon::GraphicalPolygon(std::shared_ptr<Convex_Polygon> Polygon, std::shared_ptr<SDL_Texture> texture) :
	Graphical_Object(Polygon, texture),
	PhyObject(Polygon)
{}

GraphicalPolygon::~GraphicalPolygon() {}

void GraphicalPolygon::draw(std::shared_ptr<SDL_Renderer> renderer) const {

	if(PhyObject == nullptr)
		return;

	if(texture) {
		Point2DF topLeft     = PhyObject->getBoundingBox().getTopLeft(),
				 topRight    = PhyObject->getBoundingBox().getTopRight(),
				 bottomRight = PhyObject->getBoundingBox().getBottomRight();
		
		//SDL_Rect dest = {topLeft[0], topLeft[1], topRight[0] - topLeft[0], bottomRight[1] - topRight[1]};
		//SDL_RenderCopy(renderer.get(), texture.get(), NULL, &dest);

		// on applique la rotation
		Vector2DF v = topRight - topLeft;
		v.normalize();
		// Calcul de l'angle entre le vecteur et l'axe horizontal
		float angle = atan2(v[1], v[0]);
		// Convertir l'angle de radians à degrés si nécessaire
		// angle = angle * 180.0 / M_PI;

		SDL_FRect dst = {topLeft[0], topLeft[1], std::abs(topRight[0] - topLeft[0]), std::abs(bottomRight[1] - topRight[1])};
		SDL_FPoint rotPoint = {topLeft[0], topLeft[1]};
		std::cout<<"Bouding box : width : "<< topRight[0] - topLeft[0] <<" height : "<< bottomRight[1] - topRight[1]<<std::endl;

		if(SDL_RenderCopyExF(renderer.get(),texture.get(), NULL, &dst, angle, &rotPoint, SDL_FLIP_NONE ) < 0)
			std::cerr << "Error drawing texture polygon: " << SDL_GetError() << std::endl;
	}

	SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
	const std::vector<Point2DF>& points = PhyObject->getPoints();
	for (size_t i = 0; i < points.size(); i++) {
		SDL_RenderDrawLineF(renderer.get(), points[i][0], points[i][1], points[(i + 1) % points.size()][0], points[(i + 1) % points.size()][1]);
	}
	

}