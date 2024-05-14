#include "Graphical_Engine/debug-SDL.hpp"
	
	void Debug_SDL_DestroyWindow(SDL_Window * window){
		if(window == nullptr){
			std::cerr << "Window already destroyed" << std::endl;
			return;
		}
		std::cerr << "Window destroyed "<< window << std::endl;
		SDL_DestroyWindow(window);
	}

	void Debug_SDL_DestroyRenderer(SDL_Renderer * renderer){
		if(renderer == nullptr){
			std::cerr << "Renderer already destroyed" << std::endl;
			return;
		}
		std::cerr << "Renderer destroyed "<< renderer << std::endl;
		SDL_DestroyRenderer(renderer);
	}

	void Debug_SDL_DestroyTexture(SDL_Texture * texture){
		if(texture == nullptr){
			std::cerr << "Texture already destroyed" << std::endl;
			return;
		}
		std::cerr << "Texture destroyed "<< texture << std::endl;
		SDL_DestroyTexture(texture);
	}

	void Debug_SDL_FreeSurface(SDL_Surface * surface){
		if(surface == nullptr){
			std::cerr << "Surface already freed" << std::endl;
			return;
		}
		std::cerr << "Surface freed "<< surface << std::endl;
		SDL_FreeSurface(surface);
	}

	void Debug_TTF_CloseFont(TTF_Font * font){
		if(font == nullptr){
			std::cerr << "Font already freed" << std::endl;
			return;
		}
		std::cerr << "Font freed "<< font << std::endl;
		TTF_CloseFont(font);
	}


