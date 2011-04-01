#ifndef _TIME_HPP
#define _TIME_HPP

#include <SDL/SDL.h>

namespace motor
{
	class Time
	{
		private:
			unsigned int oldtime;
			float frametime;

		public:
			Time();
			void update();
			float frameTime();
	};

	class Timer
	{
		private:
			unsigned int startTicks;
			unsigned int pausedTicks;
			int step;
			bool paused;
			bool started;
		public:
			Timer(int timeStep = 1);
			void Start();//starts the timer after it was initialized
			void Stop();//stops and resets the counter
			void Pause();//pauses until Start() is called again
			void Restart();//stops and starts again

			unsigned int Elapsed();
	};
}
#endif
