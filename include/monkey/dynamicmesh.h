#pragma once

#include <monkey/imesh.h>


template<class Vertex>
class DynamicMesh : public IMesh {
public:
    DynamicMesh() = default;
    DynamicMesh(ShaderType type) : IMesh(type) {}


    DynamicMesh(const ITab& t) : IMesh(t) {

    }


    ~DynamicMesh() {
        if (m_vb != INVALID_OGL_VALUE)
            glDeleteBuffers(1, &m_vb);
        if (m_ib != INVALID_OGL_VALUE)
            glDeleteBuffers(1, &m_ib);
    }

    void Init(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
        glGenBuffers(1, &m_vb);
        glGenBuffers(1, &m_ib);

        glBindBuffer(GL_ARRAY_BUFFER, m_vb);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);
        m_bounds = ComputeBounds(vertices);
        //m_bounds.min = m_localTransform * glm::vec4(m_bounds.min, 1.0f);
        //m_bounds.max = m_localTransform * glm::vec4(m_bounds.max, 1.0f);
        //m_indicesCount = indices.size();
    }

    void UpdateGeometry(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertices.size(), &vertices[0]);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * indices.size(), &indices[0]);
    }


    virtual void InitAttributes() {
        Vertex::InitAttributes();
    }

};