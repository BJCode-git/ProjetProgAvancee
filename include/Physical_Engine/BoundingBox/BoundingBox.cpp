#include "Physical_Engine/BoundingBox/BoundingBox.hpp"


/******************
 *   Projection    *
 ******************/
bool isOverlap(const std::pair<float, float>& proj1, const std::pair<float, float>& proj2){
	return proj1.first <= proj2.second && proj2.first <= proj1.second;
}

/******************
 *   BoundingBox  *
 ******************/

BoundingBox::BoundingBox():
	top_left({0, 0}),
	top_right({0, 0}),
	bottom_right({0, 0}),
	bottom_left({0, 0})
	
{
	debug("Création d'une bounding box par défaut");
}

BoundingBox::BoundingBox(const Point2DF top_left,const Point2DF top_right, const Point2DF bottom_right,
						 const Point2DF bottom_left):
	top_left(top_left),
	top_right(top_right),
	bottom_right(bottom_right),
	bottom_left(bottom_left)
	
{
	if(!isBoundingBox()){ 
		std::cerr << top_left << " " << top_right << " " << bottom_right << " " << bottom_left << " "  << std::endl;
		throw std::invalid_argument("Les points ne forment pas une bounding box");
	}
	debug("Création d'une bounding box");
}

BoundingBox::~BoundingBox(){
	debug("Destruction d'une bounding box");
}

bool BoundingBox::isBoundingBox() const{
	// Rq : on peut avoir une bounding box rectangulaire, mais qui est pivotée par rapport à l'axe des abscisses
	// On vérifie que les points forment bien une bounding box


	// On vérifie que les points soient bien ordonnés
	/*
	 * top_left    top_right
	 * +-----------+
	 * |           |
	 * |           |
	 * +-----------+
	 * bottom_left bottom_right
	 */
	/*
	if(top_left[1] > bottom_left[1] || top_right[1]   > bottom_right[1] 
	|| top_left[0] > top_right[0]   || bottom_left[0] > bottom_right[0]){
		debug("Les points ne sont pas ordonnés");
		return false;
	}
	*/

	// On vérifie que les côtés sont bien égaux (rectangle)

	float width_t  = top_left.distance_square(top_right);
	float width_b  = bottom_left.distance_square(bottom_right);
	float height_l = top_left.distance_square(bottom_left);
	float height_r = top_right.distance_square(bottom_right);

	if( width_t != width_b || height_l != height_r){
		std::cerr << width_t << " " << width_b << " " << height_l << " " << height_r << std::endl;
		debug("Les côtés ne sont pas égaux");
		return false;
	}

	// On vérifie que les côtés sont bien perpendiculaires
	Vector2DF up_side    = top_right    - top_left;
	Vector2DF left_side  = bottom_left  - top_left;
	Vector2DF down_side  = bottom_left  - bottom_right;
	Vector2DF right_side = bottom_right - top_right;

	if(up_side.scalarProduct(left_side) != 0 || left_side.scalarProduct(down_side) != 0
	|| down_side.scalarProduct(right_side) != 0 || right_side.scalarProduct(up_side) != 0){
		debug("Les côtés ne sont pas perpendiculaires");
		std::cerr << "top_left : "     << top_left     << std::endl 
				  << "top_right : "    << top_right    << std::endl 
				  << "bottom_right : " << bottom_right << std::endl
				  << "bottom_left : "  << bottom_left  << std::endl;

		std::cerr << "up_side : "    << up_side << std::endl 
				  << "left_side : "  << left_side << std::endl 
				  << "down_side : "  << down_side << std::endl 
				  << "right_side : " << right_side << std::endl;
		std::cerr << up_side.scalarProduct(left_side) << " " << left_side.scalarProduct(down_side) << " " 
				  << down_side.scalarProduct(right_side) << " " << right_side.scalarProduct(up_side) << std::endl;
		return false;
	}
	return true;

}

Point2DF BoundingBox::getCenter() const{
	// rq : la bouding box est un rectangle qui peut être pivoté par rapport à l'axe des abscisses
	// On renvoie le centre de la bounding box
	return {(top_left + top_right + bottom_left+ bottom_right) / 4};
}


std::pair<float, float> BoundingBox::project(const Vector2DF& axis) const {
	float min = std::numeric_limits<float>::max();
	float max = std::numeric_limits<float>::min();

	float points[] = { top_left.scalarProduct(axis),
					   top_right.scalarProduct(axis),
					   bottom_left.scalarProduct(axis),
					   bottom_right.scalarProduct(axis)};

	for (const auto& p : points) {
		min = std::min(min, p);
		max = std::max(max, p);
	}

	return {min, max};
}
/*
bool BoundingBox::isColliding(const BoundingBox& other, Vector2DF& intersection_point, Vector2DF& normal) const {
	Vector2DF axes[] = { Point2DF(top_right)         - Point2DF(top_left),
                         Point2DF(bottom_left)       - Point2DF(top_left),
                         Point2DF(other.top_right)   - Point2DF(other.top_left),
                         Point2DF(other.bottom_left) - Point2DF(other.top_left)};

    float min_overlap = std::numeric_limits<float>::max();
    Vector2DF smallest_axis;

    for (const auto& axis : axes) {
        auto [min1, max1] = project(axis);
        auto [min2, max2] = other.project(axis);

        // Vérification du chevauchement des projections
        if (max1 < min2 || max2 < min1) return false;
        
        // Calcul de l'overlap entre les intervalles de projection
        float overlap = std::min(max1, max2) - std::max(min1, min2);
        if (overlap < min_overlap) {
            min_overlap = overlap;
            smallest_axis = axis;
        }
    }

    // Calcul du point d'intersection sur l'autre boîte
    Vector2DF other_center = other.getCenter();
    intersection_point = other_center + smallest_axis * (min_overlap / 2);

    // Calcul de la normale orientée vers l'extérieur passant par le point d'intersection sur l'axe de la boîte intersectée
    normal = smallest_axis;

    return true;
}
*/

bool BoundingBox::isColliding(const BoundingBox& other, Vector2DF& intersection_point, Vector2DF& normal) const {
    float this_min_x = std::min({top_left[0], top_right[0], bottom_left[0], bottom_right[0]});
    float this_max_x = std::max({top_left[0], top_right[0], bottom_left[0], bottom_right[0]});
    float this_min_y = std::min({top_left[1], top_right[1], bottom_left[1], bottom_right[1]});
    float this_max_y = std::max({top_left[1], top_right[1], bottom_left[1], bottom_right[1]});

    float other_min_x = std::min({other.top_left[0], other.top_right[0], other.bottom_left[0], other.bottom_right[0]});
    float other_max_x = std::max({other.top_left[0], other.top_right[0], other.bottom_left[0], other.bottom_right[0]});
    float other_min_y = std::min({other.top_left[1], other.top_right[1], other.bottom_left[1], other.bottom_right[1]});
    float other_max_y = std::max({other.top_left[1], other.top_right[1], other.bottom_left[1], other.bottom_right[1]});

    bool x_overlap = (other_min_x <= this_max_x && this_min_x <= other_max_x);
    bool y_overlap = (other_min_y <= this_max_y && this_min_y <= other_max_y);

    if (x_overlap && y_overlap) 
        std::cout << "Collision ! " << std::endl;

    // Cette boucle ne semble pas nécessaire, je l'ai commentée
    
    do {
        intersection_point = {0, 0};
        normal = {0, 0};
    } while(0);

    return x_overlap && y_overlap;
}


void BoundingBox::move(Vector2DF offset){
	top_left += offset;
	top_right += offset;
	bottom_right += offset;
	bottom_left += offset;
}