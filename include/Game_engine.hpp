#ifndef GAME_ENGINE_HPP

#include <memory>
#include <thread>


#include "windows.hpp"
#include "Graphical_Engine.hpp"
#include "Physical_Engine/Physical_Engine.hpp"
//#include "Sound_Engine.hpp"




class Game_engine{
	
	public:
		Game_engine();
		~Game_engine();

		void start() const;
		void stop() const;

		void handle_events();
	
	private:
		unsigned int score;

		std::unique_ptr<Window> window;
		std::unique_ptr<Graphical_Engine> graphical_engine;
		std::unique_ptr<Physical_Engine> physical_engine;
		//std::unique_ptr<Sound_Engine> sound_engine;

		std::thread graphical_engine_thread;
		std::thread physical_engine_thread;
		//std::thread sound_engine_thread;
};



#endif // GAME_ENGINE_HPP