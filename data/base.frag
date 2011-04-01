#version 120
uniform sampler2D texture;
varying vec2 vertTexcoord;

void main()
{
	gl_FragColor = texture2D(texture, vertTexcoord);
//	gl_FragColor = vec4(1.f,1.f,1.f,1.f);
}
