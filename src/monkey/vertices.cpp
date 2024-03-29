#include <monkey/vertices.h>
#include <stddef.h>

unsigned VertexSkeletal::point_size = 11;
unsigned Vertex3D::num_vertices = 3;
unsigned Vertex3DN::num_vertices = 3;
unsigned VertexColor::num_vertices = 2;
unsigned VertexColorNormal::num_vertices = 3;
unsigned VertexSkeletal::num_vertices = 3;
unsigned VertexSkeletalColor::num_vertices = 3;

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

void VertexColor::enableAttributes() {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

}
void VertexColor::InitAttributes() {
    //for (size_t i = 0; i < 2; i++)
    //glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColor), (void*)offsetof(VertexColor, x));
    //glEnableVertexAttribArray(1);
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

VertexSkeletal::VertexSkeletal(const float *data) {
	x = data[0];
	y = data[1];
	z = data[2];
	s = data[3];
	t = data[4];
	weight0 = data[5];
	weight1 = data[6];
	weight2 = data[7];
}

void VertexSkeletal::InitAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSkeletal), (void*)offsetof(VertexSkeletal, x));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexSkeletal), (void*)offsetof(VertexSkeletal, s));
    //glVertexAttribIPointer(2, 3, GL_INT, sizeof(VertexSkeletal), (void*)offsetof(VertexSkeletal, index0));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSkeletal), (void*)offsetof(VertexSkeletal, weight0));



}

void VertexSkeletalColor::InitAttributes() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSkeletalColor), (void*)offsetof(VertexSkeletalColor, x));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSkeletalColor), (void*)offsetof(VertexSkeletalColor, r));
    //glVertexAttribIPointer(2, 3, GL_INT, sizeof(VertexSkeletalColor), (void*)offsetof(VertexSkeletalColor, index0));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexSkeletalColor), (void*)offsetof(VertexSkeletalColor, weight0));



}