#ifndef BOUDINGBOX_HPP
#define BOUDINGBOX_HPP

#include <utility>    // Pour std::pair, std::make_pair, etc...
#include <algorithm>  // Pour std::min, std::max, find,sort, etc...

#include "debug.hpp"
#include "Physical_Engine/NumericVector.hpp"

bool isOverlap(const std::pair<float, float>& proj1, const std::pair<float, float>& proj2);

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


#endif // BOUDINGBOX_HPP