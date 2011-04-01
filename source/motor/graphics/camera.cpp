#include "camera.hpp"

motor::Camera::Camera(Input *inputPtr, Shader *shaderPtr)
{
	input = inputPtr;
	shader = shaderPtr;
	modelMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);

	projectionMatrixUniform = shader->getUniformLocation("projectionMatrix");
	viewMatrixUniform = shader->getUniformLocation("viewMatrix");
	modelMatrixUniform = shader->getUniformLocation("modelMatrix");
}

void motor::Camera::setPerspective(float fov, float aspectRatio, float near, float far)
{
	projectionMatrix = glm::perspective(fov, aspectRatio, near, far); //https://secure.wikimedia.org/wikipedia/en/wiki/Field_of_view
}

void motor::Camera::setPosition(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
	//viewMatrix = glm::translate(glm::mat4(1.0f), position);
}

void motor::Camera::movePosition(float xDelta, float yDelta, float zDelta)
{
	//position += glm::vec3(xDelta, yDelta, zDelta);
	if(zDelta > 0)
	{
			float xrotrad, yrotrad;
			yrotrad = (rotation.y / 180.0f * M_PI);
			xrotrad = (rotation.x / 180.0f * M_PI);
			position.x += float(sin(yrotrad)) * zDelta;
			position.z -= float(cos(yrotrad)) * zDelta;
			position.y -= float(sin(xrotrad)) * zDelta;
	}
	if(zDelta < 0)
	{
		float xrotrad, yrotrad;
		yrotrad = (rotation.y / 180.0f * M_PI);
		xrotrad = (rotation.x / 180.0f * M_PI);  
		position.x -= float(sin(yrotrad)) * abs(zDelta); 
		position.z += float(cos(yrotrad)) * abs(zDelta);
		position.y += float(sin(xrotrad)) * abs(zDelta); 
	}

	if(xDelta > 0)
	{
		float yrotrad;
		yrotrad = (rotation.y / 180.0f * M_PI);
		position.x -= float(cos(yrotrad)) * xDelta;
		position.z -= float(sin(yrotrad)) * xDelta;
	}
	if(xDelta < 0)
	{
		float yrotrad;
		yrotrad = (rotation.y / 180.0f * M_PI);
		position.x += float(cos(yrotrad)) * abs(xDelta);
		position.z += float(sin(yrotrad)) * abs(xDelta);
	}
	//viewMatrix = glm::translate(viewMatrix, glm::vec3(xDelta, yDelta, zDelta));
}

void motor::Camera::setRotation(float x, float y, float z)
{
	rotation = glm::vec3(x, y, z);
	//viewMatrix = glm::rotate(viewMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	//viewMatrix = glm::rotate(viewMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	//viewMatrix = glm::rotate(viewMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
}

void motor::Camera::moveRotation(float xDelta, float yDelta, float zDelta)
{
	rotation += glm::vec3(xDelta, yDelta, zDelta);
	//viewMatrix = glm::rotate(viewMatrix, xDelta, glm::vec3(1.0f, 0.0f, 0.0f));
	//viewMatrix = glm::rotate(viewMatrix, yDelta, glm::vec3(0.0f, 1.0f, 0.0f));
	//viewMatrix = glm::rotate(viewMatrix, zDelta, glm::vec3(0.0f, 0.0f, 1.0f));
}

void motor::Camera::think()
{
	if(rotation.y > 360) rotation.y -= 360;
	if(rotation.y < -360) rotation.y += 360;

	if(rotation.x > 90) rotation.x = 90;
	if(rotation.x < -90) rotation.x = -90;

	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	viewMatrix = glm::mat4(1.0f);
	viewMatrix *= rotationMatrix;
	viewMatrix = glm::translate(viewMatrix, -position);

	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}
