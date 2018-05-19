#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <gfx/font.h>
#include <gfx/tex.h>

class AssetManager {
public:
    void AddFont(const std::string &name, const std::string &file);
    Font *GetFont(const std::string &) const;
    Tex* GetTexture(const std::string&);

    void SetDirectory(const std::string&);
    std::string GetDirectory() const;
private:
    std::unordered_map<std::string, std::unique_ptr<Font>> m_fonts;
    std::unordered_map<std::string, std::unique_ptr<Tex>> m_textures;
    std::string m_directory;
};
