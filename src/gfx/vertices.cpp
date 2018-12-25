#include <gfx/vertices.h>
#include <stddef.h>

void SimpleVertex3D::InitAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex3D), (void*)offsetof(SimpleVertex3D, x));
}

void Vertex3D::InitAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, x));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, s));

}

void Vertex3DN::InitAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DN), (void*)offsetof(Vertex3DN, x));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DN), (void*)offsetof(Vertex3DN, s));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DN), (void*)offsetof(Vertex3DN, nx));

}

void VertexColor::InitAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColor), (void*)offsetof(VertexColor, x));
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexColor), (void*)offsetof(VertexColor, r));

}

void VertexText::InitAttributes() {
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexText), (void*)offsetof(VertexText, x));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexText), (void*)offsetof(VertexText, s));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexText), (void*)offsetof(VertexText, r));
}