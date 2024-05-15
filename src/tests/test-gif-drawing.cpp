#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Window* window;
SDL_Renderer* renderer;



int main() {

  int width = 1000;
  int height = 300;
  
  window = SDL_CreateWindow("Test SDL2", 
                            SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED, 
                            width, height, 
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  SDL_Init(SDL_INIT_VIDEO);


  IMG_Animation *animation = IMG_LoadAnimation("rsc/Itachi_rain.gif");
	int n = 0;
	if (animation == nullptr) {
		std::cerr << "IMG_LoadAnimated Error: " << IMG_GetError() << std::endl;
    exit(1);
	}	
	
  SDL_Event *event =nullptr;
  bool resized = false;

  while (!SDL_QuitRequested()) {
    SDL_PollEvent(event);
    switch (event->type) {
      case SDL_WINDOWEVENT_RESIZED:
      case SDL_WINDOWEVENT_SIZE_CHANGED:
          resized = true;
          break;
      default:
        break;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, animation->frames[n]);
		if (texture == nullptr) {
			std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		} 
    else {
			
			SDL_FRect dstRect = {0, 
                           0, 
                           static_cast<float> (width), 
                           static_cast<float> (height)};
      SDL_SetRenderTarget(renderer, texture);
			SDL_RenderCopyF(renderer, texture, nullptr, &dstRect);
      SDL_DestroyTexture(texture);
		
		}

		n = (n + 1) % animation->count;
  
    if(resized) {
      // on adapte l'image à la taille de la fenêtre
      SDL_GetWindowSize(window, &width, &height);
      SDL_RenderSetLogicalSize(renderer, width, height);
      resized = false;
      
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(100);

  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}