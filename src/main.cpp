#include <iostream>

#include "Windows.hpp"
#include "Game_Engine.hpp"



int main(){
	Window w("Casse-briques Bro", 960, 540);
	GameEngine game;
	game.start();

	return 0;
}