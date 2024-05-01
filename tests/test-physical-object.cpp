#include <cassert>
#include <exception>
#include <typeinfo>
#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath>
#include "Physical_Engine.hpp"
#include <indicators/cursor_control.hpp>
#include <indicators/progress_bar.hpp>

// Define a custom epsilon value for floating-point comparisons
constexpr float epsilon = 0.0001f;

// Define test macros
#define ASSERT_TRUE(expr)        if(!(expr)){std::cerr << "Erreur dans le test : " << #expr << std::endl;}
#define ASSERT_FALSE(expr)       if(expr) {std::cerr << "Erreur dans le test : " << #expr << std::endl;}
#define ASSERT_EQUAL(x, y)       if((x) != (y)){std::cerr << "Erreur dans le test : " << #x << " == " << #y << std::endl;}
#define ASSERT_FLOAT_EQUAL(x, y) if(std::abs((x) - (y)) > epsilon) {std::cerr << "Erreur dans le test : " << #x << " == " << #y << std::endl;}

// Import classes from your source file
// #include "../include/Physical_Object.hpp"

bool test_Vector(){

    // Test default constructor
    NumericVector<int, 3> v1;
    assert(v1[0] == 0);
    assert(v1[1] == 0);
    assert(v1[2] == 0);

    // Test constructor with value
    NumericVector<int, 3> v2(5);
    assert(v2[0] == 5);
    assert(v2[1] == 5);
    assert(v2[2] == 5);

    // Test constructor with initializer list
    NumericVector<int, 3> v3{1, 2, 3};
    assert(v3[0] == 1);
    assert(v3[1] == 2);
    assert(v3[2] == 3);

    // Test operator[]
    v3[0] = 10;
    assert(v3[0] == 10);

    // Test operator==
    NumericVector<int, 3> v4{1, 2, 3};
    ASSERT_FALSE(v3 == v4);

    // Test operator!=
    NumericVector<int, 3> v5{1, 2, 4};
    assert(v3 != v5);

    // Test operator+
    NumericVector<int, 3> v6 = v3 + v5;
    assert(v6[0] == 11);
    assert(v6[1] == 14);
    assert(v6[2] == 7);

    // Test operator-
    NumericVector<int, 3> v7 = v3 - v5;
    assert(v7[0] == 9);
    assert(v7[1] == 10);
    assert(v7[2] == -1);

    // Test operator*
    NumericVector<int, 3> v8 = v3 * 2;
    assert(v8[0] == 20);
    assert(v8[1] == 4);
    assert(v8[2] == 6);

    // Test operator/
    NumericVector<int, 3> v9 = v3 / 2;
    assert(v9[0] == 5);
    assert(v9[1] == 1);
    assert(v9[2] == 1);

    // Test scalarProduct
    int scalarProduct = v3.scalarProduct(v5);
    assert(scalarProduct == 15);

    // Test crossProduct
    NumericVector<int, 3> crossProduct = v3.crossProduct(v5);
    assert(crossProduct[0] == -2);
    assert(crossProduct[1] == 2);
    assert(crossProduct[2] == 0);

    // Test distance_square
    int distanceSquare = v3.distance_square(v5);
    assert(distanceSquare == 2);

    // Test distance
    double distance = v3.distance(v5);
    assert(distance == std::sqrt(2));

    // Test normalize
    v3.normalize();
    assert(v3[0] == 0);
    assert(v3[1] == 0);
    assert(v3[2] == 1);

    std::cout << "All tests passed!" << std::endl;

    return true;

}


bool test_BoundingBox(indicators::ProgressBar &bar,int origine ,int &increment, int &proportion){
    debug("test_BoundingBox");

    // Test case 1: Creating a bounding box
    BoundingBox bbox({0, 0}, {2, 0}, {0, 2}, {2, 2});
    ASSERT_TRUE(bbox.getCenter() == Point2DF(1.0));
    increment = 100 /4 * proportion/100;
    bar.set_progress(origine + increment);

    // Test case 2: Bounding box collision
    BoundingBox bbox1({0, 0}, {2, 0}, {0, 2}, {2, 2});
    BoundingBox bbox2({1, 1}, {3, 1}, {1, 3}, {3, 3});
    Vector2DF intersection_point, normal;
    ASSERT_TRUE(bbox1.isColliding(bbox2, intersection_point, normal));
    std::cout << "Collision check" <<std::endl;
    increment += 100 /4 * proportion/100;
    bar.set_progress(origine + increment);
    std::cout << "intersection point( "<<intersection_point[0]<<" ; "<<intersection_point[1]<<" )"<<std::endl;
    ASSERT_FLOAT_EQUAL(intersection_point[0], 1.5);
    increment += 100 /4 * proportion/100;
    bar.set_progress(origine + increment);
    ASSERT_FLOAT_EQUAL(intersection_point[1], 1.5);
    increment += 100 /4 * proportion/100;
    bar.set_progress(origine + increment);

    return true;
}

bool test_Physical_Object(indicators::ProgressBar &bar,int origine ,int &increment, int &proportion) {
    debug("test_Physical_Object");
    // Test case 1: Creating a physical object
    Circle c({0, 0}, 1);
    Physical_Object &obj(c);
    ASSERT_TRUE(obj.getPosition() == Point2DF({0.0, 0.0}));
    increment = 100 /9 * proportion/100;
    bar.set_progress(origine + increment);
    ASSERT_TRUE(obj.getSpeed() == Point2DF({0.0, 0.0}));
    increment += 100 /9 * proportion/100;
    bar.set_progress(origine + increment);
    ASSERT_TRUE(obj.getAcceleration() == Point2DF({0.0, 0.0}));
    increment += 100 /9 * proportion/100;
    bar.set_progress(origine + increment);

    // Test case 2: Setting and getting attributes
    obj.setPosition({1, 1});
    ASSERT_TRUE(obj.getPosition() == Point2DF(1));
    increment += 100 /9 * proportion/100;
    bar.set_progress(origine + increment);
    obj.setSpeed({2, 2});
    ASSERT_TRUE(obj.getSpeed() == Point2DF(2));
    increment += 100 /9 * proportion/100;
    bar.set_progress(origine + increment);
    obj.setAcceleration({3, 3});
    ASSERT_TRUE(obj.getAcceleration() == Point2DF(3));
    increment += 100 /9 * proportion/100;
    bar.set_progress(origine + increment);

    // Test case 3: Updating object state
    obj.update();
    ASSERT_TRUE(obj.getPosition() == Point2DF(3));
    increment += 100 /9 * proportion/100;
    bar.set_progress(origine + increment);

    // Test case 4: Breakable attribute
    obj.setBreakable(true, 2);
    ASSERT_TRUE(obj.isBreakable());
    increment += 100 /9 * proportion/100;
    bar.set_progress(origine + increment);
    ASSERT_EQUAL(obj.getLife(), 2);
    increment += 100 /9 * proportion/100;
    bar.set_progress(origine + increment);

    return true;

}

bool test_Convex_Polygon(indicators::ProgressBar &bar,int origine ,int &increment, int &proportion) {
    debug("test_Convex_Polygon");

    // Test case 1: Creating a convex polygon
    Polygon points = {{0, 0}, {2, 0},{2, 2}, {0, 2}};
    Convex_Polygon polygon(points);
    ASSERT_TRUE(polygon.getPosition() == Point2DF(1));
    increment = 100 /7 * proportion/100;

    // Test case 2: Inserting and removing points
    ASSERT_TRUE(polygon.pushPoint({3, 3}));
    increment += 100 /7 * proportion/100;
    bar.set_progress(origine + increment);
    ASSERT_EQUAL(polygon.getPoints().size(), 5);
    increment += 100 /7 * proportion/100;
    bar.set_progress(origine + increment);
    ASSERT_FALSE(polygon.removePoint({5, 5}));
    increment += 100 /7 * proportion/100;
    bar.set_progress(origine + increment);
    ASSERT_TRUE(polygon.removePoint({3, 3}));
    increment += 100 /7 * proportion/100;
    bar.set_progress(origine + increment);
    ASSERT_EQUAL(polygon.getPoints().size(), 4);
    increment += 100 /7 * proportion/100;
    bar.set_progress(origine + increment);

    // Test case 3: Updating polygon state
    polygon.setSpeed({1, 1});
    polygon.update();
    ASSERT_TRUE(polygon.getPosition() == Point2DF(2));
    increment += 100 /7 * proportion/100;
    bar.set_progress(origine + increment);

    return true;
}

bool test_Circle(indicators::ProgressBar &bar,int origine ,int &increment, int &proportion) {
    debug("test_Circle");

    // Test case 1: Creating a circle
    Circle circle({0, 0}, 2);
    ASSERT_TRUE(circle.getPosition() == Point2DF(0));
    increment = 100 /3 * proportion/100;
    ASSERT_EQUAL(circle.getRadius(), 2);
    increment += 100 /3 * proportion/100;

    // Test case 2: Updating circle state
    circle.setSpeed({2, 2});
    circle.update();
    ASSERT_TRUE(circle.getPosition() == Point2DF(2));
    increment += 100 /3 * proportion/100;

    return true;
}

bool test_collision_methods(indicators::ProgressBar &bar,int origine ,int &increment, int &proportion) {
    debug("test_collision_methods");

    // Test case 1: Convex_Polygon vs Convex_Polygon collision
    Polygon points1 = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
    Convex_Polygon polygon1(points1);
    Polygon points2 = {{1, 1}, {3, 1}, {3, 3}, {1, 3}};
    Convex_Polygon polygon2(points2);
    Vector2DF intersection_point, normal;
    ASSERT_TRUE(polygon1.isColliding(polygon2, intersection_point, normal));
    increment = 100 /9 * proportion/100;
    ASSERT_FLOAT_EQUAL(intersection_point[0], 1.5);
    increment += 100 /9 * proportion/100;
    ASSERT_FLOAT_EQUAL(intersection_point[1], 1.5);
    increment += 100 /9 * proportion/100;

    // Test case 2: Convex_Polygon vs Circle collision
    Circle circle({2, 2}, 1);
    ASSERT_TRUE(polygon1.isColliding(circle, intersection_point, normal));
    increment += 100 /9 * proportion/100;
    ASSERT_FLOAT_EQUAL(intersection_point[0], 1);
    increment += 100 /9 * proportion/100;
    ASSERT_FLOAT_EQUAL(intersection_point[1], 1);
    increment += 100 /9 * proportion/100;

    // Test case 3: Circle vs Circle collision
    Circle circle2({3, 3}, 1);
    ASSERT_TRUE(circle.isColliding(circle2, intersection_point, normal));
    increment += 100 /9 * proportion/100;
    ASSERT_FLOAT_EQUAL(intersection_point[0], 2);
    increment += 100 /9 * proportion/100;
    ASSERT_FLOAT_EQUAL(intersection_point[1], 2);
    increment += 100 /9 * proportion/100;

    return true;

}

int main() {

	std::cout << "Running tests..." << std::endl;

	indicators::show_console_cursor(false);

	// Create progress bar
	indicators::ProgressBar bar{
		indicators::option::BarWidth{50},
		indicators::option::Start{"["},
		indicators::option::Fill{"■"},
		indicators::option::Lead{"■"},
		indicators::option::Remainder{"-"},
		indicators::option::End{" ]"},
		indicators::option::PostfixText{"test_BoundingBox"},
		indicators::option::ForegroundColor{indicators::Color::cyan},
		indicators::option::FontStyles{std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}
	};


    // Run tests for each class and method

    uint8_t test_passed = 0;
    bool test_passed_ok = false;
    int increment = 0;
    int proportion =   20;
    try{
        //test_Vector();
	    bar.set_progress(0);
	    if(test_BoundingBox(bar,0,increment,proportion)){
	    	bar.set_option(indicators::option::PostfixText{"test_BoundingBox passed"});
            test_passed++;
        }
	    else
	    	bar.set_option(indicators::option::PostfixText{"test_BoundingBox failed"});
        
	    bar.set_progress(20);
	    if(test_Physical_Object(bar,0,increment,proportion)){
	    	bar.set_option(indicators::option::PostfixText{"test_Physical_Object passed"});
            test_passed++;
        }
        else
	    	bar.set_option(indicators::option::PostfixText{"test_Physical_Object failed"});
        
	    bar.set_progress(40);
	    if(test_Convex_Polygon(bar,0,increment,proportion)){
	    	bar.set_option(indicators::option::PostfixText{"test_Convex_Polygon passed"});
            test_passed++;
        }
        else
	    	bar.set_option(indicators::option::PostfixText{"test_Convex_Polygon failed"});
        
	    bar.set_progress(60);
	    if(test_Circle(bar,0,increment,proportion)){
	    	bar.set_option(indicators::option::PostfixText{"test_Circle passed"});
            test_passed++;
        }
	    else
	    	bar.set_option(indicators::option::PostfixText{"test_Circle failed"});
        
	    bar.set_progress(80);
	    if(test_collision_methods(bar,0,increment,proportion)){
	    	bar.set_option(indicators::option::PostfixText{"test_collision_methods passed"});
            test_passed++;
        }
	    else
	    	bar.set_option(indicators::option::PostfixText{"test_collision_methods failed"});
        
        bar.set_progress(100);
        bar.set_option(indicators::option::PostfixText{"Tests passed: " + std::to_string(test_passed) + "/5"});
    }catch(const std::exception &e){
        std::cerr << "Erreur !" << std::endl;
    }catch(const std::string &e){
        std::cerr << "Erreur !" << std::endl;
    }
    catch(...){
        std::exception_ptr p = std::current_exception();
        std::cerr <<(p ? p.__cxa_exception_type()->name() : "null") << std::endl;
        std::cerr << "Erreur !" << std::endl;
    }
	// Show cursor
	indicators::show_console_cursor(true);

	return 0;
}
