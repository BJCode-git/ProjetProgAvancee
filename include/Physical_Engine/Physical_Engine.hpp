#ifndef PHYSICAL_ENGINE_HPP
#define PHYSICAL_ENGINE_HPP

#include <iostream>    // Pour std::cout, std::endl, etc...
#include <cmath>       // Pour std::sqrt, std::abs, etc...
#include <limits>      // Pour std::numeric_limits
#include <type_traits> // Pour std::enable_if_t, std::is_convertible_v, etc.
#include <memory>      // Pour std::shared_ptr, etc...
#include <vector>      // Pour std::vector
#include <array>       // Pour std::array
#include <list>        // Pour std::list
#include <map>         // Pour std::map
#include <utility>     // Pour std::pair, std::make_pair, etc...
#include <algorithm>   // Pour std::min, std::max, find,sort, etc...

#include <thread>
#include <chrono>

#include <SDL2/SDL.h>   // Pour event


#include "Physical_Engine/NumericVector.hpp"
#include "Physical_Engine/Physical_Object/Physical_Object.hpp"
#include "Physical_Engine/Convex_Polygon/Convex_Polygon.hpp"
#include "Physical_Engine/Circle/Circle.hpp"


struct Scene{
	int width;
	int height;
};

// Classe pour le moteur physique
// On fait très simple pour l'instant
// Pas de Phase large, Phase étroite directement
class Physical_Engine{
	public:
		Physical_Engine(int width = 960, int height = 540);
		~Physical_Engine();

		void addObject(std::shared_ptr<Physical_Object>);
		void removeObject(std::shared_ptr<Physical_Object>);
		void clearObjects();

		void setScene(int width, int height);

		//void operator()(){start();}

		void start();
		void stop();
		bool isRunning() const{ return running;}

		void update(float dt=1);

		const std::vector<std::shared_ptr<Physical_Object>> & getObjects() const;

	private:
		// envoie un événement de destruction d'un objet physique
		// au moteur de jeu
		void sendDestructEvent();

		void removeDeadObjects();

		// détecte les collisions entre les objets physiques
		// On suppose qu'à l'état initial, les objets physiques ne se chevauchent pas
		void detectCollisions();

		void resolveCollisions(float dt);

	private:
		bool running;
		Scene scene;
		
		struct Collision{
			std::shared_ptr<Physical_Object> obj2;
			Vector2DF intersection_point;
			Vector2DF normal;
		};

		std::vector<std::shared_ptr<Physical_Object>> objects;
		std::map<std::shared_ptr<Physical_Object>, std::list<Collision>> collisions;



};

#endif // PHYSICAL_ENGINE_HPP