//
//  quadmesh.cpp
//  glib
//
//  Created by Fabrizio Venturini on 19/05/2018.
//
//

#include <monkey/quadmesh.h>
#include <monkey/engine.h>

QuadMesh::QuadMesh(GLenum prim, const std::string& filename) : Mesh<Vertex3D>(TEXTURE_SHADER_UNLIT) {
    m_primitive = prim;
    auto tex = Engine::get().GetAssetManager().GetTex(filename);
    m_texId = tex->GetTexId();
}

QuadMesh::QuadMesh(const std::string& filename, float width, float height,
                   float repeatx, float repeaty, float skewx, float skewy, glm::vec2 offset) : Mesh<Vertex3D>(TEXTURE_SHADER_UNLIT) {
    m_primitive = GL_TRIANGLES;
    auto tex = Engine::get().GetAssetManager().GetTex(filename);
    m_texId = tex->GetTexId();

    if (width == 0) {
        if (height != 0) {
            width = repeatx* height * (static_cast<float>(tex->GetWidth())/tex->GetHeight());
        } else {
            width = tex->GetWidth() * repeatx;
            height = tex->GetHeight() * repeaty;
        }
    } else {
        if (height == 0) {
            height = width * (static_cast<float>(tex->GetHeight())/tex->GetWidth());
        } else {
            //height = tex->GetHeight() * repeaty;
        }
    }
    //width *= repeatx;
    //height *= repeaty;
    std::vector<Vertex3D> vertices;
    vertices = {
        {offset.x,         offset.y,          0, 0,               repeaty},
        {offset.x + width, offset.y,          0, repeatx,         repeaty + skewy},
        {offset.x + width, offset.y + height, 0, repeatx + skewx, 0},
        {offset.x,         offset.y + height, 0, skewx,           0}
    };
    std::vector<unsigned int> indices{ 0, 1, 3, 3, 2, 1 };
    Init(vertices, indices);
    
}

QuadMesh::QuadMesh(const std::string& filename, float width, float height, glm::vec2 offset, int tx, int ty, int tw, int th) : Mesh<Vertex3D>(TEXTURE_SHADER_UNLIT) {
    m_primitive = GL_TRIANGLES;
    auto tex = Engine::get().GetAssetManager().GetTex(filename);
    m_texId = tex->GetTexId();
    // if one dimension is zero, keep aspect ratio
    if (width == 0) {
        width = height * (static_cast<float>(tw)/th);
    }
    if (height == 0) {
        height = width * (static_cast<float>(th)/tw);
    }
    float texWidth = static_cast<float>(tex->GetWidth());
    float texHeight = static_cast<float>(tex->GetHeight());
    std::vector<Vertex3D> vertices;
    vertices = {
            {offset.x,         offset.y,          0, tx/texWidth, (ty+th)/texHeight },
            {offset.x + width, offset.y,          0, (tx+tw)/texWidth, (ty+th)/texHeight},
            {offset.x + width, offset.y + height, 0, (tx+tw)/texWidth, ty/texHeight},
            {offset.x,         offset.y + height, 0, tx/texWidth, ty/texHeight}
    };
    std::vector<unsigned int> indices{ 0, 1, 3, 3, 2, 1 };
    Init(vertices, indices);

}


QuadMesh::QuadMesh(
    const std::string& filename,
    int rows,
    int cols,
    float size,
    std::vector<int>& data,
    int spriteSheetRows,
    int spriteSheetCols,
    int repx,
    int repy,
    glm::vec2 delta, float angle)
: Mesh<Vertex3D>(TEXTURE_SHADER_UNLIT) {
    m_primitive = GL_TRIANGLES;
    auto tex = Engine::get().GetAssetManager().GetTex(filename);
    m_texId = tex->GetTexId();
    std::vector<Vertex3D> vertices;
    std::vector<unsigned int> indices;
    int count = 0;
    int quad = 0;
    float dx = 1.0f / spriteSheetCols;
    float dy = 1.0f / spriteSheetRows;
    int inc = 2;
    if (data.size() == 2) {
        inc = 0;
    }

    float q = size;
    float r = 0.0f;
    if (angle != 0.0f) {
        q = size * cos(angle);
        r = size * sin(angle);
    }
    for (int rx = 0; rx < repx; ++rx) {
        for (int ry = 0; ry < repy; ++ry) {
            glm::vec2 o (
                cols * rx * q + delta.x * rx * q,
                cols * rx * r + delta.y * ry * r);
            count = 0;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    if (data[count] == -1)
                    {
                        count++;
                        continue;
                    }
                    int t1 = data[count];
                    int t2 = data[count + 1];
                    // bottom left
                    vertices.emplace_back(Vertex3D(o.x + j*q,       o.y + j*r + i * size,       0.0f, t1*dx, (t2 + 1) * dy));
                    // bottom right
                    vertices.emplace_back(Vertex3D(o.x + (j + 1)*q, o.y + (j+1)*r + i*size,     0.0f, (t1 + 1)*dx, (t2 + 1)*dy));
                    // top right
                    vertices.emplace_back(Vertex3D(o.x + (j + 1)*q, o.y + (j+1)*r + (i+1)*size, 0.0f, (t1 + 1)*dx, t2*dy));
                    // top left
                    vertices.emplace_back(Vertex3D(o.x + j*q,       o.y + j*r +(i + 1)*size,    0.0f, t1*dx, t2*dy));
                    indices.push_back(4 * quad);
                    indices.push_back(4 * quad + 1);
                    indices.push_back(4 * quad + 3);
                    indices.push_back(4 * quad + 1);
                    indices.push_back(4 * quad + 2);
                    indices.push_back(4 * quad + 3);
                    count += inc;
                    quad++;
                }
            }
        }
    }

    Init(vertices, indices);
    
}

void QuadMesh::Setup(Shader* shader) {
    shader->setInt("texture_diffuse1", 0);
//    auto texLoc = shader->GetUniformLocation(TEXTURE);
//    glUniform1i(texLoc, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texId);
}
