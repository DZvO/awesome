#include <stdlib.h>
#include <GL/glew.h>
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include "file-util.h"
#include "gl-util.h"
#include "vec-util.h"
#include "meshes.h"

static struct {
    struct flag_mesh flag, background;
    struct flag_vertex *flag_vertex_array;
    
    struct {
        GLuint vertex_shader, fragment_shader, program;

        struct {
            GLint texture, p_matrix, mv_matrix;
        } uniforms;

        struct {
            GLint position, normal, texcoord, shininess, specular;
        } attributes;
    } flag_program;

//    GLfloat p_matrix[16], mv_matrix[16];
    GLfloat eye_offset[2];
    GLsizei window_size[2];
} g_resources;

static void init_gl_state(void)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

#define PROJECTION_FOV_RATIO 0.7f
#define PROJECTION_NEAR_PLANE 0.0625f
#define PROJECTION_FAR_PLANE 256.0f

static void render_mesh(struct flag_mesh const *mesh)
{
    glBindTexture(GL_TEXTURE_2D, mesh->texture);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer);
    glVertexAttribPointer(
        g_resources.flag_program.attributes.position,
        3, GL_FLOAT, GL_FALSE, sizeof(struct flag_vertex),
        (void*)offsetof(struct flag_vertex, position)
    );
    glVertexAttribPointer(
        g_resources.flag_program.attributes.normal,
        3, GL_FLOAT, GL_FALSE, sizeof(struct flag_vertex),
        (void*)offsetof(struct flag_vertex, normal)
    );
    glVertexAttribPointer(
        g_resources.flag_program.attributes.texcoord,
        2, GL_FLOAT, GL_FALSE, sizeof(struct flag_vertex),
        (void*)offsetof(struct flag_vertex, texcoord)
    );
    glVertexAttribPointer(
        g_resources.flag_program.attributes.shininess,
        1, GL_FLOAT, GL_FALSE, sizeof(struct flag_vertex),
        (void*)offsetof(struct flag_vertex, shininess)
    );
    glVertexAttribPointer(
        g_resources.flag_program.attributes.specular,
        4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(struct flag_vertex),
        (void*)offsetof(struct flag_vertex, specular)
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->element_buffer);
    glDrawElements(
        GL_TRIANGLES,
        mesh->element_count,
        GL_UNSIGNED_SHORT,
        (void*)0
    );
}

#define INITIAL_WINDOW_WIDTH  640
#define INITIAL_WINDOW_HEIGHT 480

static void enact_flag_program(
    GLuint vertex_shader,
    GLuint fragment_shader,
    GLuint program
) {
    g_resources.flag_program.vertex_shader = vertex_shader;
    g_resources.flag_program.fragment_shader = fragment_shader;

    g_resources.flag_program.program = program;

    g_resources.flag_program.uniforms.texture
        = glGetUniformLocation(program, "texture");
    g_resources.flag_program.uniforms.p_matrix
        = glGetUniformLocation(program, "p_matrix");
    g_resources.flag_program.uniforms.mv_matrix
        = glGetUniformLocation(program, "mv_matrix");

    g_resources.flag_program.attributes.position
        = glGetAttribLocation(program, "position");
    g_resources.flag_program.attributes.normal
        = glGetAttribLocation(program, "normal");
    g_resources.flag_program.attributes.texcoord
        = glGetAttribLocation(program, "texcoord");
    g_resources.flag_program.attributes.shininess
        = glGetAttribLocation(program, "shininess");
    g_resources.flag_program.attributes.specular
        = glGetAttribLocation(program, "specular");
}

static int make_flag_program(
    GLuint *vertex_shader,
    GLuint *fragment_shader,
    GLuint *program
) {
    *vertex_shader = make_shader(GL_VERTEX_SHADER, "flag.v.glsl");
    if (*vertex_shader == 0)
        return 0;
    *fragment_shader = make_shader(GL_FRAGMENT_SHADER, "flag.f.glsl");
    if (*fragment_shader == 0)
        return 0;

    *program = make_program(*vertex_shader, *fragment_shader);
    if (*program == 0)
        return 0;

    return 1;
}

static int make_resources(void)
{
    GLuint vertex_shader, fragment_shader, program;

    g_resources.flag_vertex_array = init_flag_mesh(&g_resources.flag);
    init_background_mesh(&g_resources.background);

    g_resources.flag.texture = make_texture("flag.tga");
    g_resources.background.texture = make_texture("background.tga");

    if (g_resources.flag.texture == 0 || g_resources.background.texture == 0)
        return 0;

    if (!make_flag_program(&vertex_shader, &fragment_shader, &program))
        return 0;

    enact_flag_program(vertex_shader, fragment_shader, program);

    g_resources.eye_offset[0] = 0.0f;
    g_resources.eye_offset[1] = 0.0f;
    g_resources.window_size[0] = INITIAL_WINDOW_WIDTH;
    g_resources.window_size[1] = INITIAL_WINDOW_HEIGHT;

    update_p_matrix(
        g_resources.p_matrix,
        INITIAL_WINDOW_WIDTH,
        INITIAL_WINDOW_HEIGHT
    );
    update_mv_matrix(g_resources.mv_matrix, g_resources.eye_offset);

    return 1;
}

static void render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(g_resources.flag_program.program);

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(g_resources.flag_program.uniforms.texture, 0);

    glEnableVertexAttribArray(g_resources.flag_program.attributes.position);
    glEnableVertexAttribArray(g_resources.flag_program.attributes.normal);
    glEnableVertexAttribArray(g_resources.flag_program.attributes.texcoord);
    glEnableVertexAttribArray(g_resources.flag_program.attributes.shininess);
    glEnableVertexAttribArray(g_resources.flag_program.attributes.specular);

    render_mesh(&g_resources.flag);
    render_mesh(&g_resources.background);

    glDisableVertexAttribArray(g_resources.flag_program.attributes.position);
    glDisableVertexAttribArray(g_resources.flag_program.attributes.normal);
    glDisableVertexAttribArray(g_resources.flag_program.attributes.texcoord);
    glDisableVertexAttribArray(g_resources.flag_program.attributes.shininess);
    glDisableVertexAttribArray(g_resources.flag_program.attributes.specular);
    glutSwapBuffers();
}
