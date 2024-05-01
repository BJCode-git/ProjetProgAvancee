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
	
		virtual void computeMinimumBoundingBox() override;

	private:

		void rotatePoints(Polygon&, const Vector2DF &, float);
		int  findMinimumBoundingBox(const Polygon &);
		void updateMinimumBoundingBox(const Polygon &, int , Polygon& , float&);

		bool isConvex() const;
		Polygon points;

};

#endif // CONVEX_POLYGON_HPP