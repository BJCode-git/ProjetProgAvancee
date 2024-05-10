#ifndef GRAPHICAL_OBJECT_HPP

#include <iostream>
#include <memory>
#include <chrono>
#include <ctime>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#include "Physical_Engine/Physical_Engine.hpp"


// Algrithme de Bresenham pour dessiner un cercle rempli
void drawFilledCircle(SDL_Renderer* renderer, float x, float y, float radius);

// Algorithme de Bresenham pour dessiner un cercle
void drawCircle(SDL_Renderer* renderer, float x, float y, float radius);

struct Color{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

constexpr Color BLUE  = Color(  0,   0, 255, 255);
constexpr Color RED   = Color(255,   0,   0, 255);
constexpr Color GREEN = Color(  0, 255,   0, 255);
constexpr Color BLACK = Color(  0,   0,   0, 255);
constexpr Color WHITE = Color(255, 255, 255, 255);

/*
template<typename T>
class Animation{

	public:

		Animation(): 
			running(false),
			last_clock(std::clock()),
			elapsed_time(0),
			duration(0)
		{}
		~Animation(){}

		void start(float duration, T start_value, T end_value){
			running = true;
			last_clock = std::clock();
			elapsed_time = 0;
			this->duration = duration;
			this->start_value = start_value;
			this->end_value = end_value;
		}

		void stop(){
			running = false;
			elapsed_time = 0;
		}

		update(){
			if(running){
				clock_t current_time = std::clock();
				// On calcule le temps écoulé depuis le dernier appel à update en ms
				float dt = (current_time - last_clock) / (float)CLOCKS_PER_SEC;
				last_clock = current_time;
				elapsed_time += std::min(dt, duration - elapsed_time);
				// On met à jour la valeur de l'animation
				T value = callback(start_value, end_value, dt);

				if(elapsed_time >= duration){
					running = false;
					elapsed_time = 0;
				}
			}
		}

	private:

		T (*callback)(T,float);
		T start_value;
		T end_value;

		bool running;
		std::clock_t last_clock; //ms
		float elapsed_time;      //ms
		float duration;          //ms
};
*/

class Graphical_Object{

	public:

		Graphical_Object(std::shared_ptr<Physical_Object> PhyObject,
						 std::shared_ptr<SDL_Texture> texture = std::shared_ptr<SDL_Texture>(nullptr));
		~Graphical_Object();

		virtual void draw(std::shared_ptr<SDL_Renderer> renderer) const = 0;

		int PhyObjLife() const;
		
		Color getColor() const;
		void setColor(Color color);

		std::shared_ptr<SDL_Texture> getTexture() const;
		void setTexture(std::shared_ptr<SDL_Texture> texture);


	protected:

		Color color;
		
		// On va dessiner l'objet selon sa forme et sa position
		std::shared_ptr<Physical_Object> PhyObject;
		std::shared_ptr<SDL_Texture> texture;
};


class GraphicalCircle : public Graphical_Object{

	public:

		GraphicalCircle(std::shared_ptr<Circle> Circle);
		~GraphicalCircle();

		virtual void draw(std::shared_ptr<SDL_Renderer> renderer) const override;

	private:
		std::shared_ptr<Circle> PhyObject;
};

class GraphicalPolygon : public Graphical_Object{

	public:

		GraphicalPolygon(std::shared_ptr<Convex_Polygon> Polygon);
		~GraphicalPolygon();

		virtual void draw(std::shared_ptr<SDL_Renderer> renderer) const override;

	private:
		// On va dessiner l'objet selon sa forme et sa position
		std::shared_ptr<Convex_Polygon> PhyObject;
};

class Graphical_Engine{

	public:

		Graphical_Engine(std::shared_ptr<SDL_Renderer> renderer, 
						int scene_width,
						int scene_height,
						uint16_t fps_limit = 60);
		~Graphical_Engine();

		void setRenderer(std::shared_ptr<SDL_Renderer> renderer);
		std::shared_ptr<SDL_Renderer> getRenderer() const;

		void start();
		void stop();

		void  operator()(){start();}

		void draw();
		void clear();

		void addObject(std::shared_ptr<Physical_Object> object,
					   std::shared_ptr<SDL_Texture> texture = std::shared_ptr<SDL_Texture>(nullptr));
		void addGraphicalPolygon(std::shared_ptr<Convex_Polygon> PhyObject,
								 std::shared_ptr<SDL_Texture> texture = std::shared_ptr<SDL_Texture>(nullptr));
		void addGraphicalCircle(std::shared_ptr<Circle> PhyObject,
								std::shared_ptr<SDL_Texture> texture = std::shared_ptr<SDL_Texture>(nullptr));
		void removeObject(size_t index);

		void setFPSLimit(uint16_t fps_limit);
		void getFPSLimit() const;
	

	private:
		std::vector<std::unique_ptr<Graphical_Object>> objects;
		std::shared_ptr<SDL_Renderer> renderer;

		uint16_t fps_limit;
		int window_width;
		int window_height;

		bool running;
};


#endif // GRAPHICAL_OBJECT_HPP