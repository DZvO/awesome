#include "game.hpp"

motor::Game::Game()
{
	loop = true;
}

glm::vec2 rotate(glm::vec2 point, float angleDeg)
{
	float angle = angleDeg / 180.f * M_PI; //convert from degrees (0-360) to radians (0-2*PI)
	glm::vec2 rotPoint;
	rotPoint.x = point.x * cos(angle) - point.y * sin(angle);
	rotPoint.y = point.x * sin(angle) + point.y * cos(angle);
	return rotPoint;
}

ostream& operator<<(ostream& out, const glm::vec3& v)
{
	return out << "v3(" << v.x << "|" << v.y << "|" << v.z << ")";
}

ostream& operator<<(ostream& out, const motor::AABB& bb)
{
	return out << "AABB(" << bb.min << " - " << bb.max << ")";
}

double round(double r)
{
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

bool falling()
{
	return false;
}

float floorGetRest(float toFloor)
{
	return toFloor - floor(toFloor);
}

motor::AABB getBbOfBlock(vec3 p)
{
	return motor::AABB
		(
		 vec3(floor(p.x), floor(p.y), floor(p.z)),
		 vec3(ceil(p.x), ceil(p.y), ceil(p.z))
		);
}

//example: returns true if f=0.9, comparator=1, range=0.1
bool inRange(float f, float comparator, float range)
{
	if(abs(f - comparator) < range)
		return true;
	return false;
}

bool motor::Game::playerColliding()
{
/*	int minX = int(playerBox.min.x);
	int minY = int(playerBox.min.y);
	int minZ = int(playerBox.min.z);

	int maxX = int(playerBox.max.x);
	int maxY = int(playerBox.max.y);
	int maxZ = int(playerBox.max.z);

	for (int x = minX; x <= maxX; x++)
		for (int y = minY; y <= maxY; y++)
			for (int z = minZ; z <= maxZ; z++)
			{
				if(world.getBlock(x, y, z).type != BLOCK_AIR)
					return true;
			}

	return false;
	*/

	vec3 Position = pos;
	vec3 size = glm::vec3(.6, 1.6, .6);
	//int minX = Position.x - size.x / 2;
	//int minY = Position.y - size.y / 2;
	//int minZ = Position.z - size.z / 2;

	//int maxX = Position.x + size.x / 2;
	//int maxY = Position.y + size.y / 2;
	//int maxZ = Position.z + size.z / 2;
	//AABB    playerBox = AABB(vec3(nx - playerRadius, ny - playerHeight, nz - playerRadius), vec3(nx + playerRadius, ny, nz + playerRadius));
	int minX = pos.x - size.x / 2;
	int minY = pos.y - size.y;
	int minZ = pos.z - size.z / 2;

	int maxX = pos.x + size.x / 2;
	int maxY = pos.y;
	int maxZ = pos.z + size.z / 2;

	for (int x = minX; x <= maxX; x++)
		for (int y = minY; y <= maxY; y++)
			for (int z = minZ; z <= maxZ; z++)
			{
				if(world.getBlock(x, y, z).type != BLOCK_AIR)// world.getBlock(x, y, z).type != BLOCK_OOB)
				{
					cout << (int)world.getBlock(x, y, z).type << "\n";
					return true;
				}
			}

	return false;

}

void motor::Game::handleCollision(glm::vec3 deltaMove, float multiplierMove)
{
	//  /z
	// o----x
	// |
	// |y
	const float playerRadius = .35;
	const float playerHeight = 1.6;

	vec3 delta = (deltaMove * multiplierMove) + (vel * time->getFrameTime());
	//vec3 newPos = pos;
	vec3 oldPos = pos;

	//AABB    playerBox = AABB(vec3(nx - playerRadius, ny - playerHeight, nz - playerRadius), vec3(nx + playerRadius, ny, nz + playerRadius));
	//AABB oldPlayerBox(vec3(ox - playerRadius, oy - playerHeight, oz - playerRadius), vec3(ox + playerRadius, oy, oz + playerRadius));

	//TODO use aabbs for collision
	//			->check multiple nodes around the player -- check how minecraft does this
	//TODO get some acceleration in here?

	pos.x += delta.x;
	if(playerColliding())
	{
		pos.x -= delta.x;
		cout << "colliding x" << "\n";
	}

	pos.y += delta.y;
	if(playerColliding())
	{
		pos.y -= delta.y;
		//vel -= glm::dot(vel, vec3(0, 1, 0)) * vec3(0, 1, 0);
		//pos -= glm::dot(pos, vec3(0, 1, 0)) * vec3(0, 1, 0);
		//pos += glm::dot(oldPos, vec3(0, 1, 0)) * vec3(0, 1, 0);
		pos.y = floor(pos.y) + .6000;
		//newPos.y = floor(newPos.y) + ;
		if(vel.y < 0) vel.y = 0;
		cout << "colliding y " << int(pos.y - 1.6) << "\n";
	}
	else if(world.getBlock(pos.x, pos.y - 1.6, pos.z).type == BLOCK_AIR)
	{
		cout << "falling" << endl;
		vel.y = -(13.666f * 4 * time->getFrameTime() * 10.);
	}
	//{
		//vel.y = -(13.666f * 4 * time->getFrameTime() * 10.);
	//}

	pos.z += delta.z;
	if(playerColliding())
	{
		cout << "colliding z" << "\n";
		pos.z -= delta.z;
	}

	camera->setPosition(pos);

	/*	FOUND THE SOLUTION???

			position.X += velocity.X;
			if(colliding())
			position.X -= velocity.X;

			position.Y += velocity.Y;
			if(colliding())
			position.Y -= velocity.Y;

			position.Z += velocity.Z;
			if(colliding())
			position.Z -= velocity.Z;

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

*/
}

void motor::Game::handlePlayer()
{
	float multiplierMove = 0;
	float multiplierRotate = 0;

	if(input->isPressed(Key::LSHIFT))
	{
		multiplierMove = 1.5f;
		multiplierRotate = 1.5f;
	}
	else if(input->isPressed(Key::RCTRL))
	{
		multiplierMove = 0.1f;
	}
	else
	{
		multiplierMove = 5.4f;
		multiplierRotate = 5.0f;
	}

	multiplierMove *= time->getFrameTime();
	multiplierRotate *= time->getFrameTime() * 20;

	glm::vec3 deltaMove(0, 0, 0);

	if(input->isPressed(Key::COMMA) && !input->isPressed(Key::O))//w
	{
		glm::vec3 delta = glm::vec3(0, 0, -1); //forward vector
		glm::vec2 deltaXZ = rotate(glm::vec2(delta.x, delta.z), camera->rotation.y);
		delta = glm::vec3(deltaXZ.x, delta.y, deltaXZ.y);
		deltaMove += delta;
		deltaMove = glm::normalize(deltaMove);
	}
	if(input->isPressed(Key::O) && !input->isPressed(Key::COMMA))//S
	{
		glm::vec3 delta = glm::vec3(0, 0, 1); //backward vector
		glm::vec2 deltaXZ = rotate(glm::vec2(delta.x, delta.z), camera->rotation.y);
		delta = glm::vec3(deltaXZ.x, delta.y, deltaXZ.y);
		deltaMove += delta;
		deltaMove = glm::normalize(deltaMove);
	}
	if(input->isPressed(Key::A) && !input->isPressed(Key::E))//a
	{
		glm::vec3 delta = glm::vec3(-1, 0, 0); //left vector
		glm::vec2 deltaXZ = rotate(glm::vec2(delta.x, delta.z), camera->rotation.y);
		delta = glm::vec3(deltaXZ.x, delta.y, deltaXZ.y);
		deltaMove += delta;
		deltaMove = glm::normalize(deltaMove);
	}
	if(input->isPressed(Key::E) && !input->isPressed(Key::A))//d
	{
		glm::vec3 delta = glm::vec3(1, 0, 0); //right vector
		glm::vec2 deltaXZ = rotate(glm::vec2(delta.x, delta.z), camera->rotation.y);
		delta = glm::vec3(deltaXZ.x, delta.y, deltaXZ.y);
		deltaMove += delta;
		deltaMove = glm::normalize(deltaMove);
	}

	if(input->isPressed(Key::LEFT))
	{
		camera->moveRotation(glm::vec3(0, -multiplierRotate, 0));
	}
	if(input->isPressed(Key::RIGHT))
	{
		camera->moveRotation(glm::vec3(0, multiplierRotate, 0));
	}
	if(input->isPressed(Key::UP))
	{
		camera->moveRotation(glm::vec3(-multiplierRotate, 0, 0));
	}
	if(input->isPressed(Key::DOWN))
	{
		camera->moveRotation(glm::vec3(multiplierRotate, 0, 0));
	}
	//----------------------------------
	//
	handleCollision(deltaMove, multiplierMove);

	if(input->isPressed(Key::SEMICOLON))
	{
		//newPos.y += 1.f * multiplierMove;
		//newPos.y += .1f;
		//camera->setPosition(newPos);
		vel.y = +15.f;
		//pos.y += 1.f * multiplierMove;
	}
	if(input->isPressed(Key::DOT))
	{
		//newPos.y -= 1.f * multiplierMove;
		//newPos.y -= .1f;
		//camera->setPosition(newPos);
		vel.y = -15.f;
		//pos.y -= 1.f * multiplierMove;
	}
	//camera->setPosition(newPos);

	if(input->isPressed(Key::W) && input->getKeyDelay(Key::W) > .2f)
	{
		input->resetKeyDelay(Key::W);
		settings.printPosition = !settings.printPosition;
	}
	if(settings.printPosition)
	{
		cout << pos << " velY: " << vel.y << "\n";
	}

	if(input->isPressed(Key::BACKSPACE))
	{
		world.setBlock(int(pos.x) + 1, int(pos.y), int(pos.z), BLOCK_AIR);
		world.setBlock(int(pos.x) - 1, int(pos.y), int(pos.z), BLOCK_AIR);
		world.setBlock(int(pos.x) + 1, int(pos.y) - 1, int(pos.z), BLOCK_AIR);
		world.setBlock(int(pos.x) - 1, int(pos.y) - 1, int(pos.z), BLOCK_AIR);

		world.setBlock(int(pos.x), int(pos.y), int(pos.z) + 1, BLOCK_AIR);
		world.setBlock(int(pos.x), int(pos.y), int(pos.z) - 1, BLOCK_AIR);
		world.setBlock(int(pos.x), int(pos.y) - 1, int(pos.z) + 1, BLOCK_AIR);
		world.setBlock(int(pos.x), int(pos.y) - 1, int(pos.z) - 1, BLOCK_AIR);

		//world.setBlock(int(pos.x), int(pos.y - 1.6) - 1, int(pos.z), BLOCK_AIR);

		world.recalculateChunck(int(fabs(pos.x)), int(fabs(pos.y)), int(fabs(pos.z)));
		world.recalculateChunck(int(fabs(pos.x)) - 16, int(fabs(pos.y)), int(fabs(pos.z)));
		world.recalculateChunck(int(fabs(pos.x)) + 16, int(fabs(pos.y)), int(fabs(pos.z)));
		world.recalculateChunck(int(fabs(pos.x)), int(fabs(pos.y)), int(fabs(pos.z)) + 16);
		world.recalculateChunck(int(fabs(pos.x)), int(fabs(pos.y)), int(fabs(pos.z)) - 16);

		world.recalculateChunck(int(fabs(pos.x)) - 16, int(fabs(pos.y)), int(fabs(pos.z)) + 16);
		world.recalculateChunck(int(fabs(pos.x)) - 16, int(fabs(pos.y)), int(fabs(pos.z)) - 16);
		world.recalculateChunck(int(fabs(pos.x)) + 16, int(fabs(pos.y)), int(fabs(pos.z)) + 16);
		world.recalculateChunck(int(fabs(pos.x)) + 16, int(fabs(pos.y)), int(fabs(pos.z)) - 16);
	}

}

int motor::Game::main(Window *wndw, Input *inp, Time *tt)
{
	window = wndw;
	input = inp;
	time = tt;

	cout << endl;

	float oldTime = time->get();
	world.load(8, 8, 8, 16, 16, 16); // 128
	world.generate();
	cout << "world generation took " << time->get() - oldTime << " seconds" << endl;
	cout << endl;

	glActiveTexture(GL_TEXTURE0);
	tileset = new Image("data/tileset.png");

	baseShader = new motor::Shader();
	baseShader->init();

	baseShader->attachVertexShader("data/base.vert");
	baseShader->attachFragmentShader("data/base.frag");
	baseShader->compile();

	int texUniform;
	texUniform = baseShader->getUniformLocation("texture");

	int positionAttrib;
	int texcoordAttrib;
	positionAttrib = baseShader->getAttributeLocation("position");
	texcoordAttrib = baseShader->getAttributeLocation("texcoord");

	baseShader->activate();

	camera = new Camera(input, baseShader);
	camera->setPerspective(45.0f, float(window->width) / float(window->height), window->near, window->far);
	camera->position = glm::vec3(0, 0, 0);

	cout << endl;

	glUniform1i(texUniform, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tileset->data);

	//	glPolygonMode(GL_FRONT, GL_LINE);

	pos = vel = acc = glm::vec3(0, 0, 0);

	pos = glm::vec3(0.5, 15, 0.5);
	camera->position = pos;
	vec3 rot = glm::vec3(0, 90, 0);
	camera->rotation = rot;
	settings.printPosition = false;

	plot.addNode("Velocity", false);

	while(loop)
	{
		time->update();
		input->update(time, window);//, time);


		if(input->quit())
			loop = false;
		if(input->windowResized())
		{
			cout << "handled!" << window->width << " " << window->height << endl;
			camera->setPerspective(45.0f, float(window->width) / float(window->height), 0.3f, window->far); 
		}

		if(input->isPressed(Key::H) && input->getKeyDelay(Key::H) > .5f)
		{
			input->resetKeyDelay(Key::H);
			settings.holdPosition = !settings.holdPosition;
		}
		if(!settings.holdPosition)
			handlePlayer();

		if(input->isPressed(Key::R) && input->getKeyDelay(Key::R) > .5f)
		{
			input->resetKeyDelay(Key::R);
			world.generate();
			camera->position = glm::vec3(0.5, 20, 0.5);
			cout << "regenerating" << endl;
		}

		camera->think();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		world.draw(positionAttrib, texcoordAttrib);
		SDL_GL_SwapBuffers();
	}
	return 0;
}
void motor::Game::update()
{

}

void motor::Game::draw()
{

}

void motor::Game::init()
{

}

void motor::Game::load()
{

}

void motor::Game::unload()
{

}

motor::Game::~Game()
{
	plot.close();

	cout << endl << "bye" << endl;
}
