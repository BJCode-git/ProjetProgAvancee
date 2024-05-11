#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>

std::unique_ptr<SDL_Window,void (*)(SDL_Window*)> window(nullptr,SDL_DestroyWindow);
std::shared_ptr<SDL_Renderer> renderer,render;



int main() {

  int width = 1000;
  int height = 300;
  int nbImg = 100;
  
  window = std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>
			   (SDL_CreateWindow("Test SDL2", 
                            SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED, 
                            width, height, 
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE),
			   SDL_DestroyWindow); 
          
  renderer = std::shared_ptr<SDL_Renderer> (SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_PRESENTVSYNC),SDL_DestroyRenderer);
  render = renderer;
  SDL_Init(SDL_INIT_VIDEO);


  IMG_Animation *animation = IMG_LoadAnimation("rsc/Itachi_rain.gif");
	int n = 0;
	if (animation == nullptr) {
		std::cerr << "IMG_LoadAnimated Error: " << IMG_GetError() << std::endl;
    exit(1);
	}	
	
  SDL_Event *event;
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

    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_SetRenderDrawColor(render.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(render.get());
    SDL_RenderClear(renderer.get());

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer.get(), animation->frames[n]);
		if (texture == nullptr) {
			std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		} 
    else {
			
			SDL_FRect dstRect = {0.f, 0.f,static_cast<float> (width), static_cast<float> (height)};
      SDL_FRect dstRect2 = {static_cast<float> (width)/4, static_cast<float> (height)/4, static_cast<float> (width)/2, static_cast<float> (height)/2};
			SDL_RenderCopyF(renderer.get(), texture, nullptr, &dstRect);
      SDL_RenderCopyF(render.get(), texture, nullptr, &dstRect2);
      SDL_DestroyTexture(texture);
		
		}

		n = (n + 1) % animation->count;
  
    if(resized) {
      // on adapte l'image à la taille de la fenêtre
      SDL_GetWindowSize(window.get(), &width, &height);
      SDL_RenderSetLogicalSize(renderer.get(), width, height);
      resized = false;
      
    }

    SDL_RenderPresent(renderer.get());
    SDL_RenderPresent(render.get());
    SDL_Delay(100);

  }


  SDL_Quit();
  return 0;
}