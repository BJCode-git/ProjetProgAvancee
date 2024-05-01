#include <SDL.h>
#include <Physical_Object.hpp>
#include <iostream>

#include <memory>



class Ball: public Graphical_Object, public Circle{
	public:

		Ball(int x, int y, int w, int h, Uint32 flags);
		~Ball();

	private:
		
};