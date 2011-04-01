#define CURVATURE
#define WAVING_WHEAT

#ifdef CURVATURE
const float FLAT_RADIUS          = 64.0;
const float WORLD_RADIUS         = 192.0;
const float WORLD_RADIUS_SQUARED = WORLD_RADIUS*WORLD_RADIUS;
#endif

const float PI = 3.1415926535897932384626433832795;
const float PI2 = 6.283185307179586476925286766559;

uniform float sunVector;
uniform float moonVector;
uniform int worldTime;
uniform int renderType;

varying float texID;

int getTextureID(vec2 coord);

void main() {
    vec4 position = gl_Vertex;
#ifdef WAVING_WHEAT
    int tex = getTextureID(gl_MultiTexCoord0.st);
    if (87 < tex && tex < 96 && renderType != 0) {
        float t = float(mod(worldTime, 200))/200.0;
        vec2 pos = position.xz/16.0;
        if (round(16.0*gl_MultiTexCoord0.t) <= floor(16.0*gl_MultiTexCoord0.t)) {
            position.x += (sin(PI2*(2.0*pos.x + pos.y - 3.0*t)) + 0.6)/8.0;
        }
    }
    position = gl_ModelViewMatrix * position;
#endif
#ifdef CURVATURE
    if (gl_Color.a != 0.8) {
        // Not a cloud.

        float dist = (length(position) - FLAT_RADIUS)/WORLD_RADIUS;

        if (dist > 0) {
            dist *= dist;
            position.y -= WORLD_RADIUS - sqrt(max(1.0 - dist, 0.0)) * WORLD_RADIUS;
        }

    }
#endif

#if defined(CURVATURE) || defined(WAVING_WHEAT)
    gl_Position = gl_ProjectionMatrix * position;
#else
    gl_Position = ftransform();
#endif

    if (renderType != 0) {
        texID = float(getTextureID(gl_MultiTexCoord0.st));
    }
    else {
        texID = -1.0;
    }

    gl_FrontColor = gl_BackColor = gl_Color;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_FogFragCoord = gl_Position.z;
}

int getTextureID(vec2 coord) {
    int i = int(floor(16*coord.s));
    int j = int(floor(16*coord.t));
    return i + 16*j;
}
