#ifndef DEBUG_SDL_HPP
#define DEBUG_SDL_HPP

	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
	#include <iostream>

	void Debug_SDL_DestroyWindow(SDL_Window * window);
	void Debug_SDL_DestroyRenderer(SDL_Renderer * renderer);
	void Debug_SDL_DestroyTexture(SDL_Texture * texture);
	void Debug_SDL_FreeSurface(SDL_Surface * surface);
	void Debug_TTF_CloseFont(TTF_Font * font);
	


#endif
