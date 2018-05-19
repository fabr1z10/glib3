#include <gfx/assetman.h>
#include <gfx/error.h>

void AssetManager::AddFont(const std::string &name, const std::string &file) {
    auto font = std::unique_ptr<Font>(new Font);
    font->loadFromFile(file);
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
    
    
}

Tex* AssetManager::GetTexture(const std::string& filename) {
    auto iter = m_textures.find(filename);
    if (iter == m_textures.end()) {
        std::string file = (m_directory + filename);
        try {
            std::unique_ptr<Tex> texture(new Tex(file, nearest));
            Tex* handle = texture.get();
            m_textures[file] = std::move(texture);
            return handle;
        }
        catch (std::exception& err) {
            
        }
    }
    return iter->second.get();
}

std::string AssetManager::GetDirectory() const {
    return m_directory;
}
