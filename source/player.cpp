#include "player.hpp"

const float motor::Player::radius = .35f;
const float motor::Player::height = 1.6f;

motor::Player::Player(Time *time, Camera *camera) : position(camera->position), rotation(camera->rotation)
{
	this->time = time;
	this->camera = camera;
	life = 16;
	velocity = glm::vec3(0, 0, 0);
}

/*bool motor::Player::collides()
{
	vec3 delta = (deltaMove * multiplierMove) + (vel * time->getFrameTime());
	vec3 newPos = pos;
	vec3 oldPos = pos;

	const float& nx = newPos.x; const float& ny = newPos.y; const float& nz = newPos.z;
	const float& ox = oldPos.x; const float& oy = oldPos.y; const float& oz = oldPos.z;

	AABB    playerBox(vec3(nx - playerRadius, ny - playerHeight, nz - playerRadius), vec3(nx + playerRadius, ny, nz + playerRadius));
	AABB oldPlayerBox(vec3(ox - playerRadius, oy - playerHeight, oz - playerRadius), vec3(ox + playerRadius, oy, oz + playerRadius));


	bool colliding()
	{
		int minX = Position.X - size.X / 2;
		int minY = Position.Y - size.Y / 2;
		int minZ = Position.Z - size.Z / 2;

		int maxX = Position.X + size.X / 2;
		int maxY = Position.Y + size.Y / 2;
		int maxZ = Position.Z + size.Z / 2;

		for (int x = minX; x <= maxX; x++)
			for (int y = minY; y <= maxY; y++)
				for (int z = minZ; z <= maxZ; z++)
				{
					if(blockType[x, y, z] != 0)
						return true;
				}

		return false;
	}

}
*/
