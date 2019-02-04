#include <gfx/assetman.h>
#include <gfx/error.h>
#include <iostream>

void AssetManager::AddFont(const std::string &name, const std::string &file) {
    auto font = std::make_shared<Font>();
    font->loadFromFile(m_directory + file, 36);
    m_fonts.insert(std::make_pair(name, font));
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
            auto texture = std::make_shared<Tex>(file, nearest);
            m_textures[filename] = texture;
            return texture.get();
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

void AssetManager::AddModel (const std::string& name, std::shared_ptr<IModel> mesh) {
    m_models[name] = mesh;
}

void AssetManager::RemoveModel(const std::string& name){
    m_models.erase(name);
}

bool AssetManager::HasModel(const std::string &name) const {
    return m_models.count(name) > 0;
}

std::shared_ptr<IModel> AssetManager::GetModel(const std::string& name) const {
    auto it = m_models.find(name);
    if (it == m_models.end()){
        GLIB_FAIL("Unknown model " << name);
    }
    return it->second;
}

void AssetManager::Clear() {
    m_models.clear();
    m_textures.clear();
}
