#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <gfx/font.h>
#include <gfx/tex.h>
#include <gfx/mesh.h>
#include <gfx/imodel.h>
#include <gfx/lua/luawrapper.h>

class AssetManager {
public:
    void AddFont(const std::string &name, const std::string &file);
    Font *GetFont(const std::string &) const;
    Tex* GetTexture(const std::string&);

    void AddModel (const std::string& name, std::shared_ptr<IModel> mesh);
    void RemoveModel (const std::string& name);
    std::shared_ptr<IModel> GetModel(const std::string& name) const;

    luabridge::LuaRef GetMeshInfo (const std::string& name);
    void AddMeshInfo (const std::string& name, luabridge::LuaRef);
    void SetDirectory(const std::string&);
    std::string GetDirectory() const;

    void Clear();

    //void AddModel (const std::string& name, std::shared_ptr<Model> mesh);
    // void RemoveModel (const std::string& name);
    //std::shared_ptr<Model> GetModel (const std::string& name) const;



private:
    std::unordered_map<std::string, std::unique_ptr<Font>> m_fonts;
    std::unordered_map<std::string, std::unique_ptr<Tex>> m_textures;
    std::unordered_map<std::string, std::shared_ptr<IModel>> m_models;
    //std::unordered_map<std::string, std::shared_ptr<Model>> m_models;
    std::unordered_map<std::string, luabridge::LuaRef> m_meshAddInfo;
    std::string m_directory;
};
