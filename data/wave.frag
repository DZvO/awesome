#version 120
varying vec4 pos;
//uniform float delta;

void main(void)
{
	//gl_FragColor = vec4(sin(((pos.z - 1.0)/(132.0 - 1.0)) * 130) * 10, 0.0, 0.0, 1.0);
//	gl_FragColor = vec4(abs(pos.z), 0, 0, 1.0);
	gl_FragColor = vec4(pos.x, pos.y, pos.z, 1.0);
}
