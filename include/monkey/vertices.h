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
#include <glm/glm.hpp>

struct SimpleVertex3D {
    SimpleVertex3D(float x, float y, float z)
    : x(x), y(y), z(z) {}
    GLfloat x, y, z;
    static void InitAttributes();
};

struct __attribute__ ((visibility ("default")))  Vertex3D {
    Vertex3D(GLfloat x, GLfloat y, GLfloat z)
    :x(x), y(y), z(z), s(0.0f), t(0.0f) {}
    Vertex3D(GLfloat x, GLfloat y, GLfloat z, GLfloat s, GLfloat t)
    : x(x), y(y), z(z), s(s), t(t), r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
    Vertex3D(GLfloat x, GLfloat y, GLfloat z, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
    : x(x), y(y), z(z), s(s), t(t), r(r), g(g), b(b), a(a) {}
    GLfloat x, y, z;
    GLfloat s, t;
    GLfloat r, g, b, a;
    static void InitAttributes();
    static unsigned num_vertices;
};

//struct Vertex3DC {
//    Vertex3DC(GLfloat x, GLfloat y, GLfloat z, GLfloat s, GLfloat t, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
//            : x(x), y(y), z(z), s(s), t(t), r(r), g(g), b(b), a(a) {}
//    GLfloat x, y, z;
//    GLfloat s, t;
//    GLfloat r, g, b, a;
//    static void InitAttributes();
//};
//

// vertex with texture and normal

struct Vertex3DN {
    Vertex3DN() = default;
    Vertex3DN(
            GLfloat x, GLfloat y, GLfloat z,
            GLfloat s, GLfloat t,
            GLfloat nx, GLfloat ny, GLfloat nz)
            : x(x), y(y), z(z), nx(nx), ny(ny), nz(nz), s(s), t(t) {}
    GLfloat x, y, z;
    GLfloat s, t;
    GLfloat nx, ny, nz;

    static void InitAttributes();
};

struct __attribute__ ((visibility ("default"))) VertexColor {
    VertexColor(GLfloat x, GLfloat y, GLfloat z, GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f)
    : x(x), y(y), z(z), r(r), g(g), b(b), a(a) {}
	VertexColor(GLfloat x, GLfloat y, GLfloat z, glm::vec4 color )
	: x(x), y(y), z(z), r(color.r), g(color.g), b(color.b), a(color.a) {}
    GLfloat x, y, z;
    GLfloat r, g, b, a;
    static void enableAttributes();
    static void InitAttributes();
    static unsigned num_vertices;
};

struct VertexColorNormal {
    VertexColorNormal() : x(0), y(0), z(0), nx(0), ny(0), nz(0), r(0), g(0), b(0), a(0) {}
    VertexColorNormal(GLfloat x, GLfloat y, GLfloat z,
        GLfloat nx, GLfloat ny, GLfloat nz,
        GLfloat r = 1.0f, GLfloat g = 1.0f, GLfloat b = 1.0f, GLfloat a = 1.0f)
            : x(x), y(y), z(z), nx(nx), ny(ny), nz(nz), r(r), g(g), b(b), a(a) {}
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

struct VertexSkeletal
{
	VertexSkeletal () = default;
	VertexSkeletal (const float* s);
    GLfloat x, y, z;            // Vertex
    GLfloat s, t;               // Texcoord
    //GLint index0, index1, index2;     // Index into the bone/offset matrix array (2 bones)
    GLfloat weight0, weight1, weight2;   // The blend factor for each bone/offset matrix (2 bones)
    static void InitAttributes();
	static unsigned point_size;
	static unsigned num_vertices;

};

struct VertexSkeletalColor
{
	GLfloat x, y, z;            // Vertex
	GLfloat r, g, b;               // Texcoord
	GLint index0, index1, index2;     // Index into the bone/offset matrix array (2 bones)
	GLfloat weight0, weight1, weight2;   // The blend factor for each bone/offset matrix (2 bones)
	static void InitAttributes();

};


#endif /* vertices_h */
