#include "game.hpp"

motor::Game::Game()
{
	loop = true;
}

void motor::Game::handleCamera()
{
	float multiplierMove;
	float multiplierRotate;

	if(input->isPressed(Key::LSHIFT))
	{
		multiplierMove = 0.05f;
		multiplierRotate = 1.5f;
	}
	else if(input->isPressed(Key::RCTRL))
	{
		multiplierMove = 0.01f;
	}
	else
	{
		multiplierMove = 0.8f;
		multiplierRotate = 4.0f;
	}

	if(input->isPressed(Key::COMMA))
		cam->moveLoc(0, 0, multiplierMove, -1);
	if(input->isPressed(Key::O))
		cam->moveLoc(0, 0, -multiplierMove, -1);
	if(input->isPressed(Key::A))
		cam->moveLoc(multiplierMove, 0, 0, -1);
	if(input->isPressed(Key::E))
		cam->moveLoc(-multiplierMove, 0, 0, -1);

	if(input->isPressed(Key::LEFT))
		cam->rotateGlo(0, multiplierRotate, 0, -1);
	//cam->rotateGlo(0, 1, 0, multiplierRotate);
	if(input->isPressed(Key::RIGHT))
		cam->rotateGlo(0, -multiplierRotate, 0, -1);
	//cam->rotateGlo(0, -1, 0, multiplierRotate);
	if(input->isPressed(Key::UP))
		cam->rotateLoc(multiplierRotate, 0, 0, -1);
	//cam->rotateLoc(multiplierRotate, 0, 0, 1);
	if(input->isPressed(Key::DOWN))
		cam->rotateLoc(-multiplierRotate, 0, 0, -1);
	//cam->rotateLoc(-multiplierRotate, 0, 0, 1);
}

void printVector(glm::vec3 v)
{
	cout << "(" << v.x << " " << v.y << " " << v.z << ")";
}

double round(double r)
{
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}

bool falling()
{
	return false;
}

int motor::Game::main(Window *wndw, Input *inp, Time *tt)
{
	window = wndw;
	input = inp;
	time = tt;

	cout << endl;

	World world;
	float oldTime = time->get();
	world.load(12, 12, 12, 16, 16, 16); // 128
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

	cam = new Camera(input, baseShader);
	cam->setPerspective(45.0f, float(window->width) / float(window->height), window->near, window->far);
	cam->position = glm::vec3(0, 0, 0);

	cout << endl;

	glUniform1i(texUniform, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tileset->data);

	//	glPolygonMode(GL_FRONT, GL_LINE);

	glm::vec3 pos, acc, vel;
	pos = glm::vec3(0, 10, 0);

	float countOfMeasures = 0;
	float measures = 0;
	float average = 0;

	while(loop)
	{
		time->update();
		input->update(time, window);//, time);


		if(input->quit())
			return 0;
		if(input->windowResized())
		{
			cout << "handled!" << window->width << " " << window->height << endl;
			cam->setPerspective(45.0f, float(window->width) / float(window->height), 0.3f, window->far); 
		}
		handleCamera();

		//cout << endl;
		pos = cam->position;
		//cout << int(world.getBlock((int)pos.x, (int)pos.y - 2, (int)pos.z).type) << " block pos " << (int)pos.y << endl;

		if(world.getBlock(round(pos.x), int(pos.y), round(pos.z + 0.5f)).type == BLOCK_AIR)
		{
			//acc.y = -111.12345f;
			vel.y = -1.12345f;
		}

		if(world.getBlock(round(pos.x), round(pos.y), round(pos.z + 1.75f)).type != BLOCK_AIR)//TODO Why 1.75?
		{
			//acc.y = 0.f;
			//if(fabs(round(pos.y)) < 0.2f || fabs(round(pos.y)) > 0.2f)
			//pos.y = floor(pos.y + 0.5f);
			//cout << (pos.y) - floor(pos.y) << endl;
			if((pos.y) - floor((pos.y)) < 0.1f)
			{
				vel.y = 0.f;
				pos.y = round(pos.y);
			}
		}

		//if(falling())
		//vel.y -= 2.f;
		if(input->isPressed(Key::W) && input->getKeyDelay(Key::W) > .05f)
		{
			input->resetKeyDelay(Key::W);
			printVector(pos);
			cout << endl;
		}

		//cout << input->getKeyDelay(Key::SPACE) << endl;
		if(input->isPressed(Key::SPACE) && input->getKeyDelay(Key::SPACE) > .6f && (world.getBlock(round(pos.x), round(pos.y), round(pos.z + 1.75f)).type != BLOCK_AIR))
		{
			input->resetKeyDelay(Key::SPACE);
			vel += glm::vec3(0.0f, 52.123f, 0.0f);
		}

		//vel += acc * time->getFrameTime();
		pos += vel * time->getFrameTime();

		acc *= 0.8f;
		vel *= 0.8f;

		cam->position = pos;

		cam->think();

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

//positionAttrib = baseShader->getAttributeLocation("position");
//texcoordAttrib = baseShader->getAttributeLocation("texcoord");
//or just bind them to a location
//glBindAttribLocation(baseShader->getProgram(), 0, "position");
//glBindAttribLocation(baseShader->getProgram(), 4, "texcoord");
/*unsigned int vertexBuffer;
	unsigned int elementBuffer;
	void init_buffers()
	{
	GLsizei const VertexCount = 4;
	GLsizeiptr const VertexSize = VertexCount * sizeof(vertex);
	vertex const VertexData[VertexCount] =
	{
	vertex(glm::vec3(-1.0f,-1.0f, 5.0f), glm::vec2(0.0f, 1.0f)),//lower left
	vertex(glm::vec3( 1.0f,-1.0f, 0.0f), glm::vec2(1.0f, 1.0f)),//lower right
	vertex(glm::vec3( 1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),//upper right
	vertex(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f))//upper left
	};

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	struct vertex
	{
	vertex
	(
	glm::vec3 const & Position,
	glm::vec2 const & Texcoord
	) :
	Position(Position),
	Texcoord(Texcoord)
	{}

	glm::vec3 Position;
	glm::vec2 Texcoord;
	};

*/
