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

		Graphical_Object(std::shared_ptr<Physical_Object> PhyObject);
		~Graphical_Object();

		virtual void draw(std::shared_ptr<SDL_Renderer>> renderer) const = 0;
		
		Color getColor() const;
		void setColor(Color color);

		std::shared_ptr<SDL_Texture> getTexture() const;
		void setTexture(std::shared_ptr<SDL_Texture> texture);


	protected:

		Color color;
		
		// On va dessiner l'objet selon sa forme et sa position
		std::shared_ptr<Physical_Object> PhyObject;
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


class Graphical_Engine{

	public:

		Graphical_Engine(SDL_Renderer* renderer, uint16_t fps_limit = 60);
		~Graphical_Engine();

		void setRenderer(std::shared_ptr<SDL_Renderer> renderer);
		std::shared_ptr<SDL_Renderer> getRenderer() const;
		
		void draw();
		void clear();

		void addObject(std::unique_ptr<Graphical_Object> object,
					   std::shared_ptr<SDL_Texture> texture = std::shared_ptr(nullptr));
		void addGraphicalPolygon(std::shared_ptr<Physical_Object> PhyObject,
								 std::shared_ptr<SDL_Texture> texture = std::shared_ptr(nullptr));
		void addGraphicalCircle(std::shared_ptr<Physical_Object> PhyObject,
								std::shared_ptr<SDL_Texture> texture = std::shared_ptr(nullptr));
		void removeObject(std::unique_ptr<Graphical_Object> object);

		void setFPSLimit(uint16_t fps_limit);
		void getFPSLimit() const;


	private:
		std::vector<std::unique_ptr<Graphical_Object>> objects;
		std::shared_ptr<SDL_Renderer> renderer;

		uint16_t fps_limit;
		int window_width;
		int window_height;
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

Graphical_Object::Graphical_Object(std::shared_ptr<Physical_Object> PhyObject, std::shared_ptr<SDL_Texture> texture) : 
	PhyObject(PhyObject),
	color(WHITE),
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
	} else {
		SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
		drawFilledCircle(renderer.get(), PhyObject->getPosition()[0], PhyObject->getPosition()[1], PhyObject->getRadius());
	}

}


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
	else {

		SDL_SetRenderDrawColor(renderer.get(), color.r, color.g, color.b, color.a);
		const std::vector<Point2DF>& points = PhyObject->getPoints();
		for (size_t i = 0; i < points.size(); i++) {
			SDL_RenderDrawLineF(renderer.get(), points[i][0], points[i][1], points[(i + 1) % points.size()][0], points[(i + 1) % points.size()][1]);
		}
	}

}

/******************
 * Graphical_Engine *
 ******************/

Graphical_Engine::Graphical_Engine(std::shared_ptr<SDL_Renderer> renderer,
								 int scene_width,
								 int scene_height,
								 uint16_t fps_limit) :
	renderer(renderer),
	fps_limit(fps_limit),
	window_width(scene_width),
	window_height(scene_height)
{
	debug("Graphical_Engine::Graphical_Engine()");


}

Graphical_Engine::~Graphical_Engine() {
	debug("Graphical_Engine::~Graphical_Engine()");
	IMG_Quit();
}

void Graphical_Engine::addObject(std::shared_ptr<Convex_Polygon> object, std::shared_ptr<SDL_Texture> texture) {
	addGraphicalPolygon(object, texture);
}

void Graphical_Engine::addObject(std::shared_ptr<Circle> object, std::shared_ptr<SDL_Texture> texture) {
	addGraphicalCircle(object, texture);
}

void Graphical_Engine::addGraphicalPolygon(std::shared_ptr<Convex_Polygon> PhyObject, std::shared_ptr<SDL_Texture> texture) {
	objects.emplace_back( new GraphicalPolygon(PhyObject, texture));
}

void Graphical_Engine::addGraphicalCircle(std::shared_ptr<Circle> PhyObject, std::shared_ptr<SDL_Texture> texture) {
	objects.emplace_back(new GraphicalCircle(PhyObject, texture));
}

void Graphical_Engine::removeObject(size_t index) {
	objects.erase(objects.begin() + index);
}

void Graphical_Engine::setFPSLimit(uint16_t fps_limit) {
	this->fps_limit = fps_limit;
}

int Graphical_Engine::getFPSLimit() const {
	return fps_limit;
}


void Graphical_Engine::setRenderer(std::shared_ptr<SDL_Renderer> renderer) {
	this->renderer = renderer;
}

std::shared_ptr<SDL_Renderer> Graphical_Engine::getRenderer() const {
	return renderer;
}


void Graphical_Engine::draw(){
	

	auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	debug("Graphical_Engine::draw()" +  (std::string) std::ctime(&timenow) +"\n"  );
	

	clear();
	auto it = objects.begin();
	while (it != objects.end()) {
		if ((*it)->PhyObjLife() <= 0) {
			it = objects.erase(it);
		} 
		else {
			(*it)->draw(renderer);
			++it;
		}
	}

	SDL_RenderPresent(renderer.get());
}

void Graphical_Engine::clear(){
	SDL_SetRenderDrawColor(renderer.get(), 0, 60, 124, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer.get());
}

void Graphical_Engine::start(){
	SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);
	running = true;
	debug("Graphical_Engine::start()");

	constexpr float  fps = 60; //ms
	constexpr float  max_dt= 1000/fps; //ms

	std::chrono::high_resolution_clock::time_point last_time = std::chrono::high_resolution_clock::now(), 
												   current_time;
  
	std::chrono::duration<float, std::milli> delta;
	float dt = 0;
	
	while(running){
	
		// On calcule le temps écoulé depuis le dernier appel à update en ms
		current_time = std::chrono::high_resolution_clock::now();
		delta = current_time - last_time;
		last_time = current_time;
		dt = delta.count();
		
		// On limite le nombre d'images par seconde à fps
		if(dt >= max_dt) draw();

		else std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(max_dt - dt));
	}

	debug("Graphical_Engine::start() reach end of loop");
}

void Graphical_Engine::stop(){
	debug("Graphical_Engine::stop()");
	running = false;
}

