#ifndef _INPUT_HPP
#define _INPUT_HPP

#include "motor/graphics/window.hpp"
#include "motor/utility/time.hpp"
#include <SDL/SDL.h>

namespace motor
{
	namespace Key
	{
		typedef enum Key
		{
			A = SDLK_a,
			B = SDLK_b,
			C = SDLK_c,
			D = SDLK_d,
			E = SDLK_e,
			F = SDLK_f,
			G = SDLK_g,
			H = SDLK_h,
			I = SDLK_i,
			J = SDLK_j,
			K = SDLK_k,
			L = SDLK_l,
			M = SDLK_m,
			N = SDLK_n,
			O = SDLK_o,
			P = SDLK_p,
			Q = SDLK_q,
			R = SDLK_r,
			S = SDLK_s,
			T = SDLK_t,
			U = SDLK_u,
			V = SDLK_v,
			W = SDLK_w,
			X = SDLK_x,
			Y = SDLK_y,
			Z = SDLK_z,

			UP = SDLK_UP,
			DOWN = SDLK_DOWN,
			LEFT = SDLK_LEFT,
			RIGHT = SDLK_RIGHT,

			F1 = SDLK_F1,
			F2 = SDLK_F2,
			F3 = SDLK_F3,
			F4 = SDLK_F4,
			F5 = SDLK_F5,
			F6 = SDLK_F6,
			F7 = SDLK_F7,
			F8 = SDLK_F8,
			F9 = SDLK_F9,
			F10 = SDLK_F10,
			F11 = SDLK_F11,
			F12 = SDLK_F12,

			NUMLOCK	= SDLK_NUMLOCK,
			CAPSLOCK= SDLK_CAPSLOCK,
			SCROLLOCK= SDLK_SCROLLOCK,

			RSHIFT = SDLK_RSHIFT,
			LSHIFT = SDLK_LSHIFT,

			RCTRL = SDLK_RCTRL,
			LCTRL = SDLK_LCTRL,

			RALT = SDLK_RALT,
			LALT = SDLK_LALT,

			RMETA = SDLK_RMETA,
			LMETA = SDLK_LMETA,

			LSUPER = SDLK_LSUPER,		/*  Left "Windows" key */
			RSUPER = SDLK_RSUPER,		/*  Right "Windows" key */

			ESCAPE = SDLK_ESCAPE,
			RETURN = SDLK_RETURN,
			COMMA = SDLK_COMMA,

			SPACE = SDLK_SPACE,
			BACKSPACE = SDLK_BACKSPACE,
			SEMICOLON = SDLK_SEMICOLON,
			DOT = SDLK_PERIOD
		} Key;
	}
	class Input
	{
		unsigned char *keyStates;	
		float *keyDelay;

		bool quitBool;
		bool resized;
		int x, y;

		public:
		Input();
		bool isPressed(Key::Key k);
		void resetKeyDelay(Key::Key k);
		float getKeyDelay(Key::Key k);
		int update(Time* time, Window *wndw = NULL); 	//pass a pointer to window here
		bool windowResized();
		bool resize(int* x, int* y);				//or handle window resizes yourself
		bool quit();
	};
}
#endif
