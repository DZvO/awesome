#version 120
varying vec4 pos;
varying float depth;

void main(void)
{
	gl_FragColor.r = depth;
	gl_FragColor.g = depth;
	gl_FragColor.b = depth;
//	gl_FragColor = vec4(pos.x, pos.y, pos.z, 1.0);
}
