#ifndef _CAMERA_HPP
#define _CAMERA_HPP

#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/gl.h>

#include "motor/io/input.hpp"
#include "motor/graphics/shader.hpp"

#include <motor/math/glm/glm.hpp>
#include <motor/math/glm/gtc/matrix_transform.hpp>
#include <motor/math/glm/gtx/projection.hpp>
#include <motor/math/glm/gtc/type_ptr.hpp>

namespace motor
{
	class Camera
	{
		public:
			Camera(Input *inputPtr, Shader *shaderPtr);
			void setPerspective(float fov, float aspectRatio, float near, float far);

			void setPosition(float x, float y, float z);
			void movePosition(float xDelta, float yDelta, float zDelta);
			void setRotation(float x, float y, float z);
			void moveRotation(float xDelta, float yDelta, float zDelta);

			void think();

		private:
			Input *input;
			Shader *shader;

			glm::vec3 lookAt;
			glm::vec3 position;
			glm::vec3 rotation;
			glm::mat4 projectionMatrix;
			glm::mat4 viewMatrix;
			glm::mat4 modelMatrix;

			int projectionMatrixUniform;
			int viewMatrixUniform;
			int modelMatrixUniform;
	};
}
#endif
