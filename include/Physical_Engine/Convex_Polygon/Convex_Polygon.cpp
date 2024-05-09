#include "Physical_Engine/Convex_Polygon/Convex_Polygon.hpp"
#include "Physical_Engine/Circle/Circle.hpp"

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
	if (index >= points.size()) return false;
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


void Convex_Polygon::update(float dt){

	Physical_Object::update(dt);

	// On met à jour les positions des points du polygone
	for (auto& p : points) {
		p[0] += speed[0]*dt;
		p[1] += speed[1]*dt;
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
