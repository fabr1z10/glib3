//
//  quadmesh.cpp
//  glib
//
//  Created by Fabrizio Venturini on 19/05/2018.
//
//

#include <gfx/quadmesh.h>
#include <gfx/engine.h>

QuadMesh::QuadMesh(const std::string& filename, float width, float height, float repeatx, float repeaty) : Mesh<Vertex3D>(TEXTURE_SHADER) {
    m_primitive = GL_TRIANGLES;
    auto tex = Engine::get().GetAssetManager().GetTexture(filename);
    m_texId = tex->GetTexId();
    std::vector<Vertex3D> vertices{
        {0, 0, 0, 0, repeaty},
        {width, 0, 0, repeatx, repeaty},
        {width, height, 0, repeatx, 0},
        {0, height, 0, 0, 0}
    };
    std::vector<unsigned int> indices{ 0, 1, 3, 3, 2, 1 };
    Init(vertices, indices);
    
}

QuadMesh::QuadMesh(const std::string& filename, int rows, int cols, float size, std::vector<int>& data, int spriteSheetRows, int spriteSheetCols)
: Mesh<Vertex3D>(TEXTURE_SHADER) {
    m_primitive = GL_TRIANGLES;
    auto tex = Engine::get().GetAssetManager().GetTexture(filename);
    m_texId = tex->GetTexId();
    std::vector<Vertex3D> vertices;
    std::vector<unsigned int> indices;
    int count = 0;
    int quad = 0;
    float dx = 1.0f / spriteSheetCols;
    float dy = 1.0f / spriteSheetRows;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (data[count] == -1)
            {
                count++;
                continue;
            }
            int t1 = data[count];
            int t2 = data[count + 1];
            vertices.push_back(Vertex3D(j*size, i*size, 0.0f, t1*dx, (t2 + 1) * dy));
            vertices.push_back(Vertex3D((j + 1)*size, i*size, 0.0f, (t1 + 1)*dx, (t2 + 1)*dx));
            vertices.push_back(Vertex3D((j + 1)*size, (i + 1)*size, 0.0f, (t1 + 1)*dx, t2*dy));
            vertices.push_back(Vertex3D(j*size, (i + 1)*size, 0.0f, t1*dx, t2*dy));
            indices.push_back(4 * quad);
            indices.push_back(4 * quad + 1);
            indices.push_back(4 * quad + 3);
            indices.push_back(4 * quad + 1);
            indices.push_back(4 * quad + 2);
            indices.push_back(4 * quad + 3);
            count += 2;
            quad++;
        }
    }
    Init(vertices, indices);
    
}

void QuadMesh::Setup(Shader* shader, const std::string&, int) {
    auto texLoc = shader->GetUniformLocation(TEXTURE);
    glUniform1i(texLoc, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texId);
}
