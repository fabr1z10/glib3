#pragma once

#include <gfx/mesh.h>
#include <gfx/engine.h>

template <typename T>
class TexturedMesh : public Mesh<T> {
public:
    TexturedMesh(ShaderType type, GLenum prim, const std::string& filename) : Mesh<T>(type) {
        this->m_primitive = prim;
        auto tex = Engine::get().GetAssetManager().GetTex(filename);
        m_texId = tex->GetTexId();
    }
    void Setup(Shader* shader) override {
        auto texLoc = shader->GetUniformLocation(TEXTURE);
        glUniform1i(texLoc, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texId);
    }
private:
    GLuint m_texId;
};

