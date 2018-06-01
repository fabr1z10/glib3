#include <gfx/spritemesh.h>
#include <gfx/shader.h>
#include <gfx/error.h>
#include <gfx/engine.h>

SpriteMesh::SpriteMesh (float ppu, const std::string& filename, std::vector<Animation>& data) : Mesh<Vertex3D>(TEXTURE_SHADER) {
    m_primitive = GL_TRIANGLES;

    std::vector<Vertex3D> vertices;
    std::vector<unsigned int> indices;

    auto tex = Engine::get().GetAssetManager().GetTexture(filename);
    m_texId = tex->GetTexId();
    float texWidth = static_cast<float>(tex->GetWidth());
    float texHeight = static_cast<float>(tex->GetHeight());
    int quadCount {0};
    for (auto& anim : data) {


        std::vector<FrameInfo> frameInfos;
        for (auto& frame : anim.frames) {
            frameInfos.push_back(FrameInfo{6*quadCount, 6*static_cast<int>(frame.quads.size()), frame.time});
            for (auto& quad : frame.quads) {
                glm::vec2 bottomLeft (-quad.anchorx, -quad.anchory);
                float tx = quad.x / texWidth;
                float ty = quad.y / texHeight;
                float tw = quad.width / texWidth;
                float th = quad.height / texHeight;
                float width = quad.width / ppu;
                float height = quad.height / ppu;
                vertices.push_back(Vertex3D(bottomLeft.x, bottomLeft.y, 0.0f, tx, ty + th));
                vertices.push_back(Vertex3D(bottomLeft.x + width, bottomLeft.y, 0.0f, tx + tw, ty + th));
                vertices.push_back(Vertex3D(bottomLeft.x + width, bottomLeft.y + height, 0.0f, tx + tw, ty));
                vertices.push_back(Vertex3D(bottomLeft.x, bottomLeft.y + height, 0.0f, tx, ty));
                int ix = quadCount * 4;
                indices.push_back(ix);
                indices.push_back(ix + 1);
                indices.push_back(ix + 3);
                indices.push_back(ix + 3);
                indices.push_back(ix + 2);
                indices.push_back(ix + 1);
                quadCount++;
            }

        }
        m_animInfo.insert(std::make_pair(anim.name, frameInfos));
    }
    Init(vertices, indices);

}

void SpriteMesh::Setup(Shader* shader, const std::string& anim, int frame) {
    auto texLoc = shader->GetUniformLocation(TEXTURE);
    glUniform1i(texLoc, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texId);
    auto it = m_animInfo.find(anim);
    if (it == m_animInfo.end()) {
        GLIB_FAIL("Don't have animation: " << anim);
    }

    std::vector<FrameInfo>& aInfo = it->second;
    if (frame < 0 || frame >= aInfo.size()) {
        GLIB_FAIL("Animation " << anim << " has frames 0 to " << aInfo.size()-1 << ": requested frame " << frame);
    }
    m_offset = aInfo[frame].offset;
    m_count = aInfo[frame].count;
}
