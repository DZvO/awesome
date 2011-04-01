#version 120
varying vec4 pos;
//uniform float delta;

void main()
{
	vec4 v = vec4(gl_Vertex);
//	v.z = sin(0.1 * v.x + delta) * cos(0.1 * v.y + delta) * 22.0;
	pos = v;
	gl_Position = gl_ModelViewProjectionMatrix * v;
	//pos = gl_Position;
}
