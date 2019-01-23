#include <gfx/assetman.h>
#include <gfx/error.h>
#include <iostream>

void AssetManager::AddFont(const std::string &name, const std::string &file) {
    auto font = std::unique_ptr<Font>(new Font);
    font->loadFromFile(m_directory + file, 36);
    m_fonts[name] = std::move(font);
}

Font* AssetManager::GetFont(const std::string & name) const {
    auto it = m_fonts.find(name);
    if (it == m_fonts.end()) {
        GLIB_FAIL("Unknown font " << name);
    }
    return it->second.get();
}

void AssetManager::SetDirectory(const std::string& dir)
{
    m_directory = dir;
    if (m_directory.back() != '/')
        m_directory.push_back('/');
    
}

Tex* AssetManager::GetTexture(const std::string& filename) {
    auto iter = m_textures.find(filename);
    if (iter == m_textures.end()) {
        std::string file = (m_directory + filename);
        try {
            std::unique_ptr<Tex> texture(new Tex(file, nearest));
            Tex* handle = texture.get();
            m_textures[filename] = std::move(texture);
            return handle;
        }
        catch (std::exception& err) {
            GLIB_FAIL("Error opening image " << filename);
        }
    }
    return iter->second.get();
}

std::string AssetManager::GetDirectory() const {
    return m_directory;
}

void AssetManager::AddMesh (const std::string& name, std::shared_ptr<IMesh> mesh) {
    mesh->SetId(name);
    m_meshes[name] = mesh;
}

void AssetManager::RemoveMesh(const std::string& name){
    for (auto& m : m_meshes) {
        std::cout << m.first << ": ";
        std::cout << m.second->AnimationCount() << "\n";
    }
    m_meshes.erase(name);
}

std::shared_ptr<IMesh> AssetManager::GetMesh(const std::string& name) const {
    auto it = m_meshes.find(name);
    if (it == m_meshes.end()){
        GLIB_FAIL("Unknown mesh " << name);
    }
    return it->second;
}

luabridge::LuaRef AssetManager::GetMeshInfo (const std::string& name) {
    auto it = m_meshAddInfo.find(name);
    if (it == m_meshAddInfo.end())
        GLIB_FAIL("No additional mesh info for: " << name);
    return it->second;
}

void AssetManager::AddMeshInfo (const std::string& name, luabridge::LuaRef ref) {
    m_meshAddInfo.insert(std::make_pair(name, ref));
}

void AssetManager::Clear() {
    m_meshes.clear();
    m_textures.clear();
}