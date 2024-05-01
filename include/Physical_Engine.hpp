#ifndef PHYSICAL_OBJECT_HPP
#define PHYSICAL_OBJECT_HPP

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

#include "debug.hpp"


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
template<typename T, size_t Size, typename En = void> 
class NumericVector;


using Vector2D  = NumericVector<unsigned int,2>;
using Vector2DF = NumericVector<float       ,2>;

// Point 2D
using Point2D  = NumericVector<unsigned int,2>;
using Point2DF = NumericVector<float       ,2>;
// Polygone 2D
using Polygon  = std::vector<Point2DF>;

// Forme de l'objet physique
enum class SHAPE { NONE, CIRCLE, POLYGON};

// force appliquée à un objet physique, 
//prend en paramètre la position de l'objet et la masse de l'objet
using Force = Vector2DF (*)(const Physical_Object&);

Vector2DF Gravity(const Physical_Object& obj);

Vector2DF Friction(const Physical_Object& obj);


bool isOverlap(const std::pair<float, float>& proj1, const std::pair<float, float>& proj2);

/**
 * @class NumericVector
 * @brief A class template representing a numeric vector.
 * @tparam T The type of the elements in the vector.
 * @tparam Size The size of the vector.
 */
template< typename T, size_t Size>
class NumericVector<T, Size, std::enable_if_t<std::is_arithmetic<T>::value>>{
	private:
		std::array<T, Size> elements;

	public:
		/**
		 * @brief Default constructor. Initializes all elements to zero.
		 */
		NumericVector(){
			elements.fill(0);
		}

		/**
		 * @brief Constructor that initializes all elements to a given value.
		 * 
		 * @param value The value to initialize the elements with.
		 */
		NumericVector(const T& value) {
			elements.fill(value);
		}

		/**
		 * @brief Constructor that initializes the elements with an initializer list.
		 * 
		 * @param list The initializer list containing the values to initialize the elements with.
		 */
		NumericVector(std::initializer_list<T> list) {
			for(size_t i=0; i<std::min(list.size(),Size);i++){
				elements[i]=*(list.begin()+i);
			}
		}

		/**
		 * @brief Accesses the elements of the vector.
		 * 
		 * @param index The index of the element to access.
		 * @return T& A reference to the element at the specified index.
		 * @throw std::out_of_range If the index is out of range.
		 */
		T& operator[](size_t index) {
			if (index >= Size) {
				throw std::out_of_range("Index out of range");
			}
			return elements[index];
		}

		/**
		 * @brief Accesses the elements of the vector (const version).
		 * 
		 * @param index The index of the element to access.
		 * @return const T& A const reference to the element at the specified index.
		 * @throw std::out_of_range If the index is out of range.
		 */
		const T& operator[](size_t index) const {
			if (index >= Size) {
				throw std::out_of_range("Index out of range");
			}
			return elements[index];
		}

		/**
		 * @brief Equality comparison operator.
		 * 
		 * @param other The vector to compare with.
		 * @return bool True if the vectors are equal, false otherwise.
		 */
		bool operator==(const NumericVector<T, Size>& other) const {
			for (size_t i = 0; i < Size; ++i) {
				if (elements[i] != other[i]) {
					return false;
				}
			}
			return true;
		}

		/**
		 * @brief Inequality comparison operator.
		 * 
		 * @param other The vector to compare with.
		 * @return bool True if the vectors are not equal, false otherwise.
		 */
		bool operator!=(const NumericVector<T, Size>& other) const {
			return !(*this == other);
		}

		/**
		 * @brief Addition operator.
		 * 
		 * @param other The vector to add.
		 * @return NumericVector<T, Size> The resulting vector after addition.
		 */
		NumericVector<T, Size> operator+(const NumericVector<T, Size>& other) const {
			NumericVector<T, Size> result;
			for (size_t i = 0; i < Size; ++i) {
				result[i] = elements[i] + other[i];
			}
			return result;
		}

		/**
		 * @brief Subtraction operator.
		 * 
		 * @param other The vector to subtract.
		 * @return NumericVector<T, Size> The resulting vector after subtraction.
		 */
		NumericVector<T, Size> operator-(const NumericVector<T, Size>& other) const {
			NumericVector<T, Size> result;
			for (size_t i = 0; i < Size; ++i) {
				result[i] = elements[i] - other[i];
			}
			return result;
		}

		/**
		 * @brief Scalar multiplication operator.
		 * 
		 * @param scalar The scalar value to multiply the vector with.
		 * @return NumericVector<T, Size> The resulting vector after multiplication.
		 */
		NumericVector<T, Size> operator*(const T& scalar) const {
			NumericVector<T, Size> result;
			for (size_t i = 0; i < Size; ++i) {
				result[i] = elements[i] * scalar;
			}
			return result;
		}

		/**
		 * @brief Scalar division operator.
		 * 
		 * @param scalar The scalar value to divide the vector by.
		 * @return NumericVector<T, Size> The resulting vector after division.
		 * @throw std::invalid_argument If the scalar value is zero.
		 */
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

		/**
		 * @brief Calculates the scalar product of two vectors.
		 * 
		 * @param other The vector to calculate the scalar product with.
		 * @return T The scalar product of the two vectors.
		 */
		T scalarProduct(const NumericVector<T, Size>& other) const {
			T result = 0;
			for (size_t i = 0; i < Size; ++i) {
				result += elements[i] * other[i];
			}
			return result;
		}

		/**
		 * @brief Calculates the cross product of two 3D vectors.
		 * 
		 * @param other The vector to calculate the cross product with.
		 * @return NumericVector<T, Size> The resulting vector after cross product.
		 * @throw static_assert If the size of the vectors is not 3.
		 */
		NumericVector<T, Size> crossProduct(const NumericVector<T, Size>& other) const {
			static_assert(Size == 3, "Cross product is only defined in 3D");
			return {elements[1] * other[2] - elements[2] * other[1],
					elements[2] * other[0] - elements[0] * other[2],
					elements[0] * other[1] - elements[1] * other[0]};
		}

		/**
		 * @brief Calculates the squared distance between two vectors.
		 * 
		 * @param other The vector to calculate the distance with.
		 * @return T The squared distance between the two vectors.
		 */
		T distance_square(const NumericVector<T, Size>& other) const {
			T result = 0;
			for (size_t i = 0; i < Size; ++i) {
				result += (elements[i] - other[i]) * (elements[i] - other[i]);
			}
			return result;
		}

		/**
		 * @brief Calculates the distance between two vectors.
		 * 
		 * @param other The vector to calculate the distance with.
		 * @return T The distance between the two vectors.
		 */
		T distance(const NumericVector<T, Size>& other) const {
			return std::sqrt(distance_square(other));
		}

		/**
		 * @brief Normalizes the vector.
		 * 
		 * @return NumericVector<T, Size> The normalized vector.
		 * @throw std::invalid_argument If the vector is a zero vector.
		 */
		void normalize(){
			T norm = 0;
			for (size_t i = 0; i < Size; ++i) {
				norm += elements[i] * elements[i];
			}
			if (norm == 0) {
				throw std::invalid_argument("Cannot normalize zero vector");
			}

			for (size_t i = 0; i < Size; ++i) {
				elements[i] /= norm;
			}
		}
		
		/**
		 * @brief Outputs the vector to an output stream.
		 * 
		 * @param os The output stream.
		 * @param vector The vector to output.
		 * @return std::ostream& The output stream.
		 */
		friend std::ostream& operator<<(std::ostream& os, const NumericVector<T, Size>& vector) {
			os << "(";
			for (size_t i = 0; i < Size - 1; ++i) {
				os << vector[i] << ", ";
			}
			os << vector[Size - 1] << ")";
			return os;
		}
};


/**
 * @class BoundingBox
 * @brief Represents a bounding box in 2D space.
 * 
 * The BoundingBox class is used to define a rectangular region in 2D space. It is commonly used in collision detection algorithms to check for collisions between objects.
 */
class BoundingBox{
	public:
		/**
		 * @brief Default constructor for BoundingBox.
		 */
		BoundingBox();

		/**
		 * @brief Constructor for BoundingBox.
		 * @param top_left The top-left corner of the bounding box.
		 * @param top_right The top-right corner of the bounding box.
		 * @param bottom_left The bottom-left corner of the bounding box.
		 * @param bottom_right The bottom-right corner of the bounding box.
		 */
		BoundingBox(const Point2DF top_left, const Point2DF top_right, 
					const Point2DF bottom_left, const Point2DF bottom_right);

		/**
		 * @brief Destructor for BoundingBox.
		 */
		~BoundingBox();

		/**
		 * @brief Checks if this bounding box is colliding with another bounding box.
		 * @param other The other bounding box to check collision with.
		 * @param intersection_point The intersection point between the two bounding boxes (if they are colliding).
		 * @param normal The normal vector of the collision (if they are colliding).
		 * @return True if the bounding boxes are colliding, false otherwise.
		 */
		bool isColliding(const BoundingBox &other, Vector2DF &intersection_point, Vector2DF &normal) const;

		/**
		 * @brief Gets the center point of the bounding box.
		 * @return The center point of the bounding box.
		 */
		Point2DF getCenter() const;

	private:
		/**
		 * @brief Checks if the bounding box is valid.
		 * @return True if the bounding box is valid, false otherwise.
		 */
		bool isBoundingBox() const;

		/**
		 * @brief Projects the bounding box onto a given axis.
		 * @param axis The axis to project onto.
		 * @return A pair of floats representing the minimum and maximum projection values.
		 */
		std::pair<float, float> project(const Vector2DF& axis) const;

		Point2DF top_left, top_right, bottom_left, bottom_right;
};


/**
 * @class Physical_Object
 * @brief Represents a physical object in a simulation.
 * 
 * The Physical_Object class provides a base class for representing physical objects in a simulation. It contains properties and methods for managing the object's position, speed, acceleration, forces, mass, and collision behavior.
 * 
 * @note This is an abstract base class and cannot be instantiated directly.
 */
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
		SHAPE getShape() const;

		
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

		virtual void     saveState();
		virtual void     restoreState();
		
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


/**
 * @class Convex_Polygon
 * @brief Represents a convex polygon in a 2D space.
 * 
 * The Convex_Polygon class is a derived class of Physical_Object and represents a convex polygon
 * in a 2D space. It provides methods for manipulating and querying the polygon's points, as well
 * as performing collision detection with other objects.
 */
class Convex_Polygon : public Physical_Object{
	public:
		Convex_Polygon(const Polygon &);
		//Convex_Polygon(const Polygon);
		~Convex_Polygon();

		bool pushPoint(Point2DF point);
		bool insertPoint(unsigned int, Point2DF);

		bool removePoint(Point2DF);
		bool removePoint(unsigned int);

		const Polygon& getPoints() const;
		
		virtual void      update()                                                            override;
		virtual void      setPosition(Vector2DF)                                              override;
		virtual Vector2DF getPosition()                                                 const override;
		virtual bool      isColliding(const Physical_Object &,Vector2DF &,Vector2DF &)  const override;
		virtual bool      isColliding(const Convex_Polygon &,Vector2DF &,Vector2DF &)   const;
		virtual bool      isColliding(const Circle &,Vector2DF &,Vector2DF &)           const;

	// Méthode pour la détection de collision par l'algorithme des axes séparateurs
		std::vector<Vector2DF>          getEdges()                                      const;
	protected:
		Vector2DF                       projectPoint(const Vector2DF&, const Vector2DF&) const;
		virtual std::pair<float, float> project(const Vector2DF& )                       const override;

		void computeCentroid();

		void rotatePoints(Polygon& points, const Vector2DF& pivot, float angle);
		int  findMinimumBoundingBox(const Polygon& points);
		void updateMinimumBoundingBox(const Polygon& points, int k, Polygon& min_bounding_box, float& min_area);
		virtual void computeMinimumBoundingBox() override;

	private:

		bool isConvex() const;
		Polygon points;

};


/**
 * @class Circle
 * @brief Represents a circle object that inherits from Physical_Object.
 *
 * The Circle class represents a circle object in a 2D space. It inherits from the Physical_Object class
 * and provides methods for setting and getting the radius of the circle, updating the circle's state,
 * and checking for collisions with other objects.
 */
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

#endif // PHYSICAL_OBJECT_HPP