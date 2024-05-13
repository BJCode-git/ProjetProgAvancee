#ifndef WINDOWS_HPP
#define WINDOWS_HPP

#include <iostream>
#include <memory>
#include <string>

#include <SDL2/SDL.h>
//#include <SDL2/SDL_ttf.h>

#include "debug.hpp"

class Window{
	public:
		Window(const std::string title, int w = 960, int h = 540, Uint32 flags = SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
		~Window();

		std::shared_ptr<SDL_Renderer> get_renderer() const;
		int get_width() const;
		int get_height() const;

		//void print_score(int score);
		//void print_text(const std::string text);

	private:
		int width;
		int height;

		//std::unique_ptr<TTF_Font   , void (*)(TTF_Font*)>    font;
		std::unique_ptr<SDL_Window ,decltype(&SDL_DestroyWindow)>   window;
		std::shared_ptr<SDL_Renderer> renderer;
		

};

#endif // WINDOWS_HPP