#ifndef _LOG_HPP
#define _LOG_HPP

#include <iostream>
#include <ostream>
using namespace std;

#include <SDL/SDL.h>

namespace motor
{
	class Log : public ostream
	{
		public:
			//template<typename T>
				template <class T> ostream &operator<<(const T &data)
				{
					cout << SDL_GetTicks() << data;
					return *this;
				}
	};
}
#endif
