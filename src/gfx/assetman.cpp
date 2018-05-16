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