//Load images!
#ifndef _IMAGE_HPP
#define _IMAGE_HPP

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

namespace motor
{
	class Image
	{
		public:
			string path;
			GLuint data;

			int width;
			int height;
			int bpp;
		public:
			Image();
			~Image();
			Image(string path, GLuint data, int width, int height, int bpp);
			Image(string path);
			void print();
			void unload();
	};
}
#endif
