#include "Physical_Engine/Circle/Circle.hpp"
#include "Physical_Engine/Convex_Polygon/Convex_Polygon.hpp"

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
	// bottom_right = (x + r, y + r)
	// bottom_left = (x - r, y + r)
	setBoundingBox(  Point2DF({centroid[0] - radius, centroid[1] - radius}),
					 Point2DF({centroid[0] + radius, centroid[1] - radius}),
					 Point2DF({centroid[0] + radius, centroid[1] + radius}),
					 Point2DF({centroid[0] - radius, centroid[1] + radius}));
}

void Circle::update(float dt){
	Physical_Object::update(dt);
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