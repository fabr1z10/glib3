//
//  quadmesh.h
//  glib
//
//  Created by Fabrizio Venturini on 19/05/2018.
//
//

#ifndef quadmesh_h
#define quadmesh_h

#include <gfx/mesh.h>
#include <string>
#include <gfx/engine.h>
#include <gfx/assetman.h>

enum class Plane {
    XY, XZ
};

template <class Vertex>
class TexturedMesh : public Mesh<Vertex> {
public:
    TexturedMesh(ShaderType stype, GLenum prim, const std::string& filename) : Mesh<Vertex>(stype) {
        this->m_primitive = prim;
        auto tex = Engine::get().GetAssetManager().GetTexture(filename);
        m_texId = tex->GetTexId();
    }
    void Setup(Shader* shader, const std::string&, int) override {
        auto texLoc = shader->GetUniformLocation(TEXTURE);
        glUniform1i(texLoc, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texId);
    }
private:
    GLuint m_texId;
};

// rename this as texturedmesh
class QuadMesh : public Mesh<Vertex3D> {
public:
    QuadMesh (GLenum prim, const std::string& filename);
    QuadMesh (const std::string& filename,
             float width = 0.0f, float height = 0.0f, float repeatx = 1, float repeaty = 1,
             float skewx = 0.0f, float skewy = 0.0f, glm::vec2 offset = glm::vec2(0.0f), Plane p = Plane::XY);
    QuadMesh(const std::string& filename, int rows, int cols, float size, std::vector<int>& data, int sheetRows, int sheetCols);
    virtual void Setup(Shader*, const std::string&, int);
private:
    GLuint m_texId;
};

#endif /* quadmesh_h */
