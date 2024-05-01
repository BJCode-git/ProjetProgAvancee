#ifndef WINDOWS_HPP
#define WINDOWS_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include <vector>
#include <string>

#include "Graphical_Engine.hpp"

/*
Directives du projet : 
L’évaluation prendra en compte le contenu, mais surtout la modernité, la propreté, et
l’organisation du code.
Vous respecterez les critères suivants:
- Utilisez la STL au maximum.
- Pas de tableau! des conteneurs STL.
- Pas de pointeur! des unique/shared/weak_ptr.
- Utilisez les algorithmes de la STL
- Ecrivez des classes pour vos objets et encapsulez la SDL2.
- Utilisez les possibilités du C++ 11/14/17/20/etc… (Lamdba, for range).
- Utilisez de l’héritage et du polymorphisme.
- Soyez const-correct et efficaces, pas de copie inutile!
- Documentez votre code.
- Utilisez une convention de codage.

*/

// SDL_Init(SDL_INIT_EVERYTHING); et SDL_Quit(); gérer par le moteur de jeu

class Window{

	public:
		Window(cons title, int x, int y, int w, int h, Uint32 flags);
		~Window();
		
		void update();
		void clean();

	private:

		void draw();
		void init();
		void handleEvents();
		
	private:

		std::shared_ptr<SDL_Window>   window;
		std::shared_ptr<SDL_Renderer> renderer;
		std::shared_ptr<SDL_Texture>  texture;
		std::shared_ptr<SDL_Surface>  surface;

};

#endif // WINDOWS_HPP