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
		Circle(Vector2DF & pos, unsigned int r);
		Circle(Vector2DF pos,   unsigned int r);
		~Circle();

		void setRadius(float radius);
		float getRadius() const;
		
		virtual void move(const Vector2DF&)                                               override;
		virtual void update(float dt=1,const Vector2DF& max_speed= maxVector2DF)               override;
		virtual bool isColliding(const Physical_Object &, Vector2DF &, Vector2DF &) const override;
		virtual bool isColliding(const Convex_Polygon &,  Vector2DF &, Vector2DF &) const;
		virtual bool isColliding(const Circle &,          Vector2DF &, Vector2DF &) const;

	protected:
	
		// Méthode pour la détection de collision par l'algorithme des axes séparateurs
		virtual std::pair<float, float> project(const Vector2DF& axis) const override;

	private:
		float radius;
		void computeMinimumBoundingBox() override;
};

#endif // CIRCLE_HPP