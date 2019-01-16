#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <gfx/font.h>
#include <gfx/tex.h>
#include <gfx/mesh.h>
#include <gfx/lua/luawrapper.h>

class AssetManager {
public:
    void AddFont(const std::string &name, const std::string &file);
    Font *GetFont(const std::string &) const;
    Tex* GetTexture(const std::string&);
    void AddMesh (const std::string& name, std::shared_ptr<IMesh> mesh);
    void RemoveMesh (const std::string& name);
    luabridge::LuaRef GetMeshInfo (const std::string& name);
    void AddMeshInfo (const std::string& name, luabridge::LuaRef);
    std::shared_ptr<IMesh> GetMesh(const std::string& name) const;

    void SetDirectory(const std::string&);
    std::string GetDirectory() const;
private:
    std::unordered_map<std::string, std::unique_ptr<Font>> m_fonts;
    std::unordered_map<std::string, std::unique_ptr<Tex>> m_textures;
    std::unordered_map<std::string, std::shared_ptr<IMesh>> m_meshes;
    std::unordered_map<std::string, luabridge::LuaRef> m_meshAddInfo;
    std::string m_directory;
};
