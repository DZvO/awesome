#include "game.hpp"

motor::Game::Game()
{
	loop = true;
}

void printVector(glm::vec3 v)
{
	cout << "(" << v.x << " " << v.y << " " << v.z << ")" << endl;
}

double round(double d)
{
	return floor(d + 0.5);
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

	World world;
	world.load(4, 4, 4, 16, 16, 16); // 128
	world.generate();

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
	cam->position = glm::vec3(0, 10, -0.5);

	cout << endl;

	glUniform1i(texUniform, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tileset->data);

//	glPolygonMode(GL_FRONT, GL_LINE);

	glm::vec3 pos, acc, vel;
	pos = glm::vec3(0, 10, 0);

	cout << sizeof(Key::Key) << endl;

	while(loop)
	{
		time->update();
		input->update(time, window);//, time);

		//cout << 1.f / time->getFrameTime() << endl;
		
		if(input->quit())
			return 0;
		if(input->windowResized())
		{
			cout << "handled!" << window->width << " " << window->height << endl;
			cam->setPerspective(45.0f, float(window->width) / float(window->height), 0.3f, window->far); 
		}

		pos = cam->position;
		//cout << int(world.getBlock((int)pos.x, (int)pos.y - 2, (int)pos.z).type) << " block pos " << (int)pos.y << endl;

		if(world.getBlock(round(pos.x), int(pos.y) - 2.0f, round(pos.z)).type == BLOCK_AIR)
		{
			vel.y -= 2.f;
		}

		if(falling())
			vel.y -= 2.f;


		vel += acc * time->getFrameTime();
		pos += vel * time->getFrameTime();
		cam->position = pos;

		acc *= 0.8f;
		vel *= 0.8f;

		if(input->isPressed(Key::W))
				printVector(pos);

		//cout << input->getKeyDelay(Key::SPACE) << endl;
		if(input->isPressed(Key::SPACE) )//&& (input->getKeyDelay(Key::SPACE) > 2.f))
		{
			//cout << " jump";
			vel = glm::vec3(0.0f, 52.123f, 0);
		}
		//cout << endl;

		float multiplierMove;
		float multiplierRotate;

		if(input->isPressed(Key::LSHIFT))
		{
			multiplierMove = 0.01f;
			multiplierRotate = 1.5f;
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
