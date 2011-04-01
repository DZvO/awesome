#include "shader.hpp"
//------------------------------------------------------------------------
motor::Shader::Shader()
{
	programPointer = 0;
	vertexPointer = 0;
	fragmentPointer = 0;
}

motor::Shader::~Shader()
{
	glUseProgram(0);
	glDeleteShader(vertexPointer);
	glDeleteShader(fragmentPointer);
	glDeleteProgram(programPointer);
}

void motor::Shader::init()
{
	programPointer = glCreateProgram();
}

void motor::Shader::attachVertexShader(const char* path)
{
	vertexPointer = loadShader(GL_VERTEX_SHADER, path);
	glAttachShader(programPointer, vertexPointer);
}

void motor::Shader::attachFragmentShader(const char* path)
{
	fragmentPointer = loadShader(GL_FRAGMENT_SHADER, path);
	glAttachShader(programPointer, fragmentPointer);
}

void motor::Shader::attachShader(const unsigned int type, const char* path)
{
	if(type == GL_FRAGMENT_SHADER)
		attachFragmentShader(path);
	else if(type == GL_VERTEX_SHADER)
		attachVertexShader(path);
	else
		cout << "Dear Sir, you have specified a wrong type!" << endl;
}

void motor::Shader::attachShader(const char* vertexPath, const char* fragmentPath)
{
	attachVertexShader(vertexPath);
	attachFragmentShader(fragmentPath);
}

int motor::Shader::getUniformLocation(const char *name)
{
	return glGetUniformLocation(this->programPointer, name);
}

int motor::Shader::getAttributeLocation(const char *name)
{
	return glGetAttribLocation(this->programPointer, name);
}

bool motor::Shader::compile()
{
	glLinkProgram(this->programPointer);

	if(error(this->programPointer, GL_LINK_STATUS))
	{
		show_error(this->programPointer, glGetProgramiv, glGetProgramInfoLog);
		glDeleteProgram(this->programPointer);
		return false;
	}
	return true;
}

void motor::Shader::activate()
{
	if(programPointer == 0)
		cout << "ERROR: Please init me first! (shader)" << endl;
	glUseProgram(programPointer);
//	cout << "Program: " << programPointer << " Vertex: " << vertexPointer << " Fragment: " << fragmentPointer << endl;
}

void motor::Shader::deactivate()
{
	glUseProgram(0);
}

unsigned int motor::Shader::getProgram()
{
	return programPointer;
}

//-------------------------------------------------------------------------


bool motor::Shader::error(unsigned int object, unsigned int status)
{
	int ok = 0;
	if(status == GL_LINK_STATUS)
	{
		glGetProgramiv(object, status, &ok);
		return !ok;
	}
	else if(status == GL_COMPILE_STATUS)
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &ok);
		return !ok;
	}
	return true;
}

void motor::Shader::show_error(unsigned int object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog)
{
	int length;
	char *out;

	glGet__iv(object, GL_INFO_LOG_LENGTH, &length);
	out = new char[length];
	glGet__InfoLog(object, length, NULL, out);
	cout << out << endl;
	delete [] out;
}

char* motor::Shader::loadFile(const char* path)
{
	FILE *fd;
	long len, r;
	char *str;

	if (!(fd = fopen(path, "r")))
	{
		fprintf(stderr, "Can't open file '%s' for reading\n", path);
		return NULL;
	}

	fseek(fd, 0, SEEK_END);
	len = ftell(fd);

	//printf("File '%s' is %ld long\n", path, len);

	fseek(fd, 0, SEEK_SET);

	if (!(str = (char*)malloc(len * sizeof(char))))
	{
		fprintf(stderr, "Can't malloc space for '%s'\n", path);
		return NULL;
	}

	r = fread(str, sizeof(char), len, fd);

	str[r - 1] = '\0'; /*   Shader sources have to term with null */

	fclose(fd);

	return str;
}

int motor::Shader::loadShader(const unsigned int type, const char* path)
{
	unsigned int shaderPointer = 0;
	char *source = loadFile(path);
//	cout << path << ":" << endl;
//	cout << source << endl << endl;

	shaderPointer = glCreateShader(type);
	glShaderSource(shaderPointer, 1, (const char**)(&(source)), NULL);
	glCompileShader(shaderPointer);

	delete [] source; //free shader source, because GL has saved its own copy

	if(error(shaderPointer, GL_COMPILE_STATUS))
	{
		cout << "error in " << path << endl;
		show_error(shaderPointer, glGetShaderiv, glGetShaderInfoLog);
		glDeleteShader(shaderPointer);
		return 0;
	}
	cout << path << " compiled successfully" << endl;
	return shaderPointer;
}
