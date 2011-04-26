#version 120

uniform float delta;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

attribute vec3 position;
attribute vec2 texcoord;

varying vec2 vertTexcoord;

void main()
{
	vertTexcoord = texcoord;
	vec4 pos = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0f);//, 1.0f);//vec4(gl_Vertex.x, gl_Vertex.y, gl_Vertex.z, 1.0f);
	//pos.y += sin(position.y) * 10 * (cos(delta + position.z) / 10) + tan(position.x);
	//pos.x += sin(delta + position.z);
	
	gl_Position = pos;
}
