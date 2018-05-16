#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <gfx/font.h>

class AssetManager {
public:
    void AddFont(const std::string &name, const std::string &file);
    Font *GetFont(const std::string &) const;


private:
    std::unordered_map<std::string, std::unique_ptr<Font>> m_fonts;
};