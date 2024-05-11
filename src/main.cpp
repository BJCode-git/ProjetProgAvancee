#include <iostream>

#include "Windows.hpp"
#include "Game_Engine.hpp"



int main(){
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	TTF_Init();
	GameEngine game;
	game.start();

	return 0;
}