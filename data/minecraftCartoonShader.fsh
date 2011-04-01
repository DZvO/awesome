#define GAMMA 1.2
#define CARTOON

#ifdef CARTOON
const float EDGE_THRESHOLD = 0.05;
const float EDGE_THICKNESS = 1.0;
#endif

const float PI = 3.141592653589793238462;

uniform sampler2D sampler0;
uniform sampler2D sampler1;
uniform sampler2D sampler2;

uniform float near;
uniform float far;

uniform float aspectRatio;
uniform float displayHeight;
uniform float displayWidth;

float getDepth(vec2 coord);
#ifdef CARTOON
vec4 edgeDetect(vec2 coord);
#endif

void main() {
    gl_FragColor = texture2D(sampler0, gl_TexCoord[0].st);

#ifdef CARTOON
    vec4 outlineColor = edgeDetect(gl_TexCoord[0].st);
    if (outlineColor.a == 1.0) {
        gl_FragColor.rgb = outlineColor.rgb;
    }
#endif

#ifdef GAMMA
    if (gl_FragColor[3] == 0.0) {
        gl_FragColor = gl_Fog.color;
    }
    else {
        gl_FragColor.rgb = pow(gl_FragColor.rgb, vec3(1.0/GAMMA));
    }
#endif

}

float getDepth(vec2 coord) {
    float depth = texture2D(sampler1, coord).x;
    float depth2 = texture2D(sampler2, coord).x;
    if (depth2 < 1.0) {
        depth = depth2;
    }

    return depth * near / (far + (near - far)*depth);
}

#ifdef CARTOON
vec4 edgeDetect(vec2 coord) {
    vec2 o11 = vec2(1.0, aspectRatio)*EDGE_THICKNESS/displayWidth;

	vec4 accum = vec4(0.0);

    // row -2
    accum.x = getDepth(coord + vec2(-1*o11.s, -2*o11.t));
	accum.yz += vec2(-accum.x, accum.x);
    accum.x = getDepth(coord + vec2(     0.0, -2*o11.t));
    accum.yz += vec2(-accum.x, accum.x);
    accum.x = getDepth(coord + vec2( 1*o11.s, -2*o11.t));
    accum.yz += vec2(-accum.x, accum.x);
    // row -1
    accum.x = getDepth(coord + vec2(-2*o11.s, -1*o11.t));
    accum.yz += vec2(-accum.x, accum.x);
    accum.x = getDepth(coord + vec2(-1*o11.s, -1*o11.t));
    accum.yz += vec2(-accum.x, accum.x);
    accum.x = getDepth(coord + vec2(     0.0, -1*o11.t));
    accum.yz += vec2(-2*accum.x, accum.x);
    accum.x = getDepth(coord + vec2( 1*o11.s, -1*o11.t));
    accum.yz += vec2(-accum.x, accum.x);
    accum.x = getDepth(coord + vec2( 2*o11.s, -1*o11.t));
    accum.yz += vec2(-accum.x, accum.x);
    // row 0
    accum.x = getDepth(coord + vec2(-2*o11.s, 0.0));
    accum.yz += vec2(-accum.x, accum.x);
    accum.x = getDepth(coord + vec2(-1*o11.s, 0.0));
    accum.yz += vec2(-2*accum.x, accum.x);
	accum.x = getDepth(coord);
    accum.yz += vec2(24*accum.x, accum.x);
    accum.x = getDepth(coord + vec2( 1*o11.s, 0.0));
    accum.yz += vec2(-2*accum.x, accum.x);
    accum.x = getDepth(coord + vec2( 2*o11.s, 0.0));
    accum.yz += vec2(-accum.x, accum.x);
    // row 1
    accum.x = getDepth(coord + vec2(-2*o11.s, 1*o11.t));
    accum.yz += vec2(-accum.x, accum.x);
    accum.x = getDepth(coord + vec2(-1*o11.s, 1*o11.t));
    accum.yz += vec2(-accum.x, accum.x);
    accum.x = getDepth(coord + vec2(     0.0, 1*o11.t));
    accum.yz += vec2(-2*accum.x, accum.x);
    accum.x = getDepth(coord + vec2( 1*o11.s, 1*o11.t));
    accum.yz += vec2(-accum.x, accum.x);
    accum.x = getDepth(coord + vec2( 2*o11.s, 1*o11.t));
    accum.yz += vec2(-accum.x, accum.x);
    // row 2
    accum.x = getDepth(coord + vec2(-1*o11.s, 2*o11.t));
    accum.yz += vec2(-accum.x, accum.x);
    accum.x = getDepth(coord + vec2(     0.0, 2*o11.t));
	accum.yz += vec2(-accum.x, accum.x);
    accum.x = getDepth(coord + vec2( 1*o11.s, 2*o11.t));
	accum.yz += vec2(-accum.x, accum.x);

    accum.z = clamp(accum.z/21.0, 0.0, 1.0);
    
    return vec4(vec3(0.0), step(accum.z*EDGE_THRESHOLD, accum.y));

}
#endif
