#ifndef _GAME_HPP
#define _GAME_HPP

#include "state.hpp"
#include "motor/graphics/image.hpp"
#include "motor/graphics/shader.hpp"
#include "motor/graphics/camera.hpp"
#include "motor/utility/log.hpp"
#include "motor/utility/time.hpp"
#include "motor/utility/settings.hpp"
#include "motor/io/input.hpp"

#include <motor/math/glm/glm.hpp>
#include <motor/math/glm/gtc/matrix_transform.hpp>
#include <motor/math/glm/gtx/projection.hpp>
#include <motor/math/glm/gtc/type_ptr.hpp>

using glm::vec3;

//#include <GL/glut.h>
#include <cmath>

#include "motor/graphics/chunk.hpp"
#include "motor/graphics/world.hpp"

#include "motor/math/aabb.hpp"

#include <iostream>
#include <ostream>
using namespace std;

namespace motor
{
	class Game : public State
	{
		public:
			Game();
			int main(Window*, Input*, Time*);
			void init();
			void load();
			void unload();
			void update();
			void draw();

		private:
			void handlePlayer();

			Image *tileset;

			Input *input;
			Window *window;
			Time *time;
			Camera *camera;

			World world;
			Settings settings;

			Shader *baseShader;

			bool loop;

			glm::mat4 projectionMatrix;
			glm::mat4 viewMatrix;
			glm::mat4 modelMatrix;


			glm::vec3 pos, acc, vel;
	};
}
#endif
