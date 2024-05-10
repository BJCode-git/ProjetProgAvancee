#include "Game_Engine.hpp"

/*

class GameEngine{
	
	public:
		GameEngine();
		~GameEngine();

		void start() const;
		void stop() const;
	
	private:
		void init();
		void handle_events();
	
	private:

		unsigned int score;
		GraphicalPolygon graph_bar;
		Convex_Polygon phy_bar;
		Window w;


		std::unique_ptr<Window> window;
		std::unique_ptr<Graphical_Engine> graphical_engine;
		std::unique_ptr<Physical_Engine> physical_engine;
		//std::unique_ptr<Sound_Engine> sound_engine;

		std::thread graphical_engine_thread;
		std::thread physical_engine_thread;
		//std::thread sound_engine_thread;

};

*/

GameEngine::GameEngine(): 
	running(false),
	score(0),
	window(std::make_unique<Window>("Casse-briques Bro"),
			960,
			540),
	graphical_engine(window->get_renderer(),
					window->get_width(),
					window->get_height()),
	physical_engine(std::make_unique<Physical_Engine>())
{

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	
}

GameEngine::~GameEngine(){
	SDL_Quit();
}


void GameEngine::handle_events(){
	SDL_Event event;
	static bool pause = false;
	satic float v = 0;
	static float k = 1;
	const_expr max_velocity = 5;

	SDL_PollEvent(&event);
	switch(event.type){
		case SDL_USEREVENT:
			// quand un objet physique a été détruit
			// on incrémente le score
			// si c'est la barre qui a été détruite
			// on arrête le jeu

			// on met le jeu en pause
			if(phy_bar.getLife() <= 0){
				stop();
				window->print_text("Game Over");
				SDL_Delay(2000);
			}
			else{
				score++;
				print_score(score);
			}

		break;
		case SDL_QUIT:
			stop();
			window->print_text("Fin du jeu");
		break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym){
				case SDLK_ESCAPE:
					if(pause) start();
					else stop();
				
					pause = !pause;
					break;
				
				// on change la vitesse de la barre
				// pour laisser le moteur physique gérer le reste
				// La vélocité augmente logarithmiquement : v(k) = ln(k)
				//  v(k+1) - v(k)/(k+1 - k) ~ ln'(k) = 1/k
				//  d'ou v(k+1) = v(k) + 1/k
				case SDLK_LEFT:
					v = std::max(v+1/k, max_velocity);
					k++;
					Vector2DF speed = phy_bar.getSpeed();
					speed[0] = - v;
				break;
				case SDLK_RIGHT:
					v = std::max(v + 1/k, max_velocity);
					k++;
					//augmenter la vélocité de la barre
					Vector2DF speed = phy_bar.getSpeed();
					speed[0] = v;
				break;
				
				default:
				break;
			}
		break;
		// on arrête de bouger la barre
		case KEYUP:
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


void GameEngine::init(){
	// on va créer les objets graphiques et physiques
	// on va les lier

	// on va notamment créer la barre de jeu
	// ainsi que la balle
	// on donnera une vitesse initiale à la balle

	// creation de la barre
	// on la place en bas et au milieu de l'écran
	// on lui donne une taille de 10 pixels de haut et de 25 pixels de longs
	// rappelons que le haut est à y = 0 et le bas à y = 540, avec un padding de 5 pixels
	int width = window->get_width();
	int height = window->get_height();

	phy_bar = std::make_shared<Convex_Polygon>(Polygon{
		Point2DF(width/2 - 25, height - 15),
		Point2DF(width/2 + 25, height - 15),
		Point2DF(width/2 + 25, height - 5),
		Point2DF(width/2 - 25, height - 5)
	});

	phy_bar->setSpeed(Vector2DF(0,0));
	phy_bar->setBreakable(false);

	// on l'ajoute à l'engine physique
	physical_engine->add_object(phy_bar);
	// on l'ajoute à l'engine graphique
	graphical_engine.add_object(phy_bar);

	// on crée la balle
	// on la place au dessus de la barre
	std::shared_ptr<Circle> ball = std::make_shared<Circle>(Point2DF(width/2, height - 35), 5);

	// on lui défini une vitesse initiale
	// avec une composante horizontale aléatoire
	// et une composante verticale négative 2*supérieure à la gravité
	// pour qu'elle parte vers le haut
	ball->setSpeed(Vector2DF(rand()%10 - 5, -2*Gravity(*ball)));
	ball->setBreakable(false);

	// on l'ajoute à l'engine physique
	physical_engine.add_object(ball);
	// on l'ajoute à l'engine graphique
	graphical_engine.add_object(ball);


	// on crée les briques

	// on crée n_lines de 10 briques
	// on les place en haut de l'écran
	// on leur donne une taille de 20 pixels de large et 10 pixels de haut

	std::shared_ptr<Convex_Polygon> brick;
	int n_line = 3;

	for(int i = 0; i<n_line; i++){
		// on parcout la largeur de l'écran
		int n_brick = (width-10)/(2+20+2);
		// on place les briques à intervalle régulier
		for(int j=0;j<n_brick; j++){
			brick = std::make_shared<Convex_Polygon>(Polygon{
				Point2DF(5 + j*(20+2), 5 + i*(10+2)),
				Point2DF(5 + j*(20+2) + 20, 5 + i*(10+2)),
				Point2DF(5 + j*(20+2) + 20, 5 + i*(10+2) + 10),
				Point2DF(5 + j*(20+2), 5 + i*(10+2) + 10)
			});

			brick->setBreakable(true);
			brick->setLife(1);
			// on l'ajoute à l'engine physique
			physical_engine.add_object(brick);
			// on l'ajoute à l'engine graphique
			graphical_engine.add_object(brick);
		}
		
	}

}


void GameEngine::start(){

	running = true;
	// on lance les threads
	graphical_engine_thread = std::thread(&Graphical_Engine::run, &graphical_engine);
	physical_engine_thread  = std::thread(&Physical_Engine::run, &physical_engine);

	while(running){
		handle_events();
	}

	physical_engine_thread.join();
	graphical_engine_thread.join();
	
}


void GameEngine::stop() const{
	running = false;

	graphical_engine.stop();
	physical_engine.stop();
	//sound_engine.stop();
}


#endif // GAME_ENGINE_HPP