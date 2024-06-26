#include "Graphical_Engine/Graphical_Engine.hpp"

/******************
 * Graphical_Engine *
 ******************/

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

