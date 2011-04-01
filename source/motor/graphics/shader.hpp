#ifndef _SHADER_HPP
#define _SHADER_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>

using namespace std;

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace motor
{
	class Shader
	{
		public:
			Shader();
			~Shader();

			void init();

			void attachVertexShader(const char* path);
			void attachFragmentShader(const char* path);
			void attachShader(unsigned const int type, const char* path);
			void attachShader(const char* vertex, const char* fragment);

			int getUniformLocation(const char *name);
			int getAttributeLocation(const char *name);
			//void setUniform(ShaderStruct shadr, vector/matrix/usw...?

			bool compile();
			void activate();
			static void deactivate(); //deactivate all the shaders, you dont need an instance of the class for this, everything this does is call glUseProgram(0);

			unsigned int getProgram();

		private:
			unsigned int programPointer;
			unsigned int vertexPointer;
			unsigned int fragmentPointer;

			static bool error(unsigned int shader, unsigned int status /* GL_LINK_STATUS or GL_COMPILE_STATUS... */); //checks for an error
			static void show_error(unsigned int object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog); //prints the error to cerr/stderr
			static char* loadFile(const char* path);
			int loadShader(const unsigned int type, const char* path);
	};
}

//work on .. you know... aviable functions -> convenient interface

#endif
