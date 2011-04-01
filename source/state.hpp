#ifndef _STATE_HPP
#define _STATE_HPP
#include <iostream>

#include "motor/graphics/window.hpp"
#include "motor/io/input.hpp"

#include <GL/gl.h>
#include <SDL/SDL.h>

using namespace std;

namespace motor
{
	class State
	{
		protected:
			SDL_Surface *screen;
			int width, height;
		public:
			State();
			virtual int main(Window*, Input*);
			virtual void init();
			virtual void load();
			virtual	void unload();
			virtual void update();
			virtual void draw();
	};
}
#endif
