#ifndef PHYSICAL_ENGINE_HPP
#define PHYSICAL_ENGINE_HPP

#include <iostream>    // Pour std::cout, std::endl, etc...
#include <cmath>       // Pour std::sqrt, std::abs, etc...
#include <limits>      // Pour std::numeric_limits
#include <type_traits> // Pour std::enable_if_t, std::is_convertible_v, etc.
#include <memory>     // Pour std::shared_ptr, etc...
#include <vector>     // Pour std::vector
#include <array>      // Pour std::array
#include <list>       // Pour std::list
#include <map>        // Pour std::map
#include <utility>    // Pour std::pair, std::make_pair, etc...
#include <algorithm>  // Pour std::min, std::max, find,sort, etc...


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
class PhysicalEngine{
	public:
		PhysicalEngine();
		~PhysicalEngine();

		void addObject(std::shared_ptr<Physical_Object>);
		void removeObject(std::shared_ptr<Physical_Object>);
		void clearObjects();

		void start();
		void stop();

		void update();

		const std::vector<std::shared_ptr<Physical_Object>> & getObjects() const;

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

		// détecte les collisions entre les objets physiques
		// On suppose qu'à l'état initial, les objets physiques ne se chevauchent pas
		void detectCollisions();

		void resolveCollisions();

};

#endif // PHYSICAL_ENGINE_HPP