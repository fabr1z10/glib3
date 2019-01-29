#include <gfx/spritemesh.h>


SpriteMesh::SpriteMesh (const std::string& filename) : TexturedMesh(GL_TRIANGLES, filename) {}

const AnimInfo* SpriteMesh::GetAnimInfo(const std::string& anim) const {
    auto it = m_info.find(anim);

    if (it != m_info.end()) {
        return &it->second;
    }
    return nullptr;
    // throw
}
