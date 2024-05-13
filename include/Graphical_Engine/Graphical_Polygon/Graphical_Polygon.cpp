#include "Graphical_Polygon.hpp"

/********************
 * GraphicalPolygon *
 ********************/

GraphicalPolygon::GraphicalPolygon(std::shared_ptr<Convex_Polygon> Polygon, std::shared_ptr<SDL_Texture> texture) :
	Graphical_Object(Polygon, texture),
	PhyObject(Polygon)
{}

GraphicalPolygon::~GraphicalPolygon() {}

void GraphicalPolygon::draw(std::shared_ptr<SDL_Renderer> renderer) const {

	if(texture) {
		Point2DF topLeft     = PhyObject->getBoundingBox().getTopLeft(),
				 topRight    = PhyObject->getBoundingBox().getTopRight(),
				 bottomRight = PhyObject->getBoundingBox().getBottomRight(),
				 bottomLeft  = PhyObject->getBoundingBox().getBottomLeft();
				
		SDL_RenderDrawLineF(renderer.get(), topLeft[0], topLeft[1], topRight[0], topRight[1]);
		SDL_RenderDrawLineF(renderer.get(), topRight[0], topRight[1], bottomRight[0], bottomRight[1]);
		SDL_RenderDrawLineF(renderer.get(), bottomRight[0], bottomRight[1], bottomLeft[0], bottomLeft[1]);
		SDL_RenderDrawLineF(renderer.get(), bottomLeft[0], bottomLeft[1], topLeft[0], topLeft[1]);
		//SDL_Rect dest = {topLeft[0], topLeft[1], topRight[0] - topLeft[0], bottomRight[1] - topRight[1]};
		//SDL_RenderCopy(renderer.get(), texture.get(), NULL, &dest);
	}
	

	SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
	const std::vector<Point2DF>& points = PhyObject->getPoints();
	for (size_t i = 0; i < points.size(); i++) {
		SDL_RenderDrawLineF(renderer.get(), points[i][0], points[i][1], points[(i + 1) % points.size()][0], points[(i + 1) % points.size()][1]);
	}
	

}