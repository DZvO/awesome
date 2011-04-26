#include "aabb.hpp"

motor::AABB::AABB()
{
	min = max = glm::vec3(0,0,0);
}

motor::AABB::AABB(glm::vec3 min, glm::vec3 max)
{
	this->min = min;
	this->max = max;
}

bool motor::AABB::intersects(AABB& aabb)
{
	if(aabb.max.x <= this->min.x || aabb.min.x >= this->max.x)
		return false;
	if(aabb.max.y <= this->min.y || aabb.min.y >= this->max.y)
		return false;
	return aabb.max.z > min.z && aabb.min.z < max.z;
}

bool motor::AABB::intersects(AABB& aabb1, AABB& aabb2)
{
	return aabb1.intersects(aabb2);
}

glm::vec3 motor::AABB::center()
{
	return min + glm::vec3((max.x - min.x) / 2, (max.y - min.y) / 2, (max.z - min.z) / 2);
}
