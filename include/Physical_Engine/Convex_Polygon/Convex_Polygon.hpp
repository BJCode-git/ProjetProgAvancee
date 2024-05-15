#ifndef CONVEX_POLYGON_HPP
#define CONVEX_POLYGON_HPP

#include <vector>     // Pour std::vector
#include <utility>    // Pour std::pair, std::make_pair, etc...
#include <algorithm>  // Pour std::min, std::max, find,sort, etc...


#include "debug.hpp"
#include "Physical_Engine/NumericVector.hpp"
#include "Physical_Engine/Physical_Object/Physical_Object.hpp"


class Circle;

/**
 * @class Convex_Polygon
 * @brief Represents a convex polygon in a 2D space.
 * 
 * The Convex_Polygon class is a derived class of Physical_Object and represents a convex polygon
 * in a 2D space. It provides methods for manipulating and querying the polygon's points, as well
 * as performing collision detection with other objects.
 */

 // Polygone 2D
using Polygon  = std::vector<Point2DF>;
class Convex_Polygon : public Physical_Object{
	public:
		/**
		 * @brief Default constructor for Convex_Polygon.
		  @param an array of points
		 */
		Convex_Polygon(const Polygon &);
		/**
		 * @brief Constructor for Convex_Polygon.
		 * @param an initializer list of points
		 */
		Convex_Polygon(std::initializer_list<Point2DF> list);
		/**
		 * @brief Destructor for Convex_Polygon.
		 */
		~Convex_Polygon();

		/**
		 * @brief Adds a point to the polygon.
		 * @param point The point to add to the polygon.
		 * @return True if the point was added successfully, false otherwise.
		 */
		bool pushPoint(Point2DF point);
		/**
		 * @brief Inserts a point at a specific index in the polygon.
		 * @param index The index at which to insert the point.
		 * @param point The point to insert into the polygon.
		 * @return True if the point was inserted successfully, false otherwise.
		 */
		bool insertPoint(unsigned int, Point2DF);

		/**
		 * @brief Removes a point from the polygon.
		 * @param point The point to remove from the polygon.
		 * @return True if the point was removed successfully, false otherwise.
		 */
		bool removePoint(Point2DF);
		/**
		 * @brief Removes a point from the polygon at a specific index.
		 * @param index The index of the point to remove.
		 * @return True if the point was removed successfully, false otherwise.
		 */
		bool removePoint(unsigned int);

		/**
		 * @brief Gets the points of the polygon.
		 * @return The points of the polygon.
		 */
		const Polygon& getPoints() const;
		
		/**
		 * @brief force the polygon to move by a given offset
		 * @param offset The offset to move the polygon by.
		 */
		virtual void      move(const Vector2DF&)                                              override;
		/**
		 * @brief update the polygon's state by a given time step
		 * @param dt The time step to update the polygon by.
		 * @param max_speed The maximum speed of the polygon.
		 */
		virtual void      update(float dt=1,const Vector2DF& max_speed=maxVector2DF)          override;
		/**
		 * @brief set the position of the polygon
		 * @param pos The new position of the polygon.
		 */
		virtual void      setPosition(Vector2DF)                                              override;
		/**
		 * @brief get the position of the polygon
		 * @return The position of the polygon.
		 */
		virtual Vector2DF getPosition()                                                 const override;
		/**
		 * @brief check if the polygon is colliding with another object
		 * @param other The other object to check collision with.
		 * @param intersection_point The intersection point between the two objects (if they are colliding).
		 * @param normal The normal vector of the collision (if they are colliding).
		 * @return True if the objects are colliding, false otherwise.
		 */
		virtual bool      isColliding(const Physical_Object &,Vector2DF &,Vector2DF &)  const override;
		/**
		 * @brief check if the polygon is colliding with another convex polygon
		 * @param other The other convex polygon to check collision with.
		 * @param intersection_point The intersection point between the two convex polygons (if they are colliding).
		 * @param normal The normal vector of the collision (if they are colliding).
		 * @return True if the convex polygons are colliding, false otherwise.
		 */
		virtual bool      isColliding(const Convex_Polygon &,Vector2DF &,Vector2DF &)   const;
		/**
		 * @brief check if the polygon is colliding with a circle
		 * @param other The circle to check collision with.
		 * @param intersection_point The intersection point between the polygon and the circle (if they are colliding).
		 * @param normal The normal vector of the collision (if they are colliding).
		 * @return True if the polygon and the circle are colliding, false otherwise.
		 */
		virtual bool      isColliding(const Circle &,Vector2DF &,Vector2DF &)           const;

		// Method use by separation axis theorem
		/**
		 * @brief Gets the edges of the polygon.
		 * @return The edges of the polygon.
		 */
		std::vector<Vector2DF>          getEdges()                                      const;
	protected:

		/**
		 * @brief Projects a vecto onto an axis.
		 * @param The vector to project.
		 * @param  The axis to project onto.
		 * @return The projection of the vecto onto the axis.
		 */
		Vector2DF                       projectPoint(const Vector2DF&, const Vector2DF&) const;
		/**
		 * @brief Projects the polygon onto an axis.
		 * @param axis The axis to project onto.
		 * @return A pair of floats representing the minimum and maximum projection values.
		 */
		virtual std::pair<float, float> project(const Vector2DF& )                       const override;

		/**
		 * @brief Computes the centroid of the polygon.
		 */
		void computeCentroid();
	
		/**
		 * @brief Computes the minimum bounding box of the polygon.
		 */
		virtual void computeMinimumBoundingBox() override;

	private:

		/**
		 * @brief Rotates the points of the polygon around a given point. (usd by the computeMinimumBoundingBox method)
		 * @param The point to rotate the polygon around.
		 * @param The angle to rotate the polygon by.
		 */
		void rotatePoints(Polygon&, const Vector2DF &, float);
		/**
		 * @brief Finds the minimum bounding box of the polygon. (usd by the computeMinimumBoundingBox method)
		 * @param The polygon to find the minimum bounding box of.
		 * @return The minimum bounding box of the polygon.
		 */
		int  findMinimumBoundingBox(const Polygon &);
		/**
		 * @brief Updates the minimum bounding box of the polygon. (usd by the computeMinimumBoundingBox method)
		 * @param The polygon to update the minimum bounding box of.
		 * @param The index of the point to update the minimum bounding box of.
		 * @param The minimum bounding box of the polygon.
		 * @param The minimum area of the minimum bounding box.
		 */
		void updateMinimumBoundingBox(const Polygon &, int , Polygon& , float&);

		/**
		 * @brief Checks if the polygon is convex.
		 * @return True if the polygon is convex, false otherwise.
		 */
		bool isConvex() const;
		
		Polygon points;

};

#endif // CONVEX_POLYGON_HPP