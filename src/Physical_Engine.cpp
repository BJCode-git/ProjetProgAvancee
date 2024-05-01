#include "Physical_Engine.hpp"

/*

// Algorithme du moteur physique 
//
//	Calcul des nouvelles positions -> Détection des collisions -> Calcul de réponses aux collisions -> 
//	Mise à jour de l'état des objets physiques -> Calcul des forces -> Calcul des accélérations ->
//
//

// Le gestion de la physique sera fait ici (déplacement, collision, etc)
// Pour la collision, on utilisera la méthode des axes séparateurs puisque 
// les objets physiques seront des rectangles, des cercles et des polygones convexes.
// Nous utiliserons une phase large pour détecter les collisions et une phase étroite pour les résoudre.
// Pour le déplacement, on utilisera la méthode de la vitesse et de l'accélération
// Pour l'accélération, on utilisera la méthode de la force et de la masse
// Par défaut, un objet physique se trouve dans une boudning box, ce qui permet de faire des détections de colisions plus rapides et plus simples
// Les objets physiques peuvent être statiques ou dynamiques, et peuvent ignorer la gravité ou les collisions
#include <iostream>
#include <utility>
#include <cmath>
#include <limits>

#include <memory>
#include <vector>
#include <array>
#include <list>

#include "debug.hpp"

#ifndef PHYSICAL_OBJECT_HPP
#define PHYSICAL_OBJECT_HPP


// Algorithme du moteur physique 
//
//	Calcul des nouvelles positions -> Détection des collisions -> Calcul de réponses aux collisions -> 
//	Mise à jour de l'état des objets physiques -> Calcul des forces -> Calcul des accélérations ->
//
//

// Le gestion de la physique sera fait ici (déplacement, collision, etc)
// Pour la collision, on utilisera la méthode des axes séparateurs puisque 
// les objets physiques seront des rectangles, des cercles et des polygones convexes.
// Nous utiliserons une phase large pour détecter les collisions et une phase étroite pour les résoudre.
// Pour le déplacement, on utilisera la méthode de la vitesse et de l'accélération
// Pour l'accélération, on utilisera la méthode de la force et de la masse
// Par défaut, un objet physique se trouve dans une boudning box, ce qui permet de faire des détections de colisions plus rapides et plus simples
// Les objets physiques peuvent être statiques ou dynamiques, et peuvent ignorer la gravité ou les collisions


class Physical_Object;
class Convex_Polygon;
class Circle;
//class Vector_Numerical;
template<typename T, size_t Size> class NumericVector;


using Vector2D  = NumericVector<unsigned int,2>;//std::pair<int, int>;
using Vector2DF = NumericVector<float       ,2>;//std::pair<float, float>;

// Point 2D
using Point2D  = NumericVector<unsigned int,2>;
using Point2DF = NumericVector<float       ,2>;
// Polygone 2D
using Polygon  = std::list<Point2DF>;
// Equation de droite (a*x + b*y + c = 0)
//using CartesianLine  = std::array<int,3>;
//using CartesianLineF = std::array<float,3>;

// Forme de l'objet physique
enum class SHAPE { NONE, CIRCLE, POLYGON};

// force appliquée à un objet physique, 
//prend en paramètre la position de l'objet et la masse de l'objet
using Force = Vector2DF (*)(const Physical_Object&);

// Distance entre deux points

//Produit scalaire
//template <typename T> float scalar_product(const T& v1, const T& v2){
//	return v1[0] * v2[0] + v1[1] * v2[1];
//}

//template <typename T> float distance_square(const T a, const T b){
//	T v = a - b;
//	return scalar_product(v, v);
//}

bool isOverlap(const std::pair<float, float>& proj1, const std::pair<float, float>& proj2){
	return proj1.first <= proj2.second && proj2.first <= proj1.second;
}


template<typename T, size_t Size>
class NumericVector {
	private:
		std::array<T, Size> elements;

	public:
		// Constructeur par défaut
		NumericVector(){
			elements.fill(0);
		}

		// Constructeur initialisant tous les éléments à une valeur donnée
		NumericVector(const T& value) {
			elements.fill(value);
		}

		 // Constructeur initialisant les éléments avec une liste d'initialisation
		NumericVector(std::initializer_list<T> list) {
			for(size_t i=0; i<std::min(list.size(),Size);i++){
				elements[i]=*(list.begin()+i);
			}
		}

		// Accès aux éléments du vecteur
		T& operator[](size_t index) {
			if (index >= Size) {
				throw std::out_of_range("Index out of range");
			}
			return elements[index];
		}

		const T& operator[](size_t index) const {
			if (index >= Size) {
				throw std::out_of_range("Index out of range");
			}
			return elements[index];
		}

		// Opérateurs de comparaison
		bool operator==(const NumericVector<T, Size>& other) const {
			for (size_t i = 0; i < Size; ++i) {
				if (elements[i] != other[i]) {
					return false;
				}
			}
			return true;
		}

		bool operator!=(const NumericVector<T, Size>& other) const {
			return !(*this == other);
		}

		// Opérateurs arithmétiques
		NumericVector<T, Size> operator+(const NumericVector<T, Size>& other) const {
			NumericVector<T, Size> result;
			for (size_t i = 0; i < Size; ++i) {
				result[i] = elements[i] + other[i];
			}
			return result;
		}

		NumericVector<T, Size> operator-(const NumericVector<T, Size>& other) const {
			NumericVector<T, Size> result;
			for (size_t i = 0; i < Size; ++i) {
				result[i] = elements[i] - other[i];
			}
			return result;
		}

		// Multiplication par un scalaire
		NumericVector<T, Size> operator*(const T& scalar) const {
			NumericVector<T, Size> result;
			for (size_t i = 0; i < Size; ++i) {
				result[i] = elements[i] * scalar;
			}
			return result;
		}

		// Division par un scalaire
		NumericVector<T, Size> operator/(const T& scalar) const {
			if (scalar == 0) {
				throw std::invalid_argument("Division by zero");
			}
			NumericVector<T, Size> result;
			for (size_t i = 0; i < Size; ++i) {
				result[i] = elements[i] / scalar;
			}
			return result;
		}

		// Produit scalaire
		T scalarProduct(const NumericVector<T, Size>& other) const {
			T result = 0;
			for (size_t i = 0; i < Size; ++i) {
				result += elements[i] * other[i];
			}
			return result;
		}
		// Produit vectoriel
		NumericVector<T, Size> crossProduct(const NumericVector<T, Size>& other) const {
			static_assert(Size == 3, "Cross product is only defined in 3D");
			return {elements[1] * other[2] - elements[2] * other[1],
					elements[2] * other[0] - elements[0] * other[2],
					elements[0] * other[1] - elements[1] * other[0]};
		}

		// distance au carré
		T distance_square(const NumericVector<T, Size>& other) const {
			T result = 0;
			for (size_t i = 0; i < Size; ++i) {
				result += (elements[i] - other[i]) * (elements[i] - other[i]);
			}
			return result;
		}


		// Affichage du vecteur
		friend std::ostream& operator<<(std::ostream& os, const NumericVector<T, Size>& vector) {
			os << "(";
			for (size_t i = 0; i < Size - 1; ++i) {
				os << vector[i] << ", ";
			}
			os << vector[Size - 1] << ")";
			return os;
		}
};


class BoundingBox{
	public:
		BoundingBox();
		BoundingBox(const Point2DF top_left, const Point2DF top_right, 
					const Point2DF bottom_left, const Point2DF bottom_right);
		~BoundingBox();

		bool isColliding(const BoundingBox &other, Vector2DF &intersection_point, Vector2DF &normal) const;
		Point2DF getCenter() const;

	private:
		bool isBoundingBox() const;
		std::pair<float, float> project(const Vector2DF& axis) const;

		std::array<Point2DF,4> vertices;//top_left, top_right, bottom_left, bottom_right;
};

class Physical_Object{

	public:

		Physical_Object(Point2DF centroid = {0, 0},
						SHAPE shape=SHAPE::NONE,
						float mass = 1.0,
						bool is_static = false,
						bool ignore_gravity = false,
						bool ignore_collision = false,
						bool breakable = false,
						uint8_t life = 1
						);
		virtual ~Physical_Object();


		void setBreakable(bool,uint8_t);
		bool isBreakable() const;
		uint8_t getLife() const;

		
		void setSpeed         (Vector2DF);
		void setAcceleration  (Vector2DF);

		void setForces        (std::list<Force>);
		void addForce         (Force);
		void removeForce      (Force);
		void removeForce      (unsigned int);
		void clearForces      ();

		void setMass(float);
		void setStatic(bool);
		void setIgnoreCollision(bool);

		Vector2DF        getSpeed()             const;
		Vector2DF        getAcceleration()      const;
		std::list<Force> getForces()            const;
		float            getMass()              const;
		bool             isStatic()             const;
		bool             isCollisions_ignored() const;

		virtual void             saveState();
		virtual void             restoreState();
		
		virtual Vector2DF getPosition() const                          ;
		virtual void      setPosition(Vector2DF)                        ;
		// Méthodes virtuelles pures
		virtual bool      isColliding(const Physical_Object &, Vector2DF &, Vector2DF &) const = 0;
		virtual void      update()                                                             = 0;

	protected:
		
		// donne la normale à un point donné de l'objet physique
		//virtual void getNormal(Vector2DF)   = 0;

		Vector2DF centroid;
		Vector2DF speed, acceleration;

		void setBoundingBox(const Point2DF ,const Point2DF ,const Point2DF ,const Point2DF );
		void setBoundingBox(const BoundingBox &);

		// Méthodes virtuelles pures
		virtual void                    computeMinimumBoundingBox()          = 0;
		virtual std::pair<float, float> project(const Vector2DF& axis) const = 0;


	private:
		void updateSpeed()       ;
		void updateAcceleration();

		const SHAPE shape;
		BoundingBox hitbox;

		float mass;
		bool ignore_collision, is_static, breakable;
		uint8_t life;
		std::list<Force> F_ext;

		Vector2DF saved_position;
		Vector2DF saved_speed;
		Vector2DF saved_acceleration;
		bool      saved_life;

};

Vector2DF Gravity(const Physical_Object& obj) {
	return {0, 9.81};
}

Vector2DF Friction(const Physical_Object& obj) {

	float alpha = 0.1;
	return {-obj.getSpeed()[0] * alpha, -obj.getSpeed()[1] * alpha};
}

class Convex_Polygon : public Physical_Object{
	public:
		Convex_Polygon(const Polygon &);
		//Convex_Polygon(const Polygon);
		~Convex_Polygon();

		bool pushPoint(Point2DF point);
		bool insertPoint(unsigned int, Point2DF);

		bool removePoint(Point2DF);
		bool removePoint(unsigned int);

		Polygon& getPoints() const;
		
		virtual void      update()                                                            override;
		virtual void      setPosition(Vector2DF)                                              override;
		virtual Vector2DF getPosition()                                                 const override;
		virtual bool      isColliding(const Physical_Object &,Vector2DF &,Vector2DF &)  const override;
		virtual bool      isColliding(const Convex_Polygon &,Vector2DF &,Vector2DF &)   const;
		virtual bool      isColliding(const Circle &,Vector2DF &,Vector2DF &)           const;

	protected:
		
		//virtual void getNormal(Vector2DF) override;

		// Méthode pour la détection de collision par l'algorithme des axes séparateurs
		virtual std::pair<float, float> project(const Vector2DF& )                       const override;
		std::vector<Vector2DF>          getEdges()                                       const;
		Vector2DF                       projectPoint(const Vector2DF&, const Vector2DF&) const;

		void computeCentroid();

		void rotatePoints(Polygon& points, const Vector2DF& pivot, float angle);
		int  findMinimumBoundingBox(const Polygon& points);
		void updateMinimumBoundingBox(const Polygon& points, int k, Polygon& min_bounding_box, float& min_area);
		virtual void computeMinimumBoundingBox() override;

	private:

		bool isConvex() const;
		Polygon points;

};

class Circle : public Physical_Object{
	public:
		Circle(Vector2DF & pos, unsigned int r);
		Circle(Vector2DF pos, unsigned int r);
		~Circle();

		void setRadius(unsigned int radius);
		int getRadius() const;

		virtual void update()                                                             override;
		virtual bool isColliding(const Physical_Object &, Vector2DF &, Vector2DF &) const override;
		virtual bool isColliding(const Convex_Polygon &,  Vector2DF &, Vector2DF &) const;
		virtual bool isColliding(const Circle &,          Vector2DF &, Vector2DF &) const;

	protected:
	
		// Méthode pour la détection de collision par l'algorithme des axes séparateurs
		virtual std::pair<float, float> project(const Vector2DF& axis) const override;

	private:
		unsigned int radius;
		void computeMinimumBoundingBox() override;
};

#endif
*/

/******************
 *     Forces     *
 ******************/

Vector2DF Gravity(const Physical_Object& obj) {
	return {0, 9.81};
}

Vector2DF Friction(const Physical_Object& obj) {

	float alpha = 0.1;
	return {-obj.getSpeed()[0] * alpha, -obj.getSpeed()[1] * alpha};
}

/******************
 *   Projection    *
 ******************/
bool isOverlap(const std::pair<float, float>& proj1, const std::pair<float, float>& proj2){
	return proj1.first <= proj2.second && proj2.first <= proj1.second;
}

/******************
 *   BoundingBox  *
 ******************/

BoundingBox::BoundingBox():
	top_left({0, 0}),
	top_right({0, 0}),
	bottom_left({0, 0}),
	bottom_right({0, 0})
{
	debug("Création d'une bounding box par défaut");
}

BoundingBox::BoundingBox(const Point2DF top_left,const Point2DF top_right, 
						 const Point2DF bottom_left,const Point2DF bottom_right):
	top_left(top_left),
	top_right(top_right),
	bottom_left(bottom_left),
	bottom_right(bottom_right)
{
	if(!isBoundingBox()){ 
		std::cerr << top_left << " " << top_right << " " << bottom_left << " " << bottom_right << std::endl;
		throw std::invalid_argument("Les points ne forment pas une bounding box");
	}
	debug("Création d'une bounding box");
}

BoundingBox::~BoundingBox(){
	debug("Destruction d'une bounding box");
}

bool BoundingBox::isBoundingBox() const{
	// Rq : on peut avoir une bounding box rectangulaire, mais qui est pivotée par rapport à l'axe des abscisses
	// On vérifie que les points forment bien une bounding box


	// On vérifie que les points sont bien ordonnés
	if(top_left[1] > bottom_left[1] || top_right[1]   > bottom_right[1] 
	|| top_left[0] > top_right[0]   || bottom_left[0] > bottom_right[0]){
		debug("Les points ne sont pas ordonnés");
		return false;
	}

	// On vérifie que les côtés sont bien égaux (rectangle)

	unsigned int width_t  = top_left.distance_square(top_right);
	unsigned int width_b  = bottom_left.distance_square(bottom_right);
	unsigned int height_l = top_left.distance_square(bottom_left);
	unsigned int height_r = top_right.distance_square(bottom_right);

	if( width_t != width_b || height_l != height_r){
		std::cerr << width_t << " " << width_b << " " << height_l << " " << height_r << std::endl;
		debug("Les côtés ne sont pas égaux");
		return false;
	}

	// On vérifie que les côtés sont bien perpendiculaires
	Vector2DF v1 = top_right - top_left;
	Vector2DF v2 = bottom_left - top_left;
	Vector2DF v3 = bottom_right - bottom_left;
	Vector2DF v4 = top_right - bottom_right;

	if(v1.scalarProduct(v2) != 0 || v2.scalarProduct(v3) != 0 || v3.scalarProduct(v4) != 0 || v4.scalarProduct(v1) != 0){
		debug("Les côtés ne sont pas perpendiculaires");
		return false;
	}

	return true;

}

Point2DF BoundingBox::getCenter() const{
	// rq : la bouding box est un rectangle qui peut être pivoté par rapport à l'axe des abscisses
	// On renvoie le centre de la bounding box
	return {(top_left + top_right + bottom_left+ bottom_right) / 4};
}


std::pair<float, float> BoundingBox::project(const Vector2DF& axis) const {
	float min = std::numeric_limits<float>::max();
	float max = std::numeric_limits<float>::min();

	float points[] = { top_left.scalarProduct(axis),
					   top_right.scalarProduct(axis),
					   bottom_left.scalarProduct(axis),
					   bottom_right.scalarProduct(axis)};

	for (const auto& p : points) {
		min = std::min(min, p);
		max = std::max(max, p);
	}

	return {min, max};
}

bool BoundingBox::isColliding(const BoundingBox& other, Vector2DF& intersection_point, Vector2DF& normal) const {
	Vector2DF axes[] = { Point2DF(top_right)         - Point2DF(top_left),
                         Point2DF(bottom_left)       - Point2DF(top_left),
                         Point2DF(other.top_right)   - Point2DF(other.top_left),
                         Point2DF(other.bottom_left) - Point2DF(other.top_left)};

    float min_overlap = std::numeric_limits<float>::max();
    Vector2DF smallest_axis;

    for (const auto& axis : axes) {
        auto [min1, max1] = project(axis);
        auto [min2, max2] = other.project(axis);

        // Vérification du chevauchement des projections
        if (max1 < min2 || max2 < min1) return false;
        
        // Calcul de l'overlap entre les intervalles de projection
        float overlap = std::min(max1, max2) - std::max(min1, min2);
        if (overlap < min_overlap) {
            min_overlap = overlap;
            smallest_axis = axis;
        }
    }

    // Calcul du point d'intersection sur l'autre boîte
    Vector2DF other_center = other.getCenter();
    intersection_point = other_center + smallest_axis * (min_overlap / 2);

    // Calcul de la normale orientée vers l'extérieur passant par le point d'intersection sur l'axe de la boîte intersectée
    normal = smallest_axis;

    return true;
}

/******************
 * Physical_Object*
 ******************/

Physical_Object::Physical_Object(Point2DF centroid,
						SHAPE shape,
						float mass,
						bool is_static,
						bool ignore_gravity,
						bool ignore_collision,
						bool breakable,
						uint8_t life):
	centroid(centroid),
	speed({0, 0}),
	acceleration({0, 0}),
	shape(shape),
	mass(mass),
	is_static(is_static),
	ignore_collision(ignore_collision),
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

void Physical_Object::setIgnoreCollision(bool){
	this->ignore_collision = ignore_collision;
}

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

bool             Physical_Object::isCollisions_ignored() const{
	return ignore_collision;
}
		
Vector2DF Physical_Object::getPosition()const{
	return centroid;
}

void      Physical_Object::setPosition(Vector2DF){
	this->centroid = centroid;
}

void Physical_Object::updateSpeed(){
	// On met à jour la vitesse
	// (v(t+1) -v(t))/(t+1 -t) ~ a(t) => v(t+1) = v(t) + a(t)
	speed[0] += acceleration[0];
	speed[1] += acceleration[1];
}

void Physical_Object::updateAcceleration(){
	// On met à jour l'accélération
	// (a(t+1) -a(t))/(t+1 -t) ~ F_ext/m => a(t+1) = a(t) + F_ext/m
	acceleration[0] = 0;
	acceleration[1] = 0;

	// Principes fondamentaux de la dynamique
	for(auto F : F_ext){
		Vector2DF v = F(*this);
		acceleration = acceleration + v/ mass;
	}
}


void Physical_Object::update(){
	if(is_static) return;

	updateSpeed();
	updateAcceleration();

	// On met à jour la position
	// (x(t+1) -x(t))/(t+1 -t) ~ v(t) => x(t+1) = x(t) + v(t)
	centroid[0]  += speed[0];
	centroid[1] += speed[1];

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


/******************
 * Convex_Polygon *
 ******************/

Convex_Polygon::Convex_Polygon(const Polygon &points):
	Physical_Object({0, 0}, SHAPE::POLYGON),
	points(points)
{
	debug("Création d'un Polygone convexe");
	if (!isConvex()) throw std::invalid_argument("Le polygone n'est pas convexe");
	computeCentroid();
}
/*
Convex_Polygon::Convex_Polygon(const Polygon points):
	Physical_Object({0, 0}, SHAPE::POLYGON),
	points(points),
	hitbox()
{
	if (!isConvex()) throw std::invalid_argument("Le polygone n'est pas convexe");
	computeCentroid();
}*/

Convex_Polygon::~Convex_Polygon(){
	debug("Destruction d'un polygone convexe");
}


bool Convex_Polygon::pushPoint(Point2DF point){
	points.push_back(point);
	if (!isConvex()) {
		points.pop_back();
		return false;
	}
	computeCentroid();
	return true;
}

bool Convex_Polygon::insertPoint(unsigned int index, Point2DF point){
	auto it = points.begin();
	std::advance(it, index);
	points.insert(it, point);
	if (!isConvex()) {
		points.erase(it);
		return false;
	}
	computeCentroid();
	return true;
}

bool Convex_Polygon::removePoint(Point2DF point){
	auto it = std::find(points.begin(), points.end(), point);
	if (it == points.end()) return false;
	points.erase(it);
	computeCentroid();
	return true;
}

bool Convex_Polygon::removePoint(unsigned int index){
	auto it = points.begin();
	std::advance(it, index);
	points.erase(it);
	computeCentroid();
	return true;
}


const Polygon& Convex_Polygon::getPoints() const{
	return points;
}

void Convex_Polygon::setPosition(Vector2DF pos){
	// On déplace le polygone en déplaçant tous ses points
	Vector2DF offset = pos - centroid;
	for (auto& p : points) {
		p[0] += offset[0];
		p[1] += offset[1];
	}
	centroid = pos;
}

Vector2DF Convex_Polygon::getPosition() const{
	return centroid;
}


bool Convex_Polygon::isConvex() const {
	int n = points.size();
	if (n < 3) return false; // Un polygone doit avoir au moins 3 points

	bool isPositive = false;
	bool isNegative = false;

	for (size_t i = 0; i < n; ++i) {
		Vector2DF p1 = points[i];
		Vector2DF p2 = points[(i + 1) % n];
		Vector2DF p3 = points[(i + 2) % n];

		float crossProduct = (p2[0] - p1[0]) * (p3[1] - p2[1]) - (p2[1] - p1[1]) * (p3[0] - p2[0]);

		
		if (crossProduct < 0)
			isNegative = true;
		else if (crossProduct > 0)
			isPositive = true;

		// si le produit vectoriel change de signe, le polygone n'est pas convexe
		if (isNegative && isPositive) return false;
	}

	return true; // Le polygone est convexe
}

void Convex_Polygon::computeCentroid(){
	// On calcule le centre de gravité du polygone
	// Pour cela, on fait la moyenne des coordonnées de tous les points
	// On suppose que le polygone est convexe
	float x = 0;
	float y = 0;
	float Sum_area = 0, area = 0;

	// On ajoute le premier point à la fin pour fermer le polygone
	points.push_back(points[0]);

	for(int i = 0; i < points.size()-1; ++i){
		area = points[i][0] * points[i+1][1] - points[i+1][0] * points[i][1];
		x += ( points[i][0] + points[i+1][0]) * area;
		y += ( points[i][1] + points[i+1][1]) * area;
		Sum_area += area;
	}
	// On retire le dernier point ajouté
	points.pop_back();

	if(Sum_area != 0){
		x = x / (3 * Sum_area);
		y = y / (3 * Sum_area);
	}
	centroid = Point2DF({x , y});

}


void Convex_Polygon::rotatePoints(Polygon& points, const Vector2DF& pivot, float angle) {
	for (auto& p : points) {
		float x = p[0] - pivot[0];
		float y = p[1] - pivot[1];
		float new_x = x * cos(angle) - y * sin(angle);
		float new_y = x * sin(angle) + y * cos(angle);
		p[0] = pivot[0] + new_x;
		p[1] = pivot[1] + new_y;
	}
}

int Convex_Polygon::findMinimumBoundingBox(const Polygon& points) {
	int n = points.size();
	int k = 1, min_index = 0;
	float min_x = std::numeric_limits<float>::max();
	for (int i = 0; i < n; ++i) {
		if (points[i][0] < min_x) {
			min_x = points[i][0];
			min_index = i;
		}
	}
	return min_index;
}

void Convex_Polygon::updateMinimumBoundingBox(const Polygon& points, int k, Polygon& min_bounding_box, float& min_area) {
	int n = points.size();
	int next = (k + 1) % n;
	float area = abs(points[next][0] - points[k][0]) * abs(points[next][1] - points[k][1]);
	if (area < min_area) {
		min_area = area;
		min_bounding_box.clear();
		min_bounding_box.push_back(points[k]);
		min_bounding_box.push_back(Vector2DF({points[next][0], points[k][1]}));
		min_bounding_box.push_back(points[next]);
		min_bounding_box.push_back(Vector2DF({points[k][0], points[next][1]}));
	}
}

/**
 * Computes the minimum bounding box for a convex polygon.
 * 
 * This function calculates the minimum bounding box that tightly encloses a convex polygon.
 * The polygon must have at least 3 points for the calculation to be valid.
 * 
 * @throws std::runtime_error if the polygon has less than 3 points.
 */
void Convex_Polygon::computeMinimumBoundingBox(){ // Vérifier si le polygone a au moins 3 points
	if (points.size() < 3) {
		throw std::runtime_error("Convex polygon must have at least 3 points to compute minimum bounding box.");
	}

	// Initialisation de la boîte englobante minimale avec des valeurs extrêmes
	float min_area = std::numeric_limits<float>::max();
	Polygon min_bounding_box;

	// Convertir les points du polygone en tableau pour être utilisé dans l'algorithme du Rotating Calipers
	std::vector<Vector2DF> polygon_points(points.begin(), points.end());

	// Appliquer l'algorithme du Rotating Calipers
	int n = polygon_points.size();
	int i = 0, j = 0, k = 0;
	float angle = 0.0;
	for (int l = 0; l < n; ++l) {
		// Point de référence
		Vector2DF p = polygon_points[i];

		// Trouver le prochain point
		j = (i + 1) % n;

		// Calculer le vecteur entre les points
		Vector2DF v({polygon_points[j][0] - p[0], polygon_points[j][1] - p[1]});

		// Calculer l'angle entre le vecteur actuel et le vecteur horizontal
		float next_angle = atan2(v[1], v[0]);

		// Calculer l'angle de rotation entre les points
		float rotation_angle = next_angle - angle;

		// Faire tourner les points autour du point de référence
		rotatePoints(polygon_points, p, rotation_angle);

		// Mettre à jour l'angle actuel
		angle = next_angle;

		// Trouver les indices du rectangle minimal
		k = findMinimumBoundingBox(polygon_points);

		// Mettre à jour la boîte englobante minimale si nécessaire
		updateMinimumBoundingBox(polygon_points, k, min_bounding_box, min_area);

		// Mettre à jour l'indice du point de départ
		i = (k + 1) % n;
	}

	// Mettre à jour les coins de la boîte englobante minimale de l'objet physique
	setBoundingBox(min_bounding_box[0], min_bounding_box[1], min_bounding_box[2], min_bounding_box[3]);
	//hitbox = BoundingBox(min_bounding_box[0], min_bounding_box[1], min_bounding_box[2], min_bounding_box[3]);
}


void Convex_Polygon::update(){
	Physical_Object::update();

	// On met à jour les positions des points du polygone
	for (auto& p : points) {
		p[0] += speed[0];
		p[1] += speed[1];
	}

}


bool Convex_Polygon::isColliding(const Physical_Object& other, Vector2DF& intersection, Vector2DF& normal) const{
	try{
		switch(other.getShape()){
			case SHAPE::POLYGON:
				return isColliding(dynamic_cast<const Convex_Polygon&>(other), intersection, normal);
			case SHAPE::CIRCLE:
				return isColliding(dynamic_cast<const Circle&>(other), intersection, normal);
			default:	;
		}
	}
	catch(std::bad_cast &e){
		debug(e.what());
	}

	return Physical_Object::isColliding(other, intersection, normal);
}


std::pair<float, float> Convex_Polygon::project(const Vector2DF& axis) const {

	float min_proj = std::numeric_limits<float>::max();
	float max_proj = -std::numeric_limits<float>::max();
	for (const auto& point : points) {
		float proj = point.scalarProduct(axis);
		min_proj = std::min(min_proj, proj);
		max_proj = std::max(max_proj, proj);
	}
	return {min_proj, max_proj};
}


std::vector<Vector2DF> Convex_Polygon::getEdges() const {
	std::vector<Vector2DF> edges;

	for (auto it1 = points.begin(); it1 != std::prev(points.end()); ++it1) {
		auto it2 = std::next(it1);
		Vector2DF edge = (*it2) - (*it1);//{it2->first - it1->first, it2->second - it1->second};
		edges.push_back(edge);
	}
	return edges;
}

Vector2DF Convex_Polygon::projectPoint(const Vector2DF& point, const Vector2DF& edge) const {
	float t = point.scalarProduct(edge) / edge.scalarProduct(edge);
	t = std::clamp(t, 0.0f, 1.0f);
	return {edge[0] * t, edge[1] * t};
}

bool Convex_Polygon::isColliding(const Convex_Polygon &other, Vector2DF &intersection_point, Vector2DF &normal) const {
	const Polygon& poly2 = other.getPoints();
	
	// Déterminer les axes de séparation
	std::vector<Vector2DF> axes;
	for (auto it1 = points.begin(); it1 != std::prev(points.end()); ++it1) {
		auto it2 = std::next(it1);
		Vector2DF edge = (*it2) - (*it1);//{it2->first - it1->first, it2->second - it1->second};
		axes.push_back({-edge[1], edge[0]}); // Normale à l'arête
	}
	for (auto it1 = poly2.begin(); it1 != std::prev(poly2.end()); ++it1) {
		auto it2 = std::next(it1);
		Vector2DF edge = (*it2) - (*it1);//{it2->first - it1->first, it2->second - it1->second};
		axes.push_back({-edge[1], edge[0]}); // Normale à l'arête
	}
	
	// Itérer sur les axes de séparation
	for (const auto& axis : axes) {
		// Projetter les polygones sur l'axe
		std::pair<float, float> proj1 = project(axis);
		std::pair<float, float> proj2 = project(axis);
	
		// Vérifier s'il y a une séparation
		if (!isOverlap(proj1, proj2)) {
			// Les polygones sont séparés, donc pas de collision
			return false;
		}
	}
	
	// Les polygones se chevauchent sur tous les axes, donc il y a une collision
	
	// Trouver le point d'intersection le plus proche
	float min_dist_sq = std::numeric_limits<float>::max();
	for (const auto& edge : getEdges()) {
		for (const auto& point : poly2) {
			float dist_sq = point.distance_square(projectPoint(point, edge));
			if (dist_sq < min_dist_sq) {
				min_dist_sq = dist_sq;
				intersection_point = point;
				normal = {edge[1], -edge[0]}; // Normale à l'arête
			}
		}
	}
	
	return true;
}

bool Convex_Polygon::isColliding(const Circle &other, Vector2DF &intersection_point, Vector2DF &normal) const {

	// Déterminer les axes de séparation
	std::vector<Vector2DF> axes;
	for (auto it1 = points.begin(); it1 != std::prev(points.end()); ++it1) {
		auto it2 = std::next(it1);
		Vector2DF edge = (*it2) - (*it1);//{it2->first - it1->first, it2->second - it1->second};
		axes.push_back({-edge[1], edge[0]}); // Normale à l'arête
	}
	
	// Itérer sur les axes de séparation
	for (const auto& axis : axes) {
		// Projetter le polygone sur l'axe
		std::pair<float, float> proj1 = project(axis);
		std::pair<float, float> proj2 = {other.getPosition().scalarProduct(axis) - other.getRadius(), 
										 other.getPosition().scalarProduct(axis) + other.getRadius()};
	
		// Vérifier s'il y a une séparation
		if (!isOverlap(proj1, proj2)) {
			// Les polygones sont séparés, donc pas de collision
			return false;
		}
	}
	
	// Les polygones se chevauchent sur tous les axes, donc il y a une collision
	
	// Trouver le point d'intersection le plus proche
	float min_dist_sq = std::numeric_limits<float>::max();
	for (const auto& edge : getEdges()) {
		Vector2DF point = {other.getPosition()[0], other.getPosition()[1]};
		float dist_sq = point.distance_square(projectPoint(point, edge));
		if (dist_sq < min_dist_sq) {
			min_dist_sq = dist_sq;
			intersection_point = point;
			normal = {edge[1], -edge[0]}; // Normale à l'arête
		}
	}
	
	return true;
}


/******************
 *     Circle     *
 ******************/

// On autorise les cercles de rayon nul pour une cinématique du point
Circle::Circle(Vector2DF & pos, unsigned int r):
	Physical_Object(pos, SHAPE::CIRCLE),
	radius(r)
{
	debug("Création d'un disque");
	//centroid = pos;
	computeMinimumBoundingBox();
}

Circle::Circle(Vector2DF pos, unsigned int r):
	Physical_Object(pos, SHAPE::CIRCLE),
	radius(r)
{
	debug("Création d'un disque");
	computeMinimumBoundingBox();
}


Circle::~Circle(){
	debug("Destruction d'un cercle");
}

void Circle::setRadius(unsigned int radius){
	this->radius = radius;
}

int Circle::getRadius() const{
	return radius;
}


void Circle::computeMinimumBoundingBox(){
	// On met à jour la bounding box
	// top_left = (x - r, y - r)
	// top_right = (x + r, y - r)
	// bottom_left = (x - r, y + r)
	// bottom_right = (x + r, y + r)
	setBoundingBox(  Point2DF({centroid[0] - radius, centroid[1] - radius}),
					 Point2DF({centroid[0] + radius, centroid[1] - radius}),
					 Point2DF({centroid[0] - radius, centroid[1] + radius}),
					 Point2DF({centroid[0] + radius, centroid[1] + radius}));
}

void Circle::update(){
	Physical_Object::update();
}

std::pair<float, float> Circle::project(const Vector2DF& axis) const {
	float  proj = centroid.scalarProduct(axis);
	return {proj - radius, proj + radius};
}

bool Circle::isColliding(const Physical_Object& other, Vector2DF& intersection, Vector2DF& normal) const{

	try{
		switch(other.getShape()){
			case SHAPE::POLYGON:
				return isColliding(dynamic_cast<const Convex_Polygon&>(other), intersection, normal);
			case SHAPE::CIRCLE:
				return isColliding(dynamic_cast<const Circle&>(other), intersection, normal);
			default:
				;
		}
	}
	catch(std::bad_cast &e){
		debug(e.what());
	}

	return Physical_Object::isColliding(other, intersection, normal);
}

bool Circle::isColliding(const Circle& other, Vector2DF& collision_point, Vector2DF& normal) const{
	Vector2DF d = other.centroid - centroid;
	double distance = centroid.distance_square(other.centroid);

	if (distance > radius*radius + other.radius*other.radius)
		return false;

	// on détermine la direction de la normale
	normal = other.centroid - centroid;
	collision_point = centroid + normal * radius / sqrt(distance);

	return true;
}

bool Circle::isColliding(const Convex_Polygon& other, Vector2DF& intersection_point, Vector2DF& normal) const {
	Vector2DF closest_point;
	float min_distance = std::numeric_limits<float>::max();

	// Iterate over each edge of the polygon
	for (const auto& edge : other.getEdges()) {
		// Project the center of the circle onto the edge
		std::pair<float, float> proj = project(edge);
		Vector2DF projected_point({proj.first, proj.second});

		// Calculate the distance between the projected point and the center of the circle
		float distance = centroid.distance_square(projected_point);

		// Check if the distance is smaller than the minimum distance found so far
		if (distance < min_distance) {
			min_distance = distance;
			closest_point = projected_point;
			// Calculate the normal vector
			normal = centroid - projected_point;
		}
	}

	// Check if the closest point is inside the circle
	if (min_distance <= radius * radius) {
		intersection_point = closest_point;
		return true;
	}

	return false;
}


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