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


// rename this as texturedmesh
class QuadMesh : public Mesh<Vertex3D> {
public:
    QuadMesh (GLenum prim, const std::string& filename);
    QuadMesh (const std::string& filename,
             float width = 0.0f, float height = 0.0f, float repeatx = 1, float repeaty = 1,
             float skewx = 0.0f, float skewy = 0.0f, glm::vec2 offset = glm::vec2(0.0f));
    QuadMesh (const std::string& filename, float width, float height, glm::vec2 offset, int tx, int ty, int tw, int th);
    QuadMesh(const std::string& filename, int rows, int cols, float size, std::vector<int>& data, int sheetRows, int sheetCols);
    virtual void Setup(Shader*);
private:
    GLuint m_texId;
};

#endif /* quadmesh_h */
