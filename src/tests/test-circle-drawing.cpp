#include <SDL2/SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;


void drawFilledCircle(SDL_Renderer* renderer, float x, float y, float radius) {
    float dx = radius - 1;
    float dy = 0;
    float err = 1 - dx;

    while (dx >= dy) {
        SDL_RenderDrawLineF(renderer, x - dx, y + dy, x + dx, y + dy);
        SDL_RenderDrawLineF(renderer, x - dx, y - dy, x + dx, y - dy);
        SDL_RenderDrawLineF(renderer, x - dy, y + dx, x + dy, y + dx);
        SDL_RenderDrawLineF(renderer, x - dy, y - dx, x + dy, y - dx);

        dy++;
        if (err < 0) {
            err += 2 * dy + 1;
        } else {
            dx--;
            err += 2 * (dy - dx) + 1;
        }
    }
}

void drawCircle(SDL_Renderer* renderer, float x, float y, float radius) {
    int dx = radius - 1;
    int dy = 0;
    int err = 1 - dx;

    while (dx >= dy) {
        SDL_RenderDrawPointF(renderer, x + dx, y + dy);
        SDL_RenderDrawPointF(renderer, x - dx, y + dy);
        SDL_RenderDrawPointF(renderer, x + dx, y - dy);
        SDL_RenderDrawPointF(renderer, x - dx, y - dy);
        SDL_RenderDrawPointF(renderer, x + dy, y + dx);
        SDL_RenderDrawPointF(renderer, x - dy, y + dx);
        SDL_RenderDrawPointF(renderer, x + dy, y - dx);
        SDL_RenderDrawPointF(renderer, x - dy, y - dx);

        dy++;
        if (err < 0) {
            err += 2 * dy + 1;
        } else {
            dx--;
            err += 2 * (dy - dx) + 1;
        }
    }
}


int main() {
  int width = 900;
  int height = 300;
  int nbCircles = 100;
  float radius = ((float)width) / ((float) (2*(nbCircles+1) ) );
  
  window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height, 0);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

  while (!SDL_QuitRequested()) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 255, 255, SDL_ALPHA_OPAQUE);
    // dessine 100 petits cercles alignés
 
    for (int i = 0; i < nbCircles; i++) {
      drawCircle(renderer, i *2*radius + radius, 100, radius);
    }

    for (int i = 0; i < nbCircles; i++) {
      drawFilledCircle(renderer, i *2*radius + radius, 100 + 2*radius , radius);
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(1000);
  }

  SDL_DestroyWindow(window);
  return 0;
}