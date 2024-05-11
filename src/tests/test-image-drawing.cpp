#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Window* window;
SDL_Renderer* renderer;



int main() {

  int width = 1000;
  int height = 300;
  int nbImg = 100;
  
  window = SDL_CreateWindow("Test SDL2", 
                            SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED, 
                            width, height, 
                            SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);


  SDL_Surface* image = IMG_Load("rsc/galifeu.png");
  SDL_Texture* texture = nullptr;

  if(!image){
    printf("Erreur de chargement de l'image : %s \n",SDL_GetError());
  }
  else{
    printf("Image chargée\n");
    texture = SDL_CreateTextureFromSurface( renderer, image );
    SDL_FreeSurface(image);
       if( !texture )
        printf("Erreur de création de la texture : %s \n",SDL_GetError());
  }

  image = nullptr;

  while (!SDL_QuitRequested()) {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // SDL_Rect (x, y, w, h)
    SDL_Rect dest = {0, 0, 32, 32};

    // dessine 100 petits cercles alignés
 
    for (int i = 0; i < nbImg && dest.y+32< height; i++){
      
      for (int x  = 0; x+32 < width; x+=32){
        dest.x = x;
        SDL_SetRenderDrawColor(renderer, (i*5)%255, (i*25)%255, (i*10)%216 +40, SDL_ALPHA_OPAQUE);
        if (texture)
          SDL_RenderCopy(renderer, texture, NULL, &dest);
        
        SDL_FRect r = {dest.x, dest.y, 32, 32};
        SDL_RenderDrawRectF(renderer, &r);
    
      }

      dest.y += 32;

    }

    SDL_RenderPresent(renderer);
    SDL_Delay(1000);

  }

  SDL_DestroyWindow(window);
  return 0;
}