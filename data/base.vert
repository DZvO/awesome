#version 120

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

attribute vec3 position;
attribute vec2 texcoord;

varying vec2 vertTexcoord;

void main()
{
	vertTexcoord = texcoord;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);//, 1.0f);//vec4(gl_Vertex.x, gl_Vertex.y, gl_Vertex.z, 1.0f);
}
