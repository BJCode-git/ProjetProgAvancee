#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Physical_Engine/Physical_Engine.hpp"
#include "debug.hpp"


void init(std::shared_ptr<Physical_Engine> physical_engine, float width, float height){


	// on crée la balle
	// on la place au dessus de la barre
	std::shared_ptr<Circle> ball = std::make_shared<Circle>(Point2DF{width/2, height - 35}, 5);
	ball->setBreakable(false,1);

	// on lui défini une vitesse initiale
	// avec une composante horizontale aléatoire
	// et une composante verticale négative 2*supérieure à la gravité
	// pour qu'elle parte vers le haut
	ball->setSpeed(Vector2DF{ static_cast<float> (std::rand()%10 - 5), -2.f*10.f});
	ball->setBreakable(false);

	// on l'ajoute à l'engine physique
	physical_engine->addObject(ball);

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
		}
	}
}

int main(void){

	SDL_InitSubSystem(SDL_INIT_EVENTS);

	float width = 960, height = 540;

	std::shared_ptr<Physical_Engine> engine = std::make_shared<Physical_Engine>( 960,540);

	// on crée la barre
	std::shared_ptr<Convex_Polygon> phy_bar = std::make_shared<Convex_Polygon>(Polygon{
		Point2DF{width/2 - 25, height - 15},
		Point2DF{width/2 + 25, height - 15},
		Point2DF{width/2 + 25, height -  5},
		Point2DF{width/2 - 25, height -  5}
	});

	phy_bar->setSpeed(Vector2DF{0,0});
	phy_bar->setBreakable(false);

	// on l'ajoute à l'engine physique
	engine->addObject(phy_bar);

	init(engine, width, height);

	int score = 0;
	bool running = true;
	while(running){
		SDL_Event event;
		SDL_PollEvent(&event);
		switch(event.type){
			case SDL_USEREVENT:
				if(phy_bar->getLife() <= 0){
					engine->stop();
					std::cout<<"Game Over"<<std::endl;
					running = false;
				}
				else
					std::cout<<"Score: " <<score++<<std::endl;
			break;

			case SDL_QUIT:
				//window->print_text("Fin du jeu");
				engine->stop();
				std::cout<<"Fin du jeu";
				running = false;

			break;

			default:
			break;
		}

		engine->update();
		SDL_Delay(100);
	}

	SDL_Quit();


	return EXIT_SUCCESS;
}