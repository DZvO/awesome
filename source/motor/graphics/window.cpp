#include "window.hpp"

const float motor::Window::near = .0001f;//.3005f; //.485f;
const float motor::Window::far = 100.0f;

motor::Window::Window()
{}

motor::Window::Window(int width, int height, string title)
{
	open(width, height, title);
}

void motor::Window::open(int width, int height, string title)
{
	this->width = width;
	this->height = height;

	if(SDL_Init(SDL_INIT_TIMER) < 0 ) 
	{
		cout << "Unable to init SDL_TIMER: " << SDL_GetError() << "\nPlease send me a mail with the Error Code\n";
		exit(1);
	}
	if(SDL_Init(SDL_INIT_VIDEO) < 0 ) 
	{
		cout << "Unable to init SDL_VIDEO: " << SDL_GetError() << "\nPlease send me a mail with the Error Code\n";
		exit(1);
	}
	//if(SDL_Init(SDL_INIT_AUDIO) < 0 ) 
	//{
	//	cout << "Unable to init SDL_VIDEO: " << SDL_GetError() << "\nPlease send me a mail with the Error Code\n";
	//	exit(1);
	//}

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute( SDL_GL_SWAP_CONTROL, 0);
	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL | SDL_DOUBLEBUF | SDL_RESIZABLE);
	SDL_WM_SetCaption(title.c_str(), NULL);

	glClearColor(1.f/255.f * 146.f, 1.f/255.f * 161.f, 1.f/255.f * 207.f, 0);
	glViewport(0, 0, width, height);	

	//glClearDepth(1.0f);
	//	glMatrixMode(GL_PROJECTION);
	//	glLoadIdentity();
	//gluOrtho2D(0, width, height, 0);
	//glOrtho(0, width, height, 0, -1, 1);
	//	gluPerspective(45.0f, float(width/height), near, far);
	//	glMatrixMode(GL_MODELVIEW);
	//	glLoadIdentity();

	glEnable(GL_VERTEX_ARRAY);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	//	glDepthRangef(0.0,1.0);
	//glDepthFunc(GL_LEQUAL);
	//glDepthMask(GL_TRUE);
	//
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glShadeModel(GL_SMOOTH);

	//	glEnable(GL_CULL_FACE);
	//	glCullFace(GL_BACK);

	glEnable(GL_ALPHA_TEST);
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//	glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	//glClear(GL_COLOR_BUFFER_BIT);
	//SDL_UpdateRect(screen, 0, 0, 640, 480);
	//SDL_GL_SwapBuffers();
	//glClear(GL_COLOR_BUFFER_BIT);

	glewInit();
	if(!GLEW_VERSION_2_0)
	{
		cout << "Dude, your card doesn't supports OpenGL 2.0 (which is bad!)" << endl;
		cout << "Please update your drivers, or buy a real video card" << endl;
		cout << endl << "If you are sure you have a real video card and up-to-date drivers, drop me an E-Mail" << endl;

		cout << "hnnnngh! " << endl;
		exit(-1);
	}
	cout << "sdl and gl initialised! READY FOR WORLD DOMINATION!" << endl;
}

void motor::Window::resize(int x, int y)
{
	width = x;
	height = y;
	cout << "resizin' " << width << " " << height << endl;
	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL | SDL_DOUBLEBUF | SDL_RESIZABLE);
	glViewport(0, 0, width, height);	
	//	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	//	glLoadIdentity();							// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	//	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height, near, far);
	//	glMatrixMode(GL_MODELVIEW);						// Select The Modelview Matrix
	//	glLoadIdentity();							// Reset The Modelview Matrix
}
