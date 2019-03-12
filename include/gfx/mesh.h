#pragma once

#include <gfx/imesh.h>
#include <vector>

template<class Vertex>
class Mesh : public IMesh {
public:
    Mesh(ShaderType type) : IMesh(type) {}
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
        Init(vertices, indices);
    }
    ~Mesh() {
        if (m_vb != INVALID_OGL_VALUE)
            glDeleteBuffers(1, &m_vb);
        if (m_ib != INVALID_OGL_VALUE)
            glDeleteBuffers(1, &m_ib);
    }

    void Init(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
        m_nvertices = vertices.size();
        m_nindices = indices.size();
        glGenBuffers(1, &m_vb);
        glGenBuffers(1, &m_ib);

        glBindBuffer(GL_ARRAY_BUFFER, m_vb);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
        m_bounds = ComputeBounds(vertices);
        m_bounds.min = m_localTransform * glm::vec4(m_bounds.min, 1.0f);
        m_bounds.max = m_localTransform * glm::vec4(m_bounds.max, 1.0f);
        m_indicesCount = indices.size();
    }

    virtual void InitAttributes() {
        Vertex::InitAttributes();
    }

};