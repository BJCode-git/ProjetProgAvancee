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
/*
Graphical_Engine::Graphical_Engine(std::shared_ptr<SDL_Renderer> renderer,
								 int scene_width,
								 int scene_height,
								 uint16_t fps_limit) :
	renderer(renderer),
	fps_limit(fps_limit),
	window_width(scene_width),
	window_height(scene_height)
{
	//debug("Graphical_Engine::Graphical_Engine()");


}*/

Graphical_Engine::Graphical_Engine(int width, int height, uint16_t fps_limit) :
	is_text_to_draw(false),
	animated_background(nullptr),
	static_background(nullptr),
	textures(),
	window(nullptr),
	font(nullptr,TTF_CloseFont),
	fps_limit(60),
	running(false)
{
	//debug("Graphical_Engine::Graphical_Engine()");
	window = std::make_unique<Window>("Casse-briques Test", width, height);
	renderer = window->get_renderer();

	set_background("rsc/bg.gif", true);

	if(SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0 ){
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	constexpr int IMG_INIT_ALL = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP;

	if( (IMG_Init(IMG_INIT_ALL)  &IMG_INIT_ALL) != ( IMG_INIT_ALL )) {
		std::cerr << "Erreur lors de l'initialisation de SDL_image : " << IMG_GetError() << std::endl;
		throw std::runtime_error("Erreur lors de l'initialisation de SDL_image");
	}
	else if(TTF_Init() < 0){
		std::cerr << "Erreur lors de l'initialisation de SDL_ttf : " << TTF_GetError() << std::endl;
		throw std::runtime_error("Erreur lors de l'initialisation de SDL_ttf");
	}


	font = std::unique_ptr<TTF_Font,void (*)(TTF_Font*)>( TTF_OpenFont("rsc/mario.ttf", 40),
														  TTF_CloseFont);

	if(font.get() == nullptr){
		std::cerr << "Error: " << TTF_GetError() << std::endl;
	}

}

Graphical_Engine::~Graphical_Engine() {
	//debug("Graphical_Engine::~Graphical_Engine()");

	TTF_CloseFont(font.get());
	IMG_Quit();
	TTF_Quit();
	SDL_QuitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
}

void Graphical_Engine::addObject(std::shared_ptr<Convex_Polygon> object, std::string texture_path) {
	addGraphicalPolygon(object, texture_path);
}

void Graphical_Engine::addObject(std::shared_ptr<Circle> object, std::string texture_path) {
	addGraphicalCircle(object, texture_path);
}

void Graphical_Engine::addGraphicalPolygon(std::shared_ptr<Convex_Polygon> PhyObject, std::string texture_path) {
	if (texture_path.empty()) {
		objects.emplace_back(new GraphicalPolygon(PhyObject, nullptr));
	} 
	else {
		// on ajoute la texture à la liste des textures si elle n'existe pas
		if (textures.find(texture_path) == textures.end()) {
			textures[texture_path] = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderer.get(), texture_path.c_str()), SDL_DestroyTexture);
		}
		else {
			objects.emplace_back(new GraphicalPolygon(PhyObject, textures[texture_path]));
		}
	}
}

void Graphical_Engine::addGraphicalCircle(std::shared_ptr<Circle> PhyObject, std::string texture_path) {
	if (texture_path.empty()) {
		objects.emplace_back(new GraphicalCircle(PhyObject, nullptr));
	} 
	else {
		// on ajoute la texture à la liste des textures si elle n'existe pas
		if (textures.find(texture_path) == textures.end()) {
			textures[texture_path] = std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderer.get(), texture_path.c_str()), SDL_DestroyTexture);
		}
		else {
			objects.emplace_back(new GraphicalCircle(PhyObject, textures[texture_path]));
		}
	}
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


//void Graphical_Engine::setRenderer(std::shared_ptr<SDL_Renderer> renderer) {
//	this->renderer = renderer;
//}

std::shared_ptr<SDL_Renderer> Graphical_Engine::getRenderer() const {
	return renderer;
}


void Graphical_Engine::print_text(const std::string text){

	//debug(text);
	text_to_print.first = text;
	text_to_print.second = {static_cast<float>(window->get_width()/2), 
							static_cast<float>(window->get_height()/2)};
	is_text_to_draw = true;
} 


void Graphical_Engine::draw_text(){
	if(is_text_to_draw){
		SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE};

		
		SDL_Surface *surface = TTF_RenderText_Solid(font.get(), text_to_print.first.c_str(), color);
		if(surface == nullptr){
			std::cerr << "Error: " << TTF_GetError() << std::endl;
			return;
		}

		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
		if(texture == nullptr){
			std::cerr << "Error: " << SDL_GetError() << std::endl;
			return;
		}

		SDL_FreeSurface(surface);

		// On va afficher le au centre de la fenêtre
		
		//text_to_print.second[0] -= surface->w/2;
		//text_to_print.second[1] -= surface->h/2; ;

		SDL_FRect dest ={text_to_print.second[0] - surface->w/2 ,
						 text_to_print.second[1] - surface->h/2 ,
						 static_cast<float>(surface->w),
						 static_cast<float>(surface->h)
						};

		SDL_RenderCopyF(renderer.get(), texture, NULL, &dest);
		SDL_DestroyTexture(texture);
	}
}

void Graphical_Engine::set_background(std::string filepath, bool animated){

	//debug("Graphical_Engine::set_background()");

	if(animated_background != nullptr){
		IMG_FreeAnimation(animated_background);
		animated_background = nullptr;
	}

	if(static_background != nullptr){
		SDL_FreeSurface(static_background);
		static_background = nullptr;
	}

	if(animated){
		animated_background = IMG_LoadAnimation(filepath.c_str());
	}
	else{
		static_background = IMG_Load(filepath.c_str());
	}

	if(animated_background == nullptr && static_background == nullptr){
		std::cerr << "Graphical_Engine::set_background() Error: " << IMG_GetError() << std::endl;
		exit(1);
	}
}

void Graphical_Engine::draw_background(){

	//debug("Graphical_Engine::draw_background()");

	SDL_Texture* texture = nullptr;
	SDL_FRect dstRect = { 0,
						  0,
						  static_cast<float>(get_win_width()), 
						  static_cast<float>(get_win_height())
						};
			
	if(animated_background != nullptr){
		static int n = 0;
		texture = SDL_CreateTextureFromSurface(renderer.get(), animated_background->frames[n]);
		n = (n + 1) % animated_background->count;
	}
	else if(static_background != nullptr){
		texture = SDL_CreateTextureFromSurface(renderer.get(), static_background);
	}
	else{
		std::cerr << "Graphical_Engine::draw_background() Error: " << IMG_GetError() << std::endl;
	}

	if(texture){
		SDL_RenderCopyF(renderer.get(), texture, nullptr, &dstRect);
		SDL_DestroyTexture(texture);
	}
	else{
		std::cerr << "Error: " << SDL_GetError() << std::endl;
	}
}


void Graphical_Engine::draw(){
	

	auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	debug("Graphical_Engine::draw()" +  (std::string) std::ctime(&timenow) +"\n"  );

	clear();
	

	// Affichage du background
	draw_background();
	
	// Affichage des objets
	auto it = objects.begin();
	while (it != objects.end()) {
		if ((*it)->PhyObjLife() <= 0) {
			it = objects.erase(it);
		} 
		else {
			////debug("\t Graphical_Engine::draw() : draw object");
			(*it)->draw(renderer);
			++it;
		}
	}

	// Affichage du texte
	draw_text();

	SDL_RenderPresent(renderer.get());
}

void Graphical_Engine::clear(){
	SDL_SetRenderDrawColor(renderer.get(), 0, 60, 124, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer.get());
}

void Graphical_Engine::start(){
	SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);
	running = true;
	//debug("Graphical_Engine::start()");

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

	//debug("Graphical_Engine::start() reach end of loop");
}

void Graphical_Engine::stop(){
	//debug("Graphical_Engine::stop()");
	running = false;
}

