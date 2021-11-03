#include <monkey/imesh.h>
#include <monkey/engine.h>
#include <monkey/assets/tex.h>

void IMesh::addTexture(const std::string &file, TexType type) {
    auto tex = Engine::get().GetAssetManager().get<Tex>(file);
    m_textures.push_back({tex->GetTexId(), type});
}