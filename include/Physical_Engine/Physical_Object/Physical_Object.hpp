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
#include "Physical_Engine/NumericVector.hpp"
#include "Physical_Engine/BoundingBox/BoundingBox.hpp"


class Physical_Object;

// force appliquée à un objet physique, 
//prend en paramètre la position de l'objet et la masse de l'objet
using Force = Vector2DF (*)(const Physical_Object&);

Vector2DF Gravity(const Physical_Object& obj);

Vector2DF Friction(const Physical_Object& obj);


// Forme de l'objet physique
enum class SHAPE { NONE, CIRCLE, POLYGON};

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
						//bool ignore_collision = false,
						bool breakable = false,
						uint8_t life = 1
						);
		virtual ~Physical_Object();

		void reduceLife();
		void setBreakable(bool,uint8_t l=1);
		bool isBreakable() const;
		uint8_t getLife() const;
		SHAPE getShape() const;
		const BoundingBox & getBoundingBox() const;

		virtual void move             (Vector2DF);
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
		
		virtual Vector2DF getPosition() const   ;
		virtual void      setPosition(Vector2DF);

		// Méthodes virtuelles pures
		virtual bool      isColliding(const Physical_Object &, Vector2DF &, Vector2DF &) const = 0;
		virtual void      update(float dt=1)                                                   = 0;

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

		void updateSpeed(float dt=1)       ;
		void updateAcceleration(float dt=1);

		const SHAPE shape;
		BoundingBox hitbox;

		float mass;
		bool is_static, breakable; //ignore_collision,
		uint8_t life;
		std::list<Force> F_ext;

		Vector2DF saved_position;
		Vector2DF saved_speed;
		Vector2DF saved_acceleration;
		bool      saved_life;

};


#endif // PHYSICAL_OBJECT_HPP