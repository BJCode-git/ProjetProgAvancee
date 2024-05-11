#include "Graphical_Engine/Window/Window.hpp"

/*

class Window{
	public:
		Window(const std::string title, int w = 960, int h = 540, Uint32 flags = SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS);
		~Window();

		shared_ptr<SDL_Renderer*> get_renderer() const;
		int get_width() const;
		int get_height() const;

		void print_score(int score);
		void print_text(const std::string text);

	private:
		int width;
		int height;

		std::unique_ptr<SDL_Window*>   window;
		std::shared_ptr<SDL_Renderer*> renderer;

		std::unique_ptr<SDL_Texture*> texture, text;
		std::unique_ptr<TTF_Font*>    font;

};


*/



Window::Window(const std::string title, int w, int h, Uint32 flags):
	width(w),
	height(h),
	//font(nullptr,TTF_CloseFont),
	window(nullptr,SDL_DestroyWindow),
	renderer(nullptr, SDL_DestroyRenderer)
{

	window = std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>
				(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, w, h, flags),
				 SDL_DestroyWindow);
	
	 renderer = std::shared_ptr<SDL_Renderer> (SDL_CreateRenderer(window.get(),
												-1, 
												SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE),
												SDL_DestroyRenderer);
	/*
	if (window.get() == nullptr || renderer.get() == nullptr || font.get() == nullptr){
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		std::cerr << "Error: " << TTF_GetError() << std::endl;
		exit(1);
	}*/

	if (window.get() == nullptr || renderer.get() == nullptr){
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	//renderer = std::shared_ptr<SDL_Renderer>(
	//				SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE),
	//				SDL_DestroyRenderer);

}

Window::~Window(){
	//TTF_CloseFont(font.get());
	//TTF_Quit();
	SDL_DestroyRenderer(renderer.get());
	SDL_DestroyWindow(window.get());
}

std::shared_ptr<SDL_Renderer> Window::get_renderer() const{
	return renderer;
}

int Window::get_width() const{
	return width;
}

int Window::get_height() const{
	return height;
}
/*
void Window::print_score(int score){

	debug("Score: " + score);
	SDL_RenderClear(renderer.get());

	SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE};

	SDL_Surface *surface = TTF_RenderText_Solid(font.get(), std::to_string(score).c_str(), color);
	if(surface == nullptr){
		std::cerr << "Error: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
	if(texture == nullptr){
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_FreeSurface(surface);

	// On va afficher le en haut à gauche de la fenêtre
	SDL_FRect TextRect;
	TextRect.x = static_cast<float> (0);
	TextRect.y = static_cast<float> (0);
	TextRect.w = static_cast<float> (surface->w);
	TextRect.h = static_cast<float> (surface->h);
	SDL_RenderCopyF(renderer.get(), texture, NULL, &TextRect);
}

void Window::print_text(const std::string text){

	debug(text);
	SDL_RenderClear(renderer.get());

	SDL_Color color = {255, 255, 255, SDL_ALPHA_OPAQUE};

	SDL_Surface *surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
	if(surface == nullptr){
		std::cerr << "Error: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
	if(texture == nullptr){
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_FreeSurface(surface);

	// On va afficher le au centre de la fenêtre
	SDL_FRect TextRect;
	TextRect.x = static_cast<float> (width  / 2 - surface->w / 2);
	TextRect.y = static_cast<float> (height / 2 - surface->h / 2);
	TextRect.w = static_cast<float> (surface->w);
	TextRect.h = static_cast<float> (surface->h);
	SDL_RenderCopyF(renderer.get(), texture, NULL, &TextRect);
	SDL_RenderPresent(renderer.get());
}
*/
