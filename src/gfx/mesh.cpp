//
//  mesh.cpp
//  glib
//
//  Created by Fabrizio Venturini on 06/05/2018.
//
//

#include "gfx/mesh.h"
#include "gfx/shader.h"
#include <gfx/error.h>

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


int IMesh::FrameCount(const std::string& anim) const {
    if (m_animInfo.empty()) return 1;
    // if the mesh has only one animation, just
    auto it = m_animInfo.find(anim);
    if (it == m_animInfo.end())
        GLIB_FAIL ("Don't know animation: " << anim);
    return it->second.size();
}

float IMesh::GetDuration(const std::string& anim, int frame) const {
    if (m_animInfo.empty()) return 1.0f;
    auto it = m_animInfo.find(anim);
    if (it == m_animInfo.end())
        GLIB_FAIL ("Don't know animation: " << anim);
    return it->second[frame].duration;
}