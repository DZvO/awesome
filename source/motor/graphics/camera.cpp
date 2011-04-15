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

void motor::Camera::moveGlo(float x, float y, float z, float distance)
{
	//viewMatrix[3].x += x * distance;
//	viewMatrix[3].y += y * distance;
	//viewMatrix[3].z += z * distance;
	//position += glm::vec3(x * distance, y * distance, z * distance);
	//position += glm::vec3(x * distance, 0, z * distance);
	//viewMatrix = glm::translate(glm::mat4(1.0f), position);
	moveLoc(x,y,z,distance);
}

void motor::Camera::moveLoc(float xDelta, float yDelta, float zDelta, float distance)
{	
	if(zDelta > 0)
	{
		float xrotrad, yrotrad;
		yrotrad = (rotation.y / 180.0 * M_PI);
		xrotrad = (rotation.x / 180.0 * M_PI);
		position.x += float(sin(yrotrad)) * zDelta;
		position.z -= float(cos(yrotrad)) * zDelta;
		//position.y -= float(sin(xrotrad)) * zDelta;
	}
	if(zDelta < 0)
	{
		float xrotrad, yrotrad;
		yrotrad = (rotation.y / 180.0 * M_PI);
		xrotrad = (rotation.x / 180.0 * M_PI);  
		position.x -= float(sin(yrotrad)) * abs(zDelta); 
		position.z += float(cos(yrotrad)) * abs(zDelta);
		//position.y += float(sin(xrotrad)) * abs(zDelta); 
	}

	if(xDelta > 0)
	{
		float yrotrad;
		yrotrad = (rotation.y / 180.0 * M_PI);
		position.x -= float(cos(yrotrad))  * xDelta;
		position.z -= float(sin(yrotrad)) * xDelta;
	}
	if(xDelta < 0)
	{
		float yrotrad;
		yrotrad = (rotation.y / 180.0 * M_PI);
		position.x += float(cos(yrotrad)) * abs(xDelta);
		position.z += float(sin(yrotrad)) * abs(xDelta);
	}
/*
	float deltaX = x * viewMatrix[0].x + y * viewMatrix[1].x + z * viewMatrix[2].x;
	//float deltaX = x * viewMatrix[0].x + y * viewMatrix[1].x + z * viewMatrix[2].x;
	//float deltaY = x * viewMatrix[0].y + y * viewMatrix[1].y + z * viewMatrix[2].y;
	float deltaZ = x * viewMatrix[0].z + y * viewMatrix[1].z + z * viewMatrix[2].z;
	//float deltaZ = x * viewMatrix[0].z + y * viewMatrix[1].z + z * viewMatrix[2].z;
	viewMatrix[3].x += deltaX * distance;
	//viewMatrix[3].y += deltaY * distance;
	viewMatrix[3].z += deltaZ * distance;

	*/
	//position += glm::vec3(deltaX * distance, deltaY * distance, deltaZ * distance);
	//position += glm::vec3(deltaX * distance, 0, deltaZ * distance);
}

void motor::Camera::rotateGlo(float x, float y, float z, float degrees)
{
	rotation += glm::vec3(x * degrees, y * degrees, z * degrees);
	if(rotation.x > 90) 
	{
		rotation.x = 90;
		//return;
	}
	if(rotation.x < -90) 
	{
		rotation.x = -90;
		//return;
	}

	//float dx=x*viewMatrix[0].x + y*viewMatrix[0].y + z*viewMatrix[0].z;
	//float dy=x*viewMatrix[1].x + y*viewMatrix[1].y + z*viewMatrix[1].z;
	//float dz=x*viewMatrix[2].x + y*viewMatrix[2].y + z*viewMatrix[2].z;

	//viewMatrix = glm::rotate(viewMatrix, degrees, glm::vec3(dx, dy, dz));
}

void motor::Camera::rotateLoc(float x, float y, float z, float degrees)
{
	rotation += glm::vec3(x * degrees, y * degrees, z * degrees);
	if(rotation.x > 90) 
	{
		rotation.x = 90;
		return;
	}
	if(rotation.x < -90) 
	{
		rotation.x = -90;
		return;
	}
	//viewMatrix = glm::rotate(viewMatrix, float(x), glm::vec3(1.0f, 0.0f, 0.0f));
	//viewMatrix = glm::rotate(viewMatrix, float(y), glm::vec3(0.0f, 1.0f, 0.0f));
}

void motor::Camera::think()
{
	if(rotation.y > 360) rotation.y -= 360;
	if(rotation.y < -360) rotation.y += 360;


	glm::mat4 tm = glm::mat4(1.0);
	//tm[0] = glm::vec4(viewMatrix[0].x, viewMatrix[1].x,  viewMatrix[2].x, 0);
	//tm[1] = glm::vec4(viewMatrix[0].y, viewMatrix[1].y,  viewMatrix[2].y, 0);
	//tm[2] = glm::vec4(viewMatrix[0].z, viewMatrix[1].z,  viewMatrix[2].z, 0);
	tm = glm::rotate(tm, rotation.x, glm::vec3(1, 0, 0));
	tm = glm::rotate(tm, rotation.y, glm::vec3(0, 1, 0));
	tm = glm::rotate(tm, rotation.z, glm::vec3(0, 0, 1));
	tm = glm::translate(tm, -glm::vec3(position.x, position.y + 0.5 + 1.75, position.z));

	//tm[3] = glm::vec4(	
			//-(viewMatrix[0].x * position.x + viewMatrix[0].y * position.y + viewMatrix[0].z * position.z),
			//-(viewMatrix[1].x * position.x + viewMatrix[1].y * position.y + viewMatrix[1].z * position.z),
			//-(viewMatrix[2].x * position.x + viewMatrix[2].y * position.y + viewMatrix[2].z * position.z),
			//1);
	//tm[3] = glm::vec4(	
			//-(viewMatrix[0].x * viewMatrix[3].x + viewMatrix[0].y * viewMatrix[3].y + viewMatrix[0].z * viewMatrix[3].z),
			//-(viewMatrix[1].x * viewMatrix[3].x + viewMatrix[1].y * viewMatrix[3].y + viewMatrix[1].z * viewMatrix[3].z),
			//-(viewMatrix[2].x * viewMatrix[3].x + viewMatrix[2].y * viewMatrix[3].y + viewMatrix[2].z * viewMatrix[3].z),
			//1);

	glUniformMatrix4fv(projectionMatrixUniform, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(viewMatrixUniform, 1, GL_FALSE, glm::value_ptr(tm));
	glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}
