#ifndef GRAPHICAL_ENGINE_HPP
#define GRAPHICAL_ENGINE_HPP

#include <iostream>
#include <memory>
#include <chrono>
#include <ctime>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "debug.hpp"
#include "Physical_Engine/Physical_Engine.hpp"
#include "Graphical_Engine/Graphical_Object/Graphical_Object.hpp"
#include "Graphical_Engine/Graphical_Circle/Graphical_Circle.hpp"
#include "Graphical_Engine/Graphical_Polygon/Graphical_Polygon.hpp"
#include "Graphical_Engine/Window/Window.hpp"
#include "Graphical_Engine/debug-SDL.hpp"

class Graphical_Engine{

	public:

		/*Graphical_Engine(std::shared_ptr<SDL_Renderer> renderer, 
						int scene_width,
						int scene_height,
						uint16_t fps_limit = 60);*/
		Graphical_Engine(int scene_width,
						 int scene_height,
						 uint16_t fps_limit = 60);
		~Graphical_Engine();

		//void setRenderer(std::shared_ptr<SDL_Renderer> renderer);
		std::shared_ptr<SDL_Renderer> getRenderer() const;

		void start();
		void stop();

		//void  operator()(){start();}

		void print_text(const std::string text);

		void draw();
		void clear();

		void addObject(std::shared_ptr<Convex_Polygon> object,
					  std::string texture_path = "");

		void addObject(std::shared_ptr<Circle> object,
					   std::string texture_path = "");

		void addGraphicalPolygon(std::shared_ptr<Convex_Polygon> PhyObject,
								 std::string texture_path = "");
		void addGraphicalCircle(std::shared_ptr<Circle> PhyObject,
								std::string texture_path = "");
		void removeObject(size_t index);

		void setFPSLimit(uint16_t fps_limit);
		int getFPSLimit() const;


		//void setWindowSize(int width, int height);
		int get_win_width() const{return window->get_width(); };
		int get_win_height() const{return window->get_height();};

		void set_background(std::string filepath, bool animated = false);

	private:
		void draw_text();
		void draw_background();

	private:
		bool is_text_to_draw;

		std::pair<std::string,Vector2DF> text_to_print;
		std::unique_ptr<IMG_Animation,decltype(&IMG_FreeAnimation)> animated_background;
		std::unique_ptr<SDL_Texture,decltype(&SDL_DestroyTexture)>  static_background;
		std::vector<std::unique_ptr<Graphical_Object>> objects;
		std::map<std::string, std::shared_ptr<SDL_Texture>> textures;

		std::unique_ptr<Window> window;
		std::shared_ptr<SDL_Renderer> renderer;
		std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>    font;
		

		int fps_limit;
		//int window_width;
		//int window_height;

		bool running;
};


#endif // GRAPHICAL_ENGINE_HPP