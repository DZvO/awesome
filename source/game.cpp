#include "game.hpp"

motor::Game::Game()
{
	loop = true;
}

motor::Shader *shader;

#define _OFFSET(i) ((char *)NULL + (i))
int motor::Game::main(Window *wndw, Input *inp)
{
	window = wndw;
	input = inp;

	//glPolygonMode(GL_FRONT, GL_LINE);
	//Chunk *chk = new Chunk(16, 16, 16);
	//chk->calculateVisibleSides();
	//chk->uploadToVbo();

	World world;
	world.load(4 * 2, 4 * 2, 4 * 2);
	world.generate();

	glActiveTexture(GL_TEXTURE0);
	tileset = new Image("data/tileset.png");

	shader = new motor::Shader();
	shader->init();

	shader->attachVertexShader("data/base.vert");
	shader->attachFragmentShader("data/base.frag");
	shader->compile();
	int texUniform;
	texUniform = shader->getUniformLocation("texture");
	int positionAttrib;
	int texcoordAttrib;
	positionAttrib = shader->getAttributeLocation("position");
	texcoordAttrib = shader->getAttributeLocation("texcoord");
	cout << "texuni: " << texUniform << " posAtt: " << positionAttrib << " texcoAtt: " << texcoordAttrib << endl;
	shader->activate();

	cam = new Camera(input, shader);
	cam->setPerspective(45.0f, float(window->width) / float(window->height), window->near, window->far);

//	init_buffers();

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

		float multiplierMove = 4.0f;
		float multiplierRotate = 2.0f;
		
		if(input->isPressed(Key::LSHIFT))
		{
			multiplierMove = 10;
		}
		else
			multiplierMove = 4;


		if(input->isPressed(Key::COMMA))
			cam->movePosition(0, 0, 0.1f * multiplierMove);
		if(input->isPressed(Key::O))
			cam->movePosition(0, 0, -0.1f * multiplierMove);
		if(input->isPressed(Key::A))
			cam->movePosition(0.1f * multiplierMove, 0, 0);
		if(input->isPressed(Key::E))
			cam->movePosition(-0.1f * multiplierMove, 0, 0);

		if(input->isPressed(Key::LEFT))
			cam->moveRotation(0, 0.87654321f * multiplierRotate, 0);
		if(input->isPressed(Key::RIGHT))
			cam->moveRotation(0, -0.87654321f * multiplierRotate, 0);
		if(input->isPressed(Key::UP))
			cam->moveRotation(0.87654321f * multiplierRotate, 0, 0);
		if(input->isPressed(Key::DOWN))
			cam->moveRotation(-0.87654321f * multiplierRotate, 0, 0);
		cam->think();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniform1i(texUniform, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tileset->data);

		/*
		 * void glVertexAttribPointer(	GLuint  	index,
		 * 	GLint	size,
		 * 	GLenum  	type,
		 * 	GLboolean  	normalized,
		 * 	GLsizei  	stride,
		 * 	const GLvoid *  	pointer);
		 */
//		glEnableVertexAttribArray(positionAttrib);
//		glEnableVertexAttribArray(texcoordAttrib);

//		glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), _OFFSET(0));
//		glVertexAttribPointer(texcoordAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), _OFFSET(sizeof(glm::vec3)));


		//chk->draw();
		////glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

		////glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glDrawArrays(GL_QUADS, 0, chk->getVertexCount()); //6 -> VertexCount
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


//positionAttrib = shader->getAttributeLocation("position");
//texcoordAttrib = shader->getAttributeLocation("texcoord");
//or just bind them to a location
//glBindAttribLocation(shader->getProgram(), 0, "position");
//glBindAttribLocation(shader->getProgram(), 4, "texcoord");
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
