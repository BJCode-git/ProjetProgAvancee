#include "Windows.hpp"

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

Window::Window(const std::string title, int x, int y, int w, int h, Uint32 flags):
	width(w),
	height(h)
{
	i(TTF_Init() == -1){
		std::cerr << "Error: " << TTF_GetError() << std::endl;
		throw std::runtime_error("Error: " + std::string(TTF_GetError()));
	}


	window = std::unique_ptr<SDL_Window*>(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED, w, h, flags));
	renderer = std::shared_ptr<SDL_Renderer*>(SDL_CreateRenderer(*window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED));

	font = std::unique_ptr<TTF_Font>( TTF_OpenFont("rsc/mario.ttf", 10));


	if(font == nullptr){
		std::cerr << "Error: " << TTF_GetError() << std::endl;
	}

}

Window::~Window(){
	TTF_CloseFont(*font);
	TTF_Quit();
	SDL_DestroyTexture(*renderer);
	SDL_DestroyWindow(*window);
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

void Window::print_score(int score){

	std::cout << "Score: " << score << std::endl;

	SDL_Color color = {255, 255, 255, 0};

	SDL_Surface* surface = TTF_RenderText_Solid(*font, std::to_string(score).c_str(), color);
	if(surface == nullptr){
		std::cerr << "Error: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Texture texture = SDL_CreateTextureFromSurface(*renderer, surface);
	if(texture == nullptr){
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		return;
	}
	SDL_FreeSurface(surface);

	// On va afficher le en haut à gauche de la fenêtre
	SDL_Rect TextRect;
	TextRect.x = 0;
	TextRect.y = 0;
	TextRect.w = surface->w;
	TextRect.h = surface->h;
	SDL_RenderCopy(*renderer, *texture, NULL, &TextRect);
}

void Window::print_text(const std::string text){

	std::cout << text << std::endl;

	SDL_Color color = {255, 255, 255, 0};

	SDL_Surface* surface = TTF_RenderText_Solid(*font, text.c_str(), color);
	if(surface == nullptr){
		std::cerr << "Error: " << TTF_GetError() << std::endl;
		return;
	}

	SDL_Texture texture = SDL_CreateTextureFromSurface(*renderer, surface);
	if(texture == nullptr){
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_FreeSurface(surface);

	// On va afficher le au centre de la fenêtre
	SDL_Rect TextRect;
	TextRect.x = width / 2 - surface->w / 2;
	TextRect.y = height / 2 - surface->h / 2;
	TextRect.w = surface->w;
	TextRect.h = surface->h;
	SDL_RenderCopy(*renderer, *texture, NULL, &TextRect);
}
