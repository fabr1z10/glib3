#pragma once

#include <gfx/mesh.h>

class TexturedMesh : public Mesh<Vertex3D> {
public:
    TexturedMesh(GLenum prim, const std::string& filename);
    void Setup(Shader* shader) override;
private:
    GLuint m_texId;
};