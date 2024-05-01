#include "Physical_Engine/Physical_Engine.hpp"


/******************
 * PhysicalEngine *
 ******************/


PhysicalEngine::PhysicalEngine():
	objects(),
	collisions(),
	running(false)
{
	debug("Création d'un moteur physique");
}

PhysicalEngine::~PhysicalEngine(){
	debug("Destruction d'un moteur physique");
}

void PhysicalEngine::addObject(std::shared_ptr<Physical_Object>   obj){
	objects.push_back(obj);
}

void PhysicalEngine::removeObject(std::shared_ptr<Physical_Object> obj){
	auto it = std::find(objects.begin(), objects.end(), obj);
	if (it != objects.end()) objects.erase(it);
}

void PhysicalEngine::clearObjects(){
	objects.clear();
}

void PhysicalEngine::start(){
	running = true;
	while(running){
		update();
	}
}

void PhysicalEngine::stop(){
	running = false;
}

const std::vector<std::shared_ptr<Physical_Object>>& PhysicalEngine::getObjects() const{
	return objects;
}


void PhysicalEngine::update(){

	// On met à jour les objets physiques
	for(auto obj : objects){
		obj->saveState();
		obj->update();
	}
	
	// On détecte les collisions
	detectCollisions();

	// On résout les collisions
	resolveCollisions();
}

//std::map<std::shared_ptr<Physical_Object>, std::list<Collision>> collisions;
void PhysicalEngine::detectCollisions(){
	// On détecte les collisions entre les objets physiques
	// On compare chaque objet avec tous les autres objets O(n^2)
	for(auto it1 = objects.begin(); it1 != std::prev(objects.end()); ++it1){
		for(auto it2 = std::next(it1); it2 != objects.end(); ++it2){
			Vector2DF intersection_point;
			Vector2DF normal;
			if((*it1)->isColliding(**it2, intersection_point, normal)){
				this->collisions[*it1].push_back({*it2, intersection_point, normal});
				this->collisions[*it2].push_back({*it1, intersection_point, normal});
			}
		}
	}
}

/*
		struct Collision{
					std::shared_ptr<Physical_Object> obj2;
					Vector2DF intersection_point;
					Vector2DF normal;
				};

		std::vector<std::shared_ptr<Physical_Object>> objects;
		std::map<std::shared_ptr<Physical_Object>, std::list<Collision>> collisions;
*/

void PhysicalEngine::resolveCollisions(){
	// On résout les collisions
	for(auto& [obj, collision_list] : collisions){
		// on cherche la distance la plus proche au point de collision pour éviter la pénétration
		float min_distance = std::numeric_limits<float>::max();
		Collision &min_collision{};
		Vector2DF speed = obj->getSpeed();

		for(auto& collision : collision_list){
			float distance = obj->getPosition().distance_square(collision.intersection_point);
			if(distance < min_distance){
				min_distance = distance;
				min_collision = collision;
			}
		}

		// On déplace l'objet pour éviter la pénétration, 
		//jusqu'à ce que le point de collision soit à la distance du rayon
		speed.normalize();
		speed = speed * std::sqrt(min_distance);

		// on restaure l"état de l'objet
		obj->restoreState();

		// on applique la vitesse et déplace les objets
		obj->setSpeed(speed);
		obj->update();
		// ensuite on applique la réflexion de la vitesse de colision par rapport à la normale (rebond)
		// v' = v - 2(v.n)n (symétrie par rapport à la normale)
		// on pourrait aussi ajouter un coefficient de restitution pour simuler l'amortissement
		// v' = -e(v.n)n + (1+e)v
		// avec e le coefficient de restitution (0 < e < 1)
		// On pourrait même prendre en compte la masse des objets et la vitesse de l'objet 2
		// v' = (m1-m2)/(m1+m2)v1 + 2m2/(m1+m2)v2
		speed = (obj->getMass() - min_collision.obj2->getMass())/(obj->getMass() + *min_collision.obj2->getMass()) * speed
				+ 2 * min_collision.obj2->getMass()/(obj->getMass() + min_collision.obj2->getMass()) * min_collision.obj2->getSpeed();
		// ou simplement opposer la vitesse : v' = -v pour un rebond parfait
		//speed = speed - 2 * speed.scalarProduct(min_collision.normal) * min_collision.normal;


		// on applique la nouvelle vitesse, 
		// à la prochaine itération, l'objet ne devrait plus être en collision
		obj->setSpeed(speed);
	}
}