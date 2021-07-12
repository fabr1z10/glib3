#pragma once

#include <monkey/imesh.h>
#include <monkey/engine.h>

template<class Vertex>
class __attribute__ ((visibility ("default"))) DynamicMesh : public IMesh {
public:
    DynamicMesh() = default;
    DynamicMesh(ShaderType type) : IMesh(type), m_texId(GL_INVALID) {}


    DynamicMesh(const ITab& t) : IMesh(t), m_texId(GL_INVALID)  {

    }

    ~DynamicMesh() {
        if (m_vb != INVALID_OGL_VALUE)
            glDeleteBuffers(1, &m_vb);
        if (m_ib != INVALID_OGL_VALUE)
            glDeleteBuffers(1, &m_ib);
    }

    void setTexture(const std::string& texName) {
        auto tex = Engine::get().GetAssetManager().GetTex(texName);
        m_texId = tex->GetTexId();
    }

    void Setup(Shader* shader) override {
        if (m_texId != GL_INVALID) {
            auto texLoc = shader->GetUniformLocation(TEXTURE);
            glUniform1i(texLoc, 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_texId);
        }
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
		m_nvertices = vertices.size();
		m_nindices = indices.size();
		m_init = true;
    }

    void UpdateGeometry(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices) {
    	if (!m_init) {
    		Init(vertices, indices);

    	} else {
			glBindBuffer(GL_ARRAY_BUFFER, m_vb);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);

			//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * vertices.size(), &vertices[0]);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);
			//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * indices.size(), &indices[0]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);
		}
    }


    virtual void InitAttributes() {
        Vertex::InitAttributes();
    }
	bool m_init;
    GLuint m_texId;

};