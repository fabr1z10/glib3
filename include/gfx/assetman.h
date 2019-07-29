#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <gfx/font.h>
#include <gfx/tex.h>
#include <gfx/mesh.h>
#include <gfx/imodel.h>
#include <gfx/skeletalanimation.h>
#include <gfx/error.h>
#include <gfx/lua/luawrapper.h>

template <typename T, typename Builder>
class AssetStore {
public:
    std::shared_ptr<T> Get (const std::string& id) {
        auto it = m_assets.find(id);
        if (it == m_assets.end()) {
            // try to build
            std::shared_ptr<T> asset = m_builder(id);
            if (asset == nullptr) {
                GLIB_FAIL("Cannot find or create asset: " << id);
            }

            m_assets[id] = asset;
            if (m_local) {
                m_localAssets.insert(id);
            }
            return asset;
        }
        return it->second;

    }
    void Init() {
     m_builder.Init();
    }
    void CleanUp() {
        for (const auto& s : m_localAssets) {
            std::cout << "### dropping asset " << s << "\n";
            m_assets.erase(s);
        }
        m_localAssets.clear();
    }
    void SetLocal(bool value) {
        m_local = value;
    }

private:
    bool m_local;
    Builder m_builder;
    std::unordered_map<std::string, std::shared_ptr<T>> m_assets;
    std::unordered_set<std::string> m_localAssets;
};

class FontBuilder {
public:
    void Init();
    std::shared_ptr<Font> operator() (const std::string&) const;
private:
    std::unique_ptr<luabridge::LuaRef> m_fontLocation;
};

class TexBuilder {
public:
    void Init();
    std::shared_ptr<Tex> operator() (const std::string&) const;
private:
    std::string m_gfxDirectory;
};

class ModelBuilder {
public:
    void Init();
    std::shared_ptr<IModel> operator() (const std::string&) const;
private:
    std::unique_ptr<luabridge::LuaRef> m_modelLocation;
};

class SkeletalAnimationBuilder {
public:
    void Init();
    std::shared_ptr<SkeletalAnimation> operator() (const std::string&) const;
private:
    std::unique_ptr<luabridge::LuaRef> m_modelLocation;
};



class AssetManager {
public:
    AssetManager();
    void Init();
    std::shared_ptr<Font> GetFont (const std::string&);
    std::shared_ptr<Tex> GetTex (const std::string&);
    std::shared_ptr<IModel> GetModel (const std::string&);
    std::shared_ptr<SkeletalAnimation> GetSkeletalAnimation (const std::string&);
    void SetLocal (bool);
    void CleanUp();
private:
    AssetStore<Font, FontBuilder> m_fonts2;
    AssetStore<Tex, TexBuilder> m_textures2;
    AssetStore<IModel, ModelBuilder> m_models2;
    AssetStore<SkeletalAnimation, SkeletalAnimationBuilder> m_skeletalAnimations;

};

inline std::shared_ptr<Font> AssetManager::GetFont (const std::string& id) {
    return m_fonts2.Get(id);
}

inline std::shared_ptr<Tex> AssetManager::GetTex (const std::string& id) {
    return m_textures2.Get(id);
}

inline std::shared_ptr<IModel> AssetManager::GetModel (const std::string& id) {
    return m_models2.Get(id);
}

inline std::shared_ptr<SkeletalAnimation> AssetManager::GetSkeletalAnimation(const std::string & id) {
    return m_skeletalAnimations.Get(id);
}
