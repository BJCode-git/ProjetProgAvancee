#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <utility>    // Pour std::pair, std::make_pair, etc...
#include <algorithm>  // Pour std::min, std::max, find,sort, etc...

#include "debug.hpp"
#include "Physical_Engine/NumericVector.hpp"
#include "Physical_Engine/Physical_Object/Physical_Object.hpp"

class Convex_Polygon;

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
		/**
		 * @brief Default constructor for Circle.
		  @param pos The center position of the circle.
		 *@param r The radius of the circle.
		 */
		Circle(Vector2DF &pos, unsigned int r);
		Circle(Vector2DF pos,   unsigned int r);
		~Circle();

		/**
		 * @brief Sets the radius of the circle.
		 * @param radius The new radius of the circle.
		 */
		void setRadius(float radius);
		/**
		 * @brief Gets the radius of the circle.
		 * @return The radius of the circle.
		 */
		float getRadius() const;
		
		/**
		 *@brief force the circle to move by a given offset
		 *@param offset The offset to move the circle by.
		 */
		virtual void move(const Vector2DF&)                                               override;
		/**
		 *@brief update the circle's state by a given time step
		 *@param dt The time step to update the circle by.
		 *@param max_speed The maximum speed of the circle.
		 */
		virtual void update(float dt=1,const Vector2DF& max_speed= maxVector2DF)          override;
		/**
		 *@brief set the position of the circle
		 *@param pos The new position of the circle.
		 */
		virtual bool isColliding(const Physical_Object &, Vector2DF &, Vector2DF &) const override;
		/**
		 *@brief check if the circle is colliding with another circle
		 *@param other The other circle to check collision with.
		 *@param intersection_point The intersection point between the two circles (if they are colliding).
		 *@param normal The normal vector of the collision (if they are colliding).
		 *@return True if the circles are colliding, false otherwise.
		 */
		virtual bool isColliding(const Convex_Polygon &,  Vector2DF &, Vector2DF &) const;
		/**
		 *@brief check if the circle is colliding with a convex polygon
		 *@param other The other convex polygon to check collision with.
		 *@param intersection_point The intersection point between the circle and the convex polygon (if they are colliding).
		 *@param normal The normal vector of the collision (if they are colliding).
		 *@return True if the circle and the convex polygon are colliding, false otherwise.
		 */
		virtual bool isColliding(const Circle &,          Vector2DF &, Vector2DF &) const;

	protected:
	
		// Méthode pour la détection de collision par l'algorithme des axes séparateurs
		virtual std::pair<float, float> project(const Vector2DF& axis) const override;

	private:
		float radius;
		void computeMinimumBoundingBox() override;
};

#endif // CIRCLE_HPP