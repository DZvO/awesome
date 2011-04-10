#include "title.hpp"

motor::Title::Title(): background("data/background.png"),	logo("data/logo.png")
{
	loop = true;
}

int motor::Title::main(Window *wndw, Input *inp, Time* time)
{
	/*
	window = wndw;
	input = inp;

	float delta = 1;
	Shader *shader = new Shader();
	shader->init();

	shader->attachVertexShader("data/depth.vert");
	shader->attachFragmentShader("data/depth.frag");
	shader->compile();
	shader->activate();

	while(loop)
	{
		input->update(window);
		if(input->quit())
			return 0;
		delta += 0.021f;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	 	shader->activate();
		glLoadIdentity();

		glTranslatef(0, 0, -8.0f);
		glTranslatef((sin(delta)), 0.0f, (cos(delta))*40);
		glRotatef((delta), 1.0f, 1.0f, 0.5f);
//		glColor3f(1.0f, 1.0f, 1.0f);

		glBegin(GL_QUADS);
		{
			glColor3f(0.0f,1.0f,0.0f);      // Set The Color To Green
			glVertex3f( 1.0f, 1.0f,-1.0f);      // Top Right Of The Quad (Top)
			glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Top)
			glVertex3f(-1.0f, 1.0f, 1.0f);      // Bottom Left Of The Quad (Top)
			glVertex3f( 1.0f, 1.0f, 1.0f);      // Bottom Right Of The Quad (Top)

			glColor3f(1.0f,0.5f,0.0f);      // Set The Color To Orange
			glVertex3f( 1.0f,-1.0f, 1.0f);      // Top Right Of The Quad (Bottom)
			glVertex3f(-1.0f,-1.0f, 1.0f);      // Top Left Of The Quad (Bottom)
			glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Bottom)
			glVertex3f( 1.0f,-1.0f,-1.0f);      // Bottom Right Of The Quad (Bottom)

			glColor3f(1.0f,0.0f,0.0f);      // Set The Color To Red
			glVertex3f( 1.0f, 1.0f, 1.0f);      // Top Right Of The Quad (Front)
			glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Left Of The Quad (Front)
			glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Left Of The Quad (Front)
			glVertex3f( 1.0f,-1.0f, 1.0f);      // Bottom Right Of The Quad (Front)

			glColor3f(1.0f,1.0f,0.0f);      // Set The Color To Yellow
			glVertex3f( 1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Back)
			glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Right Of The Quad (Back)
			glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Right Of The Quad (Back)
			glVertex3f( 1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Back)

			glColor3f(0.0f,0.0f,1.0f);      // Set The Color To Blue
			glVertex3f(-1.0f, 1.0f, 1.0f);      // Top Right Of The Quad (Left)
			glVertex3f(-1.0f, 1.0f,-1.0f);      // Top Left Of The Quad (Left)
			glVertex3f(-1.0f,-1.0f,-1.0f);      // Bottom Left Of The Quad (Left)
			glVertex3f(-1.0f,-1.0f, 1.0f);      // Bottom Right Of The Quad (Left)

			glColor3f(1.0f,0.0f,1.0f);      // Set The Color To Violet
			glVertex3f( 1.0f, 1.0f,-1.0f);      // Top Right Of The Quad (Right)
			glVertex3f( 1.0f, 1.0f, 1.0f);      // Top Left Of The Quad (Right)
			glVertex3f( 1.0f,-1.0f, 1.0f);      // Bottom Left Of The Quad (Right)
			glVertex3f( 1.0f,-1.0f,-1.0f);      // Bottom Right Of The Quad (Right)
		}
		glEnd();

		SDL_GL_SwapBuffers();
		//insert code with VBO's here, please :)
	}
*/
	return 0;
}

void motor::Title::update()
{

}

void motor::Title::draw()
{

}

void motor::Title::init()
{
}

void motor::Title::load()
{
}

void motor::Title::unload()
{

}

