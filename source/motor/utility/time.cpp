#include "time.hpp"
using namespace motor;

Time::Time()
{
	oldtime = frametime = 1;	
}

void Time::update()
{
	unsigned int ticks = SDL_GetTicks();

	frametime = ticks - oldtime;
	oldtime = ticks;	
}

float Time::getFrameTime()
{
	return frametime / 1000.f;
}

float Time::get()
{
	return float(SDL_GetTicks()) / 1000.f;
}

//------------------------------------------------------------

Timer::Timer(int timeStep)
{
	step = timeStep;	
}

void Timer::Start()
{
	started = true;
	if(!paused)
		startTicks = SDL_GetTicks();
	else
	{
		startTicks = SDL_GetTicks() - pausedTicks;
		paused = false;
	}
}

void Timer::Stop()
{
	startTicks = 0;
	pausedTicks = 0;
	started = false;
}

void Timer::Pause()
{
	pausedTicks = SDL_GetTicks() - startTicks;
	paused = true;
}

void Timer::Restart()
{
	Stop();
	Start();
}

unsigned int Timer::Elapsed()
{
	if(!started)
		return 0;
	else if(!paused)
		return step * (SDL_GetTicks() - startTicks);
	else
		return step * (SDL_GetTicks() - (startTicks + pausedTicks));
}
