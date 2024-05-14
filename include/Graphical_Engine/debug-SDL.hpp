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

	#ifdef DEBUG
	#define SDL_DestroyWindow(window) Debug_SDL_DestroyWindow(window)
	#define SDL_DestroyRenderer(renderer) Debug_SDL_DestroyRenderer(renderer)
	#define SDL_DestroyTexture(texture) Debug_SDL_DestroyTexture(texture)
	#define SDL_FreeSurface(surface) Debug_SDL_FreeSurface(surface)
	#define TTF_CloseFont(font) Debug_TTF_CloseFont(font)
	#endif

#endif
