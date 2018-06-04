#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <gfx/font.h>
#include <gfx/tex.h>
#include <gfx/mesh.h>

class AssetManager {
public:
    void AddFont(const std::string &name, const std::string &file);
    Font *GetFont(const std::string &) const;
    Tex* GetTexture(const std::string&);
    void AddMesh (const std::string& name, std::shared_ptr<IMesh> mesh);
    void RemoveMesh (const std::string& name);
    std::shared_ptr<IMesh> GetMesh(const std::string& name) const;

    void SetDirectory(const std::string&);
    std::string GetDirectory() const;
private:
    std::unordered_map<std::string, std::unique_ptr<Font>> m_fonts;
    std::unordered_map<std::string, std::unique_ptr<Tex>> m_textures;
    std::unordered_map<std::string, std::shared_ptr<IMesh>> m_meshes;
    std::string m_directory;
};
