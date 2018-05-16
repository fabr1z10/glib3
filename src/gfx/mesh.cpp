//
//  mesh.cpp
//  glib
//
//  Created by Fabrizio Venturini on 06/05/2018.
//
//

#include "gfx/mesh.h"
#include "gfx/shader.h"

void IMesh::Draw(Shader* shader, const std::string& anim, int frame) {
    //GLenum err = glGetError();
    glBindBuffer(GL_ARRAY_BUFFER, m_vb);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);
    Setup(shader, anim, frame);
    InitAttributes();
    glDrawElements(m_primitive, m_count, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * m_offset));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
