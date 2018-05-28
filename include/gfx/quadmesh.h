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

class QuadMesh : public Mesh<Vertex3D> {
public:
    QuadMesh(const std::string& filename, float width = 0.0f, float height = 0.0f, float repeatx = 1, float repeaty = 1);
    QuadMesh(const std::string& filename, int rows, int cols, float size, std::vector<int>& data, int sheetRows, int sheetCols);
    virtual void Setup(Shader*, const std::string&, int);
private:
    GLuint m_texId;
};

#endif /* quadmesh_h */
