#include <gfx/texturedmesh.h>
#include <gfx/engine.h>

TexturedMesh::TexturedMesh(GLenum prim, const std::string& filename) : Mesh<Vertex3D>(TEXTURE_SHADER) {
    m_primitive = prim;
    auto tex = Engine::get().GetAssetManager().GetTex(filename);
    m_texId = tex->GetTexId();
}

void TexturedMesh::Setup(Shader* shader)  {
    auto texLoc = shader->GetUniformLocation(TEXTURE);
    glUniform1i(texLoc, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texId);
}