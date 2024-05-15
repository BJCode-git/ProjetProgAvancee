#include "Game_Engine.hpp"



GameEngine::GameEngine(int width, int height): 
	running(false),
	paused(true),
	score(0),

	phy_bar(nullptr),
	//window(nullptr),
	graphical_engine(nullptr),
	physical_engine(nullptr),
	music(nullptr,Mix_FreeMusic)
{

	/*
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0 ){
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	constexpr int IMG_INIT_ALL = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP;
	int flags = IMG_INIT_ALL;
	if( (IMG_Init( flags)  &flags) != ( flags )) {
		std::cerr << "Erreur lors de l'initialisation de SDL_image : " << IMG_GetError() << std::endl;
		throw std::runtime_error("Erreur lors de l'initialisation de SDL_image");
	}
	else if(TTF_Init() < 0){
		std::cerr << "Erreur lors de l'initialisation de SDL_ttf : " << TTF_GetError() << std::endl;
		throw std::runtime_error("Erreur lors de l'initialisation de SDL_ttf");
	}
	*/

	if(SDL_InitSubSystem(SDL_INIT_AUDIO) != 0 ){
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) ){
		std::cerr << "Error: " << Mix_GetError() << std::endl;
	}



	//window = std::make_unique<Window>("Casse-briques Test", 960, 540);
	//graphical_engine = std::make_unique<Graphical_Engine>(window->get_renderer(),
	//													  window->get_width(),
	//													  window->get_height());
	graphical_engine.reset(new Graphical_Engine(width,height));
	physical_engine.reset(new Physical_Engine(width,height));


	init();

}

GameEngine::~GameEngine(){
	Mix_Quit();
	SDL_Quit();
}


void GameEngine::init(){

	// on charge la musique
	music.reset(Mix_LoadMUS("rsc/GTO.wav"));
	if(music == nullptr){
		std::cerr << "Error: " << Mix_GetError() << std::endl;
	}
	else{
		Mix_PlayMusic(music.get(),-1);
	}

	// on crée les objets physiques et graphiques

	float width = graphical_engine->get_win_width();
	float height = graphical_engine->get_win_height();

	physical_engine->setScene(width,height);


	// on crée la barre de longueur 70 pixels et de hauteur 10 pixels
	// on la place au milieu de l'écran
	phy_bar = std::make_shared<Convex_Polygon>(Polygon{
		Point2DF{width/2 - 75, height - 15},
		Point2DF{width/2 + 75, height - 15},
		Point2DF{width/2 + 75, height -  5},
		Point2DF{width/2 - 75, height -  5}
	});

	phy_bar->setSpeed(Vector2DF{0,0});
	phy_bar->setBreakable(false);
	phy_bar->setStatic(true);

	// on l'ajoute à l'engine physique
	physical_engine->addObject(phy_bar);
	// on l'ajoute à l'engine graphique
	graphical_engine->addGraphicalPolygon(phy_bar,"rsc/Breakout_Tile_Set_Free/PNG/47-Breakout-Tiles.png");

	// on crée la balle
	// on la place au dessus de la barre
	std::shared_ptr<Circle> ball = std::make_shared<Circle>(Point2DF{width/2, height - 35}, 10);

	// on lui défini une vitesse initiale
	// avec une composante horizontale aléatoire
	// et une composante verticale négative 2*supérieure à la gravité
	// pour qu'elle parte vers le haut
	ball->setSpeed(Vector2DF{ static_cast<float> (std::rand()%100-50), -7.f*10.f});
	ball->setBreakable(false);

	// on l'ajoute à l'engine physique
	physical_engine->addObject(ball);
	// on l'ajoute à l'engine graphique
	graphical_engine->addGraphicalCircle(ball,"rsc/Breakout_Tile_Set_Free/PNG/58-Breakout-Tiles.png");


	// on crée les briques

	// on crée n_lines de 10 briques
	// on les place en haut de l'écran
	// on leur donne une taille de 20 pixels de large et 10 pixels de haut

	constexpr int n_line = 2;
	for(int i = 0; i<n_line; i++){
		// on parcout la largeur de l'écran
		constexpr int n_brick = 5;//(width-10)/(2+20+2);
		constexpr float screen_padding = 5;
		constexpr float brick_padding = 4;
		float brick_width = (width - 2*screen_padding)/(n_brick);
		brick_width -= 2*brick_padding;
		
		/*
		// on place les briques à intervalle régulier
		for(int j=0;j<n_brick; j++){
		*/
		for(int j=0;j<n_brick; j++){

			std::shared_ptr<Convex_Polygon> brick = std::make_shared<Convex_Polygon>(Polygon{
				Point2DF{(float) screen_padding + j*(brick_width+brick_padding)              ,(float) brick_padding +  i*(10+2)     },
				Point2DF{(float) screen_padding + j*(brick_width+brick_padding) + brick_width,(float) brick_padding +  i*(10+2)     },
				Point2DF{(float) screen_padding + j*(brick_width+brick_padding) + brick_width,(float) brick_padding +  i*(10+2) + 10},
				Point2DF{(float) screen_padding + j*(brick_width+brick_padding)              ,(float) brick_padding +  i*(10+2) + 10}
			});


			brick->setBreakable(true,i);
			brick->setStatic(true);
			// on l'ajoute à l'engine physique
			physical_engine->addObject(brick);
			// on l'ajoute à l'engine graphique
			graphical_engine->addGraphicalPolygon(brick,"rsc/Breakout_Tile_Set_Free/PNG/0"+std::to_string(i+1)+"-Breakout-Tiles.png");
		}
		
	}

}


void GameEngine::handle_events(){

	static float v = 0;
	static float k = 1;
	constexpr float max_velocity = 30;

	SDL_Event event;
	Vector2DF speed({0,0});

	SDL_PollEvent(&event);
	switch(event.type){
		case SDL_USEREVENT:
			// quand un objet physique a été détruit
			// on incrémente le score
			// si c'est la barre qui a été détruite
			// on arrête le jeu

			// on met le jeu en pause
			if(phy_bar->getLife() <= 0){
				//window->print_text("Game Over");
				graphical_engine->print_text("Game Over");
				//stop();
				running = false;
				std::this_thread::sleep_for(std::chrono::seconds(2));
			}
			else{
				score++;
				debug("Score: " + score);
				//window->print_score(score);
				graphical_engine->print_text("Score: " + std::to_string(score));
			}

		break;
		case SDL_QUIT:
			//window->print_text("Fin du jeu");
			graphical_engine->print_text("Fin du jeu");
			running = false;
			//stop();
		break;
		case SDL_WINDOWEVENT:
		switch (event.window.event) {

			case SDL_WINDOWEVENT_CLOSE:   // exit game
				//window->print_text("Fin du jeu");
				graphical_engine->print_text("Fin du jeu");
				running = false;
				//stop();

			default:
				break;
		}
		break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
				case SDLK_SPACE:
					if(paused)
						graphical_engine->print_text("Appuyez sur Espace pour mettre en pause");
					else
						graphical_engine->print_text("Appuyez sur Espace pour relancer");
					paused = !paused;
				break;
					
				// on change la vitesse de la barre
				// pour laisser le moteur physique gérer le reste
				// La vélocité augmente linéairement : v(k) = k³+k²
				//  v(k+1) - v(k)/(k+1 - k) ~ v'(k) = 6k² + 2k
				//  d'ou v(k+1) = v(k) + 1/k
				case SDLK_LEFT:
					v = std::min(v+2*k*(3*k+1)+10, max_velocity);
					k++;
					//speed = phy_bar->getSpeed();
					speed[0] = - v;
					phy_bar->move(speed);
					debug("update bar speed : " + std::to_string(v));
				break;
				case SDLK_RIGHT:
					v = std::min(v + 2*k*(3*k+1)+10, max_velocity);
					k++;
					//augmenter la vélocité de la barre
					//speed = phy_bar->getSpeed();
					speed[0] = v;
					phy_bar->move(speed);
					debug("update bar speed : " + std::to_string(v));
				break;
				
				default:
				break;
			}
		break;
		// on arrête de bouger la barre
		case SDL_KEYUP:
			switch(event.key.keysym.sym){
				case SDLK_LEFT:
				case SDLK_RIGHT:
					v = 0;
				default:
				break;
			}
		break;

		default:
		break;
	}

}

void GameEngine::start(){

	running = true;

	// on lance les threads
	//graphical_engine_thread = std::thread(&Graphical_Engine::start, graphical_engine.get());
	//graphical_engine_thread = std::thread(&Graphical_Engine::start,graphical_engine.get());

	graphical_engine->print_text("Appuyez sur Espace pour commencer");
	while(running){
		handle_events();
		graphical_engine->draw();
		if(!paused)
			physical_engine->update();
		//SDL_Delay(1000/30); // 60 fps
	}
	debug("GameEngine::start() reach end of loop");
	stop();
	
}


void GameEngine::stop(){

	running = false;
	graphical_engine->print_text("Pause (Espace pour continuer) ~> Score: " + std::to_string(score));
	graphical_engine->stop();
	physical_engine->stop();

	debug("GameEngine::stop() wait threads ...");
	//physical_engine_thread.join();
	//graphical_engine_thread.join();

	debug("GameEngine::stop()");
	debug("Score: " + score);
	
	//sound_engine.stop();
}

