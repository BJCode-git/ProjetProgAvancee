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

		/**
		 * @brief Default constructor for Physical_Object.
		 * @param centroid The centroid of the object.
		 * @param shape The shape of the object.
		 * @param mass The mass of the object.
		 * @param is_static Whether the object is static or not.
		 * @param ignore_gravity Whether the object should ignore gravity or not.
		 * @param breakable Whether the object is breakable or not.
		 * @param life The life of the object.
		 */
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

		/**
		 * @brief Reduces the life of the object  if it is breakable.
		 * @param force_reduction Whether to force the reduction of life or not.
		 */
		void reduceLife(bool force_reduction = false);
		/**
		 * @brief Sets the breakable property of the object.
		 * @param breakable Whether the object is breakable or not.
		 * @param l The life of the object.
		 */
		void setBreakable(bool,uint8_t l=1);
		/**
		 * @brief Gets the breakable property of the object.
		 * @return True if the object is breakable, false otherwise.
		 */
		bool isBreakable() const;
		/**
		 * @brief Gets the life of the object.
		 * @return The life of the object.
		 */
		uint8_t getLife() const;
		/**
		 * @brief Gets the shape of the object.
		 * @return The shape of the object.
		 */
		SHAPE getShape() const;
		/**
		 * @brief Gets the bounding box of the object.
		 * @return The bounding box of the object.
		 */
		const BoundingBox & getBoundingBox() const;

		/**
		 * @brief Moves the object by a given offset.
		 * @param offset The offset to move the object by.
		 */
		virtual void move     (const Vector2DF&) = 0;
		/**
		 * @brief Sets the speed of the object.
		 * @param speed The new speed of the object.
		 */
		void setSpeed         (Vector2DF);
		/**
		 * @brief Sets the acceleration of the object.
		 * @param acceleration The new acceleration of the object.
		 */
		void setAcceleration  (Vector2DF);

		/**
		 * @brief Sets the forces acting on the object.
		 * @param F_ext The external forces acting on the object.
		 */
		void setForces        (std::list<Force>);
		/**
		 * @brief Adds a force to the object.
		 * @param F The force to add to the object.
		 */
		void addForce         (Force);
		/**
		 * @brief Removes a force from the object.
		 * @param F The force to remove from the object.
		 */
		void removeForce      (Force);
		/**
		 * @brief Removes a force from the object.
		 * @param index The index of the force to remove from the object.
		 */
		void removeForce      (unsigned int);
		/**
		 * @brief Clears all forces acting on the object.
		 */
		void clearForces      ();
		
		/**
		 * @brief Sets the mass of the object.
		 * @param mass The new mass of the object.
		 */
		void setMass(float);
		/**
		 * @brief Sets the static property of the object.
		 * @param is_static Whether the object is static or not.
		 */
		void setStatic(bool);
		/**
		 * @brief Sets the ignore_collision property of the object.
		 * @param ignore_collision Whether the object should ignore collisions or not.
		 */
		void setIgnoreCollision(bool);

		/**
		 * @brief Gets the speed of the object.
		 * @return The speed of the object.
		 */
		Vector2DF        getSpeed()             const;
		/**
		 * @brief Gets the acceleration of the object.
		 * @return The acceleration of the object.
		 */
		Vector2DF        getAcceleration()      const;
		/**
		 * @brief Gets the forces acting on the object.
		 * @return The external forces acting on the object.
		 */
		std::list<Force> getForces()            const;
		/**
		 * @brief Gets the mass of the object.
		 * @return The mass of the object.
		 */
		float            getMass()              const;
		/**
		 * @brief Gets the static property of the object.
		 * @return True if the object is static, false otherwise.
		 */
		bool             isStatic()             const;
		//bool             isCollisions_ignored() const;

		/**
		 * @brief Saves the current state of the object.
		 */
		virtual void     saveState();
		/**
		 * @brief Restores the saved state to the last 
		 * saved state of the object.
		 */
		virtual void     restoreState();
		/**
		 * @brief Gets the position of the object.
		 * @return The position of the object.
		 */
		virtual Vector2DF getPosition() const   ;
		/**
		 * @brief Sets the position of the object.
		 * @param pos The new position of the object.
		 */
		virtual void      setPosition(Vector2DF);
		/**
		 * @brief Gets the centroid of the object.
		 * @return The centroid of the object.
		 */

		// Méthodes virtuelles pures
		/**
		 * @brief Checks if the object is colliding with another object.
		 * @param other The other object to check collision with.
		 * @param intersection_point The intersection point between the two objects (if they are colliding).
		 * @param normal The normal vector of the collision (if they are colliding).
		 * @return True if the objects are colliding, false otherwise.
		 */
		virtual bool      isColliding(const Physical_Object &, Vector2DF &, Vector2DF &) const = 0;
		/**
		 * @brief Checks if the object is colliding with a circle.
		 * @param other The circle to check collision with.
		 * @param intersection_point The intersection point between the object and the circle (if they are colliding).
		 * @param normal The normal vector of the collision (if they are colliding).
		 * @return True if the object and the circle are colliding, false otherwise.
		 */
		virtual void      update(float dt=1,const Vector2DF& max_speed= maxVector2DF)          = 0;

	protected:
		// donne la normale à un point donné de l'objet physique
		//virtual void getNormal(Vector2DF)   = 0;

		Vector2DF centroid;
		Vector2DF speed, acceleration;

		/**
		 * @brief Define a the hitbox of the object.
		 * @param top_left The top-left corner of the bounding box.
		 * @param top_right The top-right corner of the bounding box.
		 * @param bottom_left The bottom-left corner of the bounding box.
		 * @param bottom_right The bottom-right corner of the bounding box.
		 */
		void setBoundingBox(const Point2DF ,const Point2DF ,const Point2DF ,const Point2DF );
		/**
		 * @brief Define a the hitbox of the object.
		 * @param hitbox The bounding box of the object.
		 */
		void setBoundingBox(const BoundingBox &);
		

		// Méthodes virtuelles pures
		/**
		 * @brief Compute the minimum bounding box of the object.
		 */
		virtual void                    computeMinimumBoundingBox()          = 0;
		/**
		 * @brief Projects the object onto a given axis. (for collision detection with SAT)
		 * @param axis The axis to project onto.
		 * @return A pair of floats representing the minimum and maximum projection values.
		 */
		virtual std::pair<float, float> project(const Vector2DF& axis) const = 0;

	private:

		/**
		 * @brief Updates the speed of the object.
		 * @param dt The time step to update the speed by.
		 * @param max_speed The maximum speed of the object.
		 */
		void updateSpeed(float dt=1,const Vector2DF& max_speed= maxVector2DF)       ;
		/**
		 * @brief Updates the acceleration of the object.
		 * @param dt The time step to update the acceleration by.
		 */
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