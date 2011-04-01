//Simplification for opening windows
#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

using namespace std;

namespace motor
{
	class Window
	{
		SDL_Surface *screen;
		public:
			int width, height;
			static const float near, far;
			Window();
			Window(int width, int height, string title = "Super Awesome!");
			void open(int width, int height, string title);
			void resize(int x, int y);
	};
}
#endif
