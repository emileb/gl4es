#include "gl.h"

#ifndef __FOG_H_
#define __FOG_H_

typedef struct {
    GLenum          mode;
    GLfloat         density;
    GLfloat         start;
    GLfloat         end;
    GLfloat         index;
    GLfloat         color[4];
    GLenum          coord_src;
} fog_t;

void gl4es_glFogfv(GLenum pname, const GLfloat* params);
void gl4es_glFogf(GLenum pname, GLfloat param);

void gl4es_glFogCoordf(GLfloat coord);
void gl4es_glFogCoordfv(const GLfloat *coord);

#endif