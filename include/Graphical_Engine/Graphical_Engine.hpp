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

/**
 * @class Graphical_Engine
 * @brief The Graphical_Engine class represents a graphical engine for rendering objects on the screen.
 * 
 * The Graphical_Engine class provides functionality for managing the rendering of graphical objects,
 * such as polygons and circles, on a window. It uses SDL library for rendering and supports features
 * like setting the renderer, starting and stopping the engine, printing text, drawing objects, adding
 * and removing objects, setting the FPS limit, and more.
 */
/**
 * @class Graphical_Engine
 * @brief The Graphical_Engine class represents a graphical engine for rendering objects on the screen.
 * 
 * The Graphical_Engine class provides functionality to start and stop the engine, set the renderer,
 * print text on the screen, draw objects, add and remove objects, set the FPS limit, set the window size,
 * set the background image, and more.
 */
class Graphical_Engine{

	public:
		
		/**
		 * @brief Graphical_Engine constructor.
		 * @param scene_width The width of the scene.
		 * @param scene_height The height of the scene.
		 * @param fps_limit The FPS render limit of the engine.
		 */
		Graphical_Engine(int scene_width,
						 int scene_height,
						 uint16_t fps_limit = 60);
		~Graphical_Engine();

		//void setRenderer(std::shared_ptr<SDL_Renderer> renderer);
		/*
		* @brief Returns the SDL_Renderer object of the engine.
		* @return The SDL_Renderer object of the engine.
		*/
		std::shared_ptr<SDL_Renderer> getRenderer() const;

		/**
		 * @brief Starts the graphical engine.
		 */
		void start();
		/**
		 * @brief Stops the graphical engine.
		 */
		void stop();

		//void  operator()(){start();}
		//enum Text_Align{
		//	LEFT   = 0b000001,
		//	CENTER = 0b000010,
		//	RIGHT  = 0b000100,
		//	TOP    = 0b001000,
		//	MIDDLE = 0b010000,
		//	BOTTOM = 0b100000
		//};

		/**
		 * @brief Prints text on the screen.
		 * @param text The text to print.
		 * @param position The position to print the text at.
		 */
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