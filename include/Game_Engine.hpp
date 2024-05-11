#ifndef GAME_ENGINE_HPP

#include <iostream>
#include <cstdlib>
#include <memory>
#include <thread>
#include <future>


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Physical_Engine/Physical_Engine.hpp"
#include "Graphical_Engine/Graphical_Engine.hpp"
#include "debug.hpp"

//#include "Sound_Engine.hpp"


class GameEngine{
	
	public:
		GameEngine(int width = 960, int height = 540);
		~GameEngine();

		void start();
		void stop();
	
	private:
		void init();
		void handle_events();
	
	private:
		bool running;
		int score;
		std::shared_ptr<Convex_Polygon> phy_bar;

		//std::unique_ptr<Window> window;
		std::unique_ptr<Graphical_Engine> graphical_engine;
		std::unique_ptr<Physical_Engine> physical_engine;
		std::unique_ptr<Mix_Music,void (*)(Mix_Music*)> music;
		//std::unique_ptr<Sound_Engine> sound_engine;

		std::thread graphical_engine_thread;
		std::thread physical_engine_thread;
		//std::thread sound_engine_thread;

		

};



#endif // GAME_ENGINE_HPP