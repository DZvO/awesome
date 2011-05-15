#ifndef _PLAYER_HPP
#define _PLAYER_HPP
#include <iostream>
using namespace std;

#include <motor/math/aabb.hpp>
#include <motor/utility/time.hpp>
#include <motor/graphics/camera.hpp>

#include <motor/math/glm/glm.hpp>
using glm::vec3;

namespace motor
{
	class Player
	{
		public:
			const vec3& position;
			const vec3& rotation;
			vec3 velocity;
			unsigned int life;

			Player(Time* time, Camera *cam);
			bool addVelocity(glm::vec3 vel);

		private:
			AABB boundingBox;
			static const float radius;
			static const float height;
			bool collides();
			Time* time;
			Camera* camera;
	};
}

#endif
