#include "input.hpp"

motor::Input::Input()
{
	keystates = SDL_GetKeyState(NULL);
	quitBool = false;
	resized = false;
	x = y = 0;
}

bool motor::Input::isPressed(Key::Key k)
{
	return bool(keystates[k]);
}

int motor::Input::update(Window *wndw)
{
	keystates = SDL_GetKeyState(NULL);
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if((event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q)) || event.type == SDL_QUIT)
			quitBool = true;
		if(event.type == SDL_VIDEORESIZE)
		{
			resized = true;
			x = event.resize.w;
			y = event.resize.h;
			if(wndw != NULL)
			{
				wndw->resize(x, y);
			}
		}
	}
	return 0;
}

bool motor::Input::windowResized()
{
	bool temp = resized;
	resized = false;
	return temp;
}

bool motor::Input::resize(int* x, int* y)
{
	if(resized)
	{
		resized = false;//handled
		*x = this->x;
		*y = this->y;
		return true;
	}
	return false;//no resize handled
}

bool motor::Input::quit()
{
	return quitBool;
}
