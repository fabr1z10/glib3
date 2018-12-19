//
//  vertices.h
//  glib
//
//  Created by Fabrizio Venturini on 06/05/2018.
//
//

#ifndef vertices_h
#define vertices_h

#include <GL/glew.h>

struct SimpleVertex3D {
    SimpleVertex3D(float x, float y, float z)
    : x(x), y(y), z(z) {}
    GLfloat x, y, z;
    static void InitAttributes();
};

struct Vertex3D {
    Vertex3D(GLfloat x, GLfloat y, GLfloat z)
    :x(x), y(y), z(z), s(0.0f), t(0.0f) {}
    Vertex3D(GLfloat x, GLfloat y, GLfloat z, GLfloat s, GLfloat t)
    : x(x), y(y), z(z), s(s), t(t) {}
    GLfloat x, y, z;
    GLfloat s, t;
    static void InitAttributes();
};

struct VertexColor {
    VertexColor(GLfloat x, GLfloat y, GLfloat z, GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f)
    : x(x), y(y), z(z), r(r), g(g), b(b), a(a) {}
    GLfloat x, y, z;
    GLfloat r, g, b, a;
    static void InitAttributes();
};

struct VertexColorNormal {
    VertexColorNormal(GLfloat x, GLfloat y, GLfloat z,
        GLfloat nx, GLfloat ny, GLfloat nz,
        GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f)
            : x(x), y(y), z(z), r(r), g(g), b(b), a(a) {}
    GLfloat x, y, z;
    GLfloat nx, ny, nz;
    GLfloat r, g, b, a;
    static void InitAttributes();
};

struct VertexText {
    VertexText(GLfloat x, GLfloat y, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    : x(x), y(y), s(s), t(t), r(r), g(g), b(b), a(a) {}
    GLfloat x, y;
    GLfloat s, t;
    GLfloat r, g, b, a;
    static void InitAttributes();
};

#endif /* vertices_h */
