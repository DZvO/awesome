#include "game.hpp"

motor::Game::Game()
{
	loop = true;
}

int motor::Game::main(Window *wndw, Input *inp)
{
	window = wndw;
	input = inp;

	//Chunk *chk = new Chunk(16, 16, 16);
	//chk->calculateVisibleSides();
	//chk->uploadToVbo();
	
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

	glPolygonMode(GL_FRONT, GL_LINE);

	while(loop)
	{
		input->update(window);
		if(input->quit())
			return 0;
		if(input->windowResized())
		{
			cout << "handled!" << window->width << " " << window->height << endl;
			cam->setPerspective(45.0f, float(window->width) / float(window->height), 0.5f, window->far); 
		}

		if(input->isPressed(Key::SPACE))
		{
			cam->position.y++;
		}

		float multiplierMove = 0;
		float multiplierRotate = 4.0f;
		
		if(input->isPressed(Key::LSHIFT))
		{
			multiplierMove = 0.5f;
			multiplierRotate = 1.5f;
		}
		else
		{
			multiplierMove = 3;
			multiplierRotate = 4.0f;
		}

		if(input->isPressed(Key::COMMA))
			cam->moveLoc(0, 0, -multiplierMove, 1);
		if(input->isPressed(Key::O))
			cam->moveLoc(0, 0, multiplierMove, 1);
		if(input->isPressed(Key::A))
			cam->moveLoc(-multiplierMove, 0, 0, 1);
		if(input->isPressed(Key::E))
			cam->moveLoc(multiplierMove, 0, 0, 1);

		if(input->isPressed(Key::LEFT))
		{
			cam->rotateGlo(0, 1, 0, multiplierRotate);
		}
		if(input->isPressed(Key::RIGHT))
		{
			cam->rotateGlo(0, -1, 0, multiplierRotate);
		}
		if(input->isPressed(Key::UP))
		{
			cam->rotateLoc(multiplierRotate, 0, 0, 1);
		}
		if(input->isPressed(Key::DOWN))
		{
			cam->rotateLoc(-multiplierRotate, 0, 0, 1);
		}
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
