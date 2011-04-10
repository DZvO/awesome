#include "image.hpp"

motor::Image::Image()
{

}
motor::Image::Image(string path, GLuint data, int width, int height, int bpp)
{
	this->path = path;
	this->data = data;
	this->width = width;
	this->height = height;
	this->bpp = bpp;
}

motor::Image::Image(string path)
{
	SDL_Surface* surface = IMG_Load(path.c_str());

	GLuint texture;
	glPixelStorei(GL_UNPACK_ALIGNMENT,4);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	SDL_PixelFormat *format = surface->format;
	if (format->Amask)
	{
		//mip maps are for dynamically lowering quality, we always want bad quality 8)
		//gluBuild2DMipmaps(GL_TEXTURE_2D, 4, surface->w, surface->h, GL_RGBA,GL_UNSIGNED_BYTE, surface->pixels);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	}
	else
	{
		//gluBuild2DMipmaps(GL_TEXTURE_2D, 3, surface->w, surface->h, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
	}

	this->path = path;
	this->data = texture;
	this->width = surface->w;
	this->height = surface->h;
	this->bpp = format->BitsPerPixel;
	SDL_FreeSurface(surface);
}

void motor::Image::print()
{
	cout << path << " " << width << " " << height << endl;
}

void motor::Image::unload()
{
	glDeleteTextures(1, &data);
}

motor::Image::~Image()
{
	unload();
}
