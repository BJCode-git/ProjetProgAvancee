#ifndef GRAPHICAL_OBJECT_HPP
#define GRAPHICAL_OBJECT_HPP

#include <iostream>
#include <memory>
#include <chrono>
#include <ctime>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


#include "Physical_Engine/Physical_Object/Physical_Object.hpp"
#include "debug.hpp"


struct Color{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

constexpr Color BLUE  = Color(  0,   0, 255, SDL_ALPHA_OPAQUE);
constexpr Color RED   = Color(255,   0,   0, SDL_ALPHA_OPAQUE);
constexpr Color GREEN = Color(  0, 255,   0, SDL_ALPHA_OPAQUE);
constexpr Color BLACK = Color(  0,   0,   0, SDL_ALPHA_OPAQUE);
constexpr Color WHITE = Color(255, 255, 255, SDL_ALPHA_OPAQUE);

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

/**
 * @class Graphical_Object
 * @brief Represents a graphical object associated with a physical object.
 * 
 * The Graphical_Object class provides a base class for graphical objects in a graphical engine.
 * It contains methods for drawing the object, accessing and modifying its color and texture, and retrieving information about its associated physical object.
 */
class Graphical_Object{

	public:
		/**
		 * @brief Construct a new Graphical_Object object
		 * 
		 * @param PhyObject The physical object associated with the graphical object.
		 * @param texture  The texture of the graphical object.	
		 */
		Graphical_Object(std::shared_ptr<Physical_Object> PhyObject,
						 std::shared_ptr<SDL_Texture> texture = std::shared_ptr<SDL_Texture>(nullptr));
		~Graphical_Object();
	
		/**
		 * @brief Draws the graphical object on the specified renderer.
		 * 
		 * This method must be implemented by derived classes to define how the graphical object is drawn.
		 * 
		 * @param renderer The renderer to draw the object on.
		 */
		virtual void draw(std::shared_ptr<SDL_Renderer> renderer) const = 0;

		/**
		 * @brief Returns the remaining life of the associated physical object.
		 * 
		 * @return The remaining life of the associated physical object.
		 */
		int PhyObjLife() const;
		
		/**
		 * @brief Returns the color of the graphical object.
		 * 
		 * @return The color of the graphical object.
		 */
		Color getColor() const;
		
		/**
		 * @brief Sets the color of the graphical object.
		 * 
		 * @param color The new color of the graphical object.
		 */
		void setColor(Color color);

		/**
		 * @brief Returns the texture of the graphical object.
		 * 
		 * @return The texture of the graphical object.
		 */
		std::shared_ptr<SDL_Texture> getTexture() const;
		
		/**
		 * @brief Sets the texture of the graphical object.
		 * 
		 * @param texture The new texture of the graphical object.
		 */
		void setTexture(std::shared_ptr<SDL_Texture> texture);


	protected:

		Color color;
		
		// On va dessiner l'objet selon sa forme et sa position
		std::shared_ptr<Physical_Object> PhyObject;
		std::shared_ptr<SDL_Texture> texture;
};



#endif // GRAPHICAL_OBJECT_HPP