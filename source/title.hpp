#ifndef _TITLE_HPP
#define _TITLE_HPP

#include "state.hpp"
#include "motor/graphics/image.hpp"
#include "motor/graphics/shader.hpp"
#include "motor/utility/time.hpp"
#include <GL/glut.h>
#include <cmath>
//#include <../glm/glm.hpp>
//#include <../glm/gtc/matrix_projection.hpp>  
//#include <../glm/gtc/matrix_transform.hpp> 

namespace motor
{
	class Title : public State
	{
		Image background;
		Image logo;

		Input *input;
		Window *window;

		bool loop;

		public:
		Title();
		int main(Window*, Input*, Time*);
		void init();
		void load();
		void unload();
		void update();
		void draw();
	};
}
#endif
