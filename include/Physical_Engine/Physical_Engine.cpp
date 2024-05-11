#include "Physical_Engine/Physical_Engine.hpp"


/******************
 * Physical_Engine *
 ******************/


Physical_Engine::Physical_Engine():
	objects(),
	collisions(),
	running(false)
{
	debug("Physical_Engine::Physical_Engine()");
	SDL_InitSubSystem(SDL_INIT_EVENTS);
}

Physical_Engine::~Physical_Engine(){
	debug("Physical_Engine::~Physical_Engine()");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

void Physical_Engine::setScene(int width, int height){
	scene.width = width;
	scene.height = height;
}

void Physical_Engine::addObject(std::shared_ptr<Physical_Object>   obj){
	objects.push_back(obj);
}

void Physical_Engine::removeObject(std::shared_ptr<Physical_Object> obj){
	auto it = std::find(objects.begin(), objects.end(), obj);
	if (it != objects.end()) objects.erase(it);
}

void Physical_Engine::clearObjects(){
	objects.clear();
}

void Physical_Engine::start(){
	running = true;
	debug("Physical_Engine::start()");

	//constexpr float CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;
	//clock_t current_time,last_clock = std::clock();

	std::chrono::high_resolution_clock::time_point last_time = std::chrono::high_resolution_clock::now(), 
												   current_time;
 
	std::chrono::duration<float, std::milli> delta;
	float dt = 0;
	constexpr float  max_dt= 100; //ms
	
	while(running){
	
		// On calcule le temps écoulé depuis le dernier appel à update en ms
		current_time = std::chrono::high_resolution_clock::now();
		delta = current_time - last_time;
		last_time = current_time;
		dt = delta.count();
		
		// On met à jour les objets physiques
		// on vérifie si le temps écoulé est supérieur à max_dt
		// on procède comme suit pour limiter le temps de calcul
		if( dt >= max_dt){
			update(dt / 10);
		}
		else{
			std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(max_dt - dt)); //ms
		}
	
	}

	debug("Physical_Engine::start() reach end of loop");
}

void Physical_Engine::stop(){
	debug("Physical_Engine::stop()");
	running = false;
}

const std::vector<std::shared_ptr<Physical_Object>>& Physical_Engine::getObjects() const{
	return objects;
}


void Physical_Engine::sendDestructEvent(){
	debug("Physical_Engine::sendDestructEvent()");
	SDL_Event event;
	event.type = SDL_USEREVENT;
	SDL_PushEvent(&event);
}

void Physical_Engine::removeDeadObjects(){
	// On supprime les objets physiques qui ont une vie nulle

	auto it = objects.begin();
	while(it != objects.end()){
		if((*it)->getLife() <= 0) 
			it = objects.erase(it);
		else 
			it++;
	}
}

void Physical_Engine::update(float dt){

	auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	debug("Physical_Engine::update()" +  (std::string) std::ctime(&timenow)  );

	// On met à jour les objets physiques
	for(auto obj : objects){
		obj->saveState();
		obj->update(dt);
	}

	//debug("Physical_Engine::update() check objects");
	bool need_to_destroy = false;
	// on détecte si un objet sort de la scène
	auto it = objects.begin();
	while(it <= objects.end()){
		auto obj = *it;
		Vector2DF position = obj->getPosition();
		Vector2DF speed    = obj->getSpeed();

		// on fait rebondir l'objet sur les bords de la scène 
		if(position[0]<= 0  || position[0] >= scene.width){
			speed[0] = -speed[0];
			obj->setSpeed(speed);
		}

		if(position[1]<= 0 ){
			speed[1] = -speed[1];
			obj->setSpeed(speed);
		}

		// on réduit la vie de l'objet si il sort du bas de la scène
 		if( position[1] >= scene.height){
			obj->reduceLife();
			if(obj->getLife() <= 0) {
				it = objects.erase(it);
				sendDestructEvent();
			}
			else{
				++it;
			}
		}
		else{
			++it;
		}
		//debug("Physical_Engine::update()");

	}

	// On détecte les collisions
	//debug("Physical_Engine::update() detectCollisions");
	detectCollisions();


	// On résout les collisions
	//debug("Physical_Engine::update() resolveCollisions");
	resolveCollisions();

	// On supprime les objets physiques qui ont une vie nulle
	//debug("Physical_Engine::update() removeDeadObjects");
	removeDeadObjects();
}

//std::map<std::shared_ptr<Physical_Object>, std::list<Collision>> collisions;
void Physical_Engine::detectCollisions(){
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

void Physical_Engine::resolveCollisions(){
	// On résout les collisions
	for(auto& [obj, collision_list] : collisions){
		// on cherche la distance la plus proche au point de collision pour éviter la pénétration
		float min_distance = std::numeric_limits<float>::max();
		Collision min_collision{};
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
		Vector2DF other_speed= min_collision.obj2->getSpeed();
		speed = speed*(obj->getMass() - min_collision.obj2->getMass()) / (obj->getMass() + min_collision.obj2->getMass())
				+  other_speed * 2 * min_collision.obj2->getMass()/(obj->getMass() + min_collision.obj2->getMass());
		// ou simplement opposer la vitesse : v' = -v pour un rebond parfait
		//speed = speed - 2 * speed.scalarProduct(min_collision.normal) * min_collision.normal;


		// on applique la nouvelle vitesse, 
		// à la prochaine itération, l'objet ne devrait plus être en collision
		obj->setSpeed(speed);

		min_collision.obj2->reduceLife();

	}

}