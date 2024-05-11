#include "Physical_Engine/Physical_Object/Physical_Object.hpp"


/******************
 *     Forces     *
 ******************/

Vector2DF Gravity(const Physical_Object& obj) {
	return {0, 9.81};
}

Vector2DF Friction(const Physical_Object& obj) {

	float alpha = 0.1;
	return obj.getSpeed()* -alpha;
	//return {-obj.getSpeed()[0] * alpha, -obj.getSpeed()[1] * alpha};
}


/******************
 * Physical_Object*
 ******************/

Physical_Object::Physical_Object(Point2DF centroid,
						SHAPE shape,
						float mass,
						bool is_static,
						bool ignore_gravity,
						//bool ignore_collision,
						bool breakable,
						uint8_t life):
	centroid(centroid),
	speed({0, 0}),
	acceleration({0, 0}),
	shape(shape),
	mass(mass),
	is_static(is_static),
	//ignore_collision(ignore_collision),
	breakable(false),
	life(1),
	hitbox()
{
	std::string s_shape = "";
	switch(shape){
		case SHAPE::CIRCLE:
			s_shape = "Cercle";
			break;
		case SHAPE::POLYGON:
			s_shape = "Polygone";
			break;
		default:
			s_shape = "Aucune";
			break;
	}

	debug("Création d'un objet physique "+s_shape);
	if(mass <= 0) throw std::invalid_argument("La masse doit être strictement positive");
	if(shape == SHAPE::NONE) throw std::invalid_argument("La forme de l'objet physique doit être spécifiée");

	if(!ignore_gravity) addForce(Gravity);

}


Physical_Object::~Physical_Object(){
	debug("Destruction d'un objet physique");
}

void Physical_Object::reduceLife(){
	if(breakable && life > 0) life--;
}

void Physical_Object::setBreakable(bool breakable, uint8_t life){
	this->breakable = breakable;
	this->life = life;
}

bool Physical_Object::isBreakable() const{
	return breakable;
}

uint8_t Physical_Object::getLife() const{
	return life;
}

SHAPE Physical_Object::getShape() const{
	return shape;
}

void Physical_Object::setSpeed         (Vector2DF speed){
	this->speed = speed;
}

void Physical_Object::setAcceleration  (Vector2DF acceleration){
	this->acceleration = acceleration;
}

void Physical_Object::setForces        (std::list<Force> F_ext){
	this->F_ext = F_ext;
}

void Physical_Object::addForce         (Force F){
	F_ext.push_back(F);
}

void Physical_Object::removeForce      (Force F){
	F_ext.remove(F);
}

void Physical_Object::removeForce      (unsigned int index){
	auto it = F_ext.begin();
	std::advance(it, index);
	F_ext.erase(it);
}

void Physical_Object::clearForces      (){
	F_ext.clear();
}

void Physical_Object::setMass(float){
	if(mass <= 0) throw std::invalid_argument("La masse doit être strictement positive");
	this->mass = mass;
}

void Physical_Object::setStatic(bool){
	this->is_static = is_static;
}
/*
void Physical_Object::setIgnoreCollision(bool){
	this->ignore_collision = ignore_collision;
}
*/
Vector2DF        Physical_Object::getSpeed()             const{
	return speed;
}

Vector2DF        Physical_Object::getAcceleration()      const{
	return acceleration;
}

std::list<Force> Physical_Object::getForces()            const{
	return F_ext;
}

float            Physical_Object::getMass()              const{
	return mass;
}

bool             Physical_Object::isStatic()             const{
	return is_static;
}
/*
bool             Physical_Object::isCollisions_ignored() const{
	return ignore_collision;
}
*/
		
Vector2DF Physical_Object::getPosition()const{
	return centroid;
}

void      Physical_Object::setPosition(Vector2DF){
	this->centroid = centroid;
}

void Physical_Object::updateSpeed(float dt){
	// On met à jour la vitesse
	// (v(t+dt) -v(t))/dt ~ a(t) => v(t+dt) = v(t) + a(t)*dt
	speed[0] += acceleration[0] * dt;
	speed[1] += acceleration[1] * dt;
}

void Physical_Object::updateAcceleration(float dt){
	// On met à jour l'accélération
	// (a(t+dt) -a(t))/dt ~ F_ext/m => a(t+dt) = a(t) + F_ext/m *dt
	acceleration[0] = 0;
	acceleration[1] = 0;

	// Principes fondamentaux de la dynamique
	for(auto F : F_ext){
		Vector2DF v = F(*this);
		acceleration = acceleration + v/ mass *dt;
	}
}


void Physical_Object::update(float dt){
	if(is_static) return;

	updateSpeed(dt);
	updateAcceleration(dt);

	// On met à jour la position
	// (x(t+dt) -x(t))/dt ~ v(t) => x(t+dt) = x(t) + v(t)
	centroid[0] += speed[0] * dt;
	centroid[1] += speed[1] * dt;

}


void Physical_Object::saveState(){
	// On sauvegarde l'état de l'objet physique
	// On sauvegarde la position, la vitesse et l'accélération
	// On sauvegarde aussi les forces appliquées

	saved_position = centroid;
	saved_speed = speed;
	saved_acceleration = acceleration;
	saved_life = life;

}

void Physical_Object::restoreState(){
	// On restaure l'état de l'objet physique
	// On restaure la position, la vitesse et l'accélération

	centroid = saved_position;
	speed = saved_speed;
	acceleration = saved_acceleration;
	life = saved_life;
}

const BoundingBox & Physical_Object::getBoundingBox() const{
	return hitbox;
}

void Physical_Object::setBoundingBox(const Point2DF top_left,const Point2DF top_right, 
									const  Point2DF bottom_left,const Point2DF bottom_right){
	try{
		hitbox = BoundingBox(top_left, top_right, bottom_left, bottom_right);
	}
	catch(std::invalid_argument &e){
		debug(e.what());
		throw std::invalid_argument("Les points ne forment pas une bounding box");
	}
}

void Physical_Object::setBoundingBox(const BoundingBox &hitbox){
	this->hitbox = hitbox;
}


bool Physical_Object::isColliding(const Physical_Object& other, Vector2DF &intersection, Vector2DF &normal) const{
	return hitbox.isColliding(other.hitbox, intersection, normal);
}
