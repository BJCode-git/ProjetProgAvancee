#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Physical_Engine/Physical_Engine.hpp"
#include "Graphical_Engine/Graphical_Engine.hpp"
#include "debug.hpp"




void init(std::shared_ptr<Physical_Engine> physical_engine,std::shared_ptr<Graphical_Engine> graphical_engine){


	// on crée les objets physiques et graphiques

	float width = graphical_engine->get_win_width();
	float height = graphical_engine->get_win_height();



	// on crée la balle
	// on la place au dessus de la barre
	std::shared_ptr<Circle> ball = std::make_shared<Circle>(Point2DF{width/2, height - 35}, 10);

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


			brick->setBreakable(true,1);
			// on l'ajoute à l'engine physique
			physical_engine->addObject(brick);
			// on l'ajoute à l'engine graphique
			graphical_engine->addGraphicalPolygon(brick,"rsc/Breakout_Tile_Set_Free/PNG/0"+std::to_string(i+1)+"-Breakout-Tiles.png");
		}
	}

	// On ajoute différents cercles pour tester l'affichage

	// on crée un gros cercle

	std::shared_ptr<Circle> circle = std::make_shared<Circle>(Point2DF{width/2, height/2}, 50);
	// on l'ajoute à l'engine physique
	physical_engine->addObject(circle);
	// on l'ajoute à l'engine graphique
	graphical_engine->addGraphicalCircle(circle,"rsc/Breakout_Tile_Set_Free/PNG/58-Breakout-Tiles.png");

}

int main(){
	SDL_Init(SDL_INIT_VIDEO);

	float width = 960, height = 540;

	std::shared_ptr<Physical_Engine> physical_engine = std::make_shared<Physical_Engine>   (width, height);
	std::shared_ptr<Graphical_Engine> graphical_engine = std::make_shared<Graphical_Engine>(width, height);


	// on crée la barre
	auto phy_bar = std::make_shared<Convex_Polygon>(Polygon{
		Point2DF{width/2 - 25, height - 15},
		Point2DF{width/2 + 25, height - 15},
		Point2DF{width/2 + 25, height -  5},
		Point2DF{width/2 - 25, height -  5}
	});

	phy_bar->setSpeed(Vector2DF{0,0});
	phy_bar->setBreakable(false);

	// on l'ajoute à l'engine physique
	physical_engine->addObject(phy_bar);
	// on l'ajoute à l'engine graphique
	graphical_engine->addGraphicalPolygon(phy_bar,"rsc/Breakout_Tile_Set_Free/PNG/47-Breakout-Tiles.png");
	
	init(physical_engine, graphical_engine);



	bool running = true;
	float v = 0;
	float k = 1;
	int score = 0;
	constexpr float max_velocity = 5;

	SDL_Event event;
	Vector2DF speed;

	

	graphical_engine->print_text("Score: 0");
	while(running){
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

					// on change la vitesse de la barre
					// pour laisser le moteur physique gérer le reste
					// La vélocité augmente logarithmiquement : v(k) = ln(k)
					//  v(k+1) - v(k)/(k+1 - k) ~ ln'(k) = 1/k
					//  d'ou v(k+1) = v(k) + 1/k
					case SDLK_LEFT:
						v = std::min(v+1/k, max_velocity);
						k++;
						speed = phy_bar->getSpeed();
						speed[0] = - v;
						phy_bar->setSpeed(speed);
						debug("update bar speed : " + std::to_string(v));
					break;
					case SDLK_RIGHT:
						v = std::min(v + 1/k, max_velocity);
						k++;
						//augmenter la vélocité de la barre
						speed = phy_bar->getSpeed();
						speed[0] = v;
						phy_bar->setSpeed(speed);
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

		graphical_engine->draw();
		phy_bar->update();
		SDL_Delay(1000/60);

	}


	SDL_Quit();
}