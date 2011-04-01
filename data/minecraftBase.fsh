#define SQUIRM

const float PI = 3.1415926535897932384626433832795;
const float PI2 = 6.283185307179586476925286766559;

const int GL_LINEAR = 9729;
const int GL_EXP = 2048;

uniform sampler2D sampler0;
uniform sampler2D sampler1;

uniform float near;
uniform float far;

uniform int fogMode;

uniform int worldTime;
uniform int renderType;

uniform float aspectRatio;
uniform float displayHeight;
uniform float displayWidth;

varying float texID;
varying vec3 normal;

void main() {
#ifdef SQUIRM
    if (round(texID) == 104.0) {
        float t = float(mod(worldTime, 300))/300.0;
        vec2 coord, offset, base;
        coord = modf(16.0*gl_TexCoord[0].st, base);
        offset = vec2(cos(PI2*coord.s)*cos(PI2*(coord.t + 2.0*t))*cos(PI2*t)/32.0,
                     -cos(PI2*(coord.s + t))*sin(2.0*PI2*coord.t)/32.0);

        coord = mod(coord + offset, vec2(1.0)) + base;
        gl_FragColor = texture2D(sampler0, coord/16.0) * gl_Color;
    }
    else {
#endif
        gl_FragColor = texture2D(sampler0, gl_TexCoord[0].st) * gl_Color;
#ifdef SQUIRM
    }
#endif
    if (abs(gl_FragColor.a) > 0.005) {
		if (fogMode == GL_EXP) {
			gl_FragColor = mix(gl_FragColor, gl_Fog.color, 1.0 - clamp(exp(-gl_Fog.density * gl_FogFragCoord), 0.0, 1.0));
		} else if (fogMode == GL_LINEAR) {
			gl_FragColor = mix(gl_FragColor, gl_Fog.color, clamp((gl_FogFragCoord - gl_Fog.start) * gl_Fog.scale, 0.0, 1.0));
		}
	}
}
