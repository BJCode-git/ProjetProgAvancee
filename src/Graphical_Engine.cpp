#include "Graphical_Engine.hpp"

/*

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

		Graphical_Object(std::shared_ptr<Physical_object> PhyObject);
		~Graphical_Object();

		virtual void draw(std::shared_ptr<SDL_Renderer>> renderer) const = 0;
		
		Color getColor() const;
		void setColor(Color color);

		std::shared_ptr<SDL_Texture> getTexture() const;
		void setTexture(std::shared_ptr<SDL_Texture> texture);


	protected:

		Color color;
		
		// On va dessiner l'objet selon sa forme et sa position
		std::shared_ptr<Physical_object> PhyObject;
		std::shared_ptr<SDL_Texture> texture;
};


class GraphicalCircle : public Graphical_Object{

	public:

		GraphicalCircle(std::shared_ptr<Circle> Circle);
		~GraphicalCircle();

		virtual void draw(std::shared_ptr<SDL_Renderer>> renderer) const override;

	private:
		std::shared_ptr<Circle> PhyObject;
};

class GraphicalPolygon : public Graphical_Object{

	public:

		GraphicalPolygon(std::shared_ptr<Convex_Polygon> Polygon);
		~GraphicalPolygon();

		virtual void draw(std::shared_ptr<SDL_Renderer>> renderer) const override;

	private:
		// On va dessiner l'objet selon sa forme et sa position
		std::shared_ptr<Convex_Polygon> PhyObject;
};

class GraphicalEngine{

	public:

		GraphicalEngine(SDL_Renderer* renderer);
		~GraphicalEngine();

		void draw();
		void clear();

		void addObject(std::unique_ptr<Graphical_Object> object,
					   std::shared_ptr<SDL_Texture> texture = std::shared_ptr(nullptr));
		void addGraphicalPolygon(std::shared_ptr<Physical_object> PhyObject,
								 std::shared_ptr<SDL_Texture> texture = std::shared_ptr(nullptr));
		void addGraphicalCircle(std::shared_ptr<Physical_object> PhyObject,
								std::shared_ptr<SDL_Texture> texture = std::shared_ptr(nullptr));
		void removeObject(std::unique_ptr<Graphical_Object> object);


	private:
		std::vector<std::unique_ptr<Graphical_Object>> objects;
		std::shared_ptr<SDL_Renderer> renderer;

};

*/

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



/********************
 * Graphical_Object *
 ********************/

Graphical_Object::Graphical_Object(std::shared_ptr<Physical_object> PhyObject) : 
	PhyObject(PhyObject) 
{}

Graphical_Object::~Graphical_Object() {}

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

/******************
 * GraphicalCircle *
 ******************/

GraphicalCircle::GraphicalCircle(std::shared_ptr<Circle> Circle) :
	Graphical_Object(Circle),
	PhyObject(Circle)
{}

GraphicalCircle::~GraphicalCircle() {}

void GraphicalCircle::draw(std::shared_ptr<SDL_Renderer> renderer) const {

	if(texture) {
		SDL_Rect dest = {PhyObject->getCenter().x - PhyObject->getRadius(), PhyObject->getCenter().y - PhyObject->getRadius(), 2 * PhyObject->getRadius(), 2 * PhyObject->getRadius()};
		SDL_RenderCopy(renderer.get(), texture.get(), NULL, &dest);
	} else {
		SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
		drawFilledCircle(renderer.get(), PhyObject->getCenter().x, PhyObject->getCenter().y, PhyObject->getRadius());
	}

}


/********************
 * GraphicalPolygon *
 ********************/

GraphicalPolygon::GraphicalPolygon(std::shared_ptr<Convex_Polygon> Polygon) :
	Graphical_Object(Polygon),
	PhyObject(Polygon)
{}

GraphicalPolygon::~GraphicalPolygon() {}

void GraphicalPolygon::draw(std::shared_ptr<SDL_Renderer> renderer) const {

	if(texture) {
		Point2DF topLeft     = PhyObject->getBoundingBox().getTopLeft(),
				 topRight    = PhyObject->getBoundingBox().getTopRight(),
				 bottomRight = PhyObject->getBoundingBox().getBottomRight(),
				 bottomLeft  = PhyObject->getBoundingBox().getBottomLeft();
				
		float x =std::min({topLeft.x, topRight.x, bottomRight.x, bottomLeft.x}),
			  y =std::min({topLeft.y, topRight.y, bottomRight.y, bottomLeft.y}),
			  width = std::max({topLeft.x, topRight.x, bottomRight.x, bottomLeft.x}) - x,
			  height = std::max({topLeft.y, topRight.y, bottomRight.y, bottomLeft.y}) - y;

		SDL_Rect dest = {x, y,width, height};

		SDL_RenderCopy(renderer.get(), texture.get(), NULL, &dest);
	} 
	else {

		SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
		const std::vector<Point2DF>& points = PhyObject->getPoints();
		for (size_t i = 0; i < points.size(); i++) {
			SDL_RenderDrawLineF(renderer.get(), points[i][0], points[i][1], points[(i + 1) % points.size()][0], points[(i + 1) % points.size()][1]);
		}
	}

}