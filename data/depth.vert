#version 120
varying vec4 pos;
varying float depth;
uniform mat4 MVP;

void main()
{
	vec4 viewPos = gl_ModelViewMatrix * gl_Vertex; // this will transform the vertex into eyespace
	depth = (-viewPos.z - 1.0)/(100.0 - 1.0); // will map near..far to 0..1
	gl_Position = MVP * vec4(1.0f);
	pos = vec4(gl_Vertex.x, gl_Vertex.y, gl_Vertex.z, 1.0);
}
