#include <monkey/vertices.h>
#include <stddef.h>

void SimpleVertex3D::InitAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex3D), (void*)offsetof(SimpleVertex3D, x));
}

void Vertex3D::InitAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, x));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, s));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)offsetof(Vertex3D, r));

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

void VertexColorNormal::InitAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColorNormal), (void*)offsetof(VertexColorNormal, x));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColorNormal), (void*)offsetof(VertexColorNormal, nx));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexColorNormal), (void*)offsetof(VertexColorNormal, r));

}


void VertexText::InitAttributes() {
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexText), (void*)offsetof(VertexText, x));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexText), (void*)offsetof(VertexText, s));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexText), (void*)offsetof(VertexText, r));
}

void VertexSkeletal::InitAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSkeletal), (void*)offsetof(VertexSkeletal, x));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexSkeletal), (void*)offsetof(VertexSkeletal, s));
    glVertexAttribIPointer(2, 3, GL_INT, sizeof(VertexSkeletal), (void*)offsetof(VertexSkeletal, index0));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSkeletal), (void*)offsetof(VertexSkeletal, weight0));



}

void VertexSkeletalColor::InitAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSkeletalColor), (void*)offsetof(VertexSkeletalColor, x));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSkeletalColor), (void*)offsetof(VertexSkeletalColor, r));
    glVertexAttribIPointer(2, 3, GL_INT, sizeof(VertexSkeletalColor), (void*)offsetof(VertexSkeletalColor, index0));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSkeletalColor), (void*)offsetof(VertexSkeletalColor, weight0));



}