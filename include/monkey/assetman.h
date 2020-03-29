#pragma once

#include <monkey/scenefactory.h>

#include <monkey/assets/font.h>
#include <monkey/assets/tex.h>
#include <monkey/assets/imodel.h>
#include <monkey/assets/skeletalanimation.h>

template <typename T>
class IAssetStore {
private:
    virtual std::shared_ptr<T> create(const std::string& id) = 0;
public:
    std::shared_ptr<T> Get (const std::string& id) {

        auto it = m_assets.find(id);
        if (it == m_assets.end()) {
            auto asset = create(id);
            m_assets.insert(std::make_pair(id, asset));
            if (m_local) {
                m_localAssets.insert(id);
            }
            return asset;
        }
        return it->second;
    }

    virtual void Init(const std::string& f, SceneFactory* sf) {
        m_factory = sf;
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

protected:
    bool m_local;
    std::unordered_map<std::string, std::shared_ptr<T>> m_assets;
    std::unordered_set<std::string> m_localAssets;
    std::unique_ptr<luabridge::LuaRef> loc;
    SceneFactory* m_factory;
};

template <typename T>
class BasicAssetStore : public IAssetStore<T> {
private:
    std::shared_ptr<T> create(const std::string& id) override {
        luabridge::LuaRef modelDef = IAssetStore<T>::loc->operator[](id);
        if (modelDef.isNil()) {
            GLIB_FAIL("Unknown asset: " << id);
            return nullptr;
        }
        LuaTable table(modelDef);
        auto asset = IAssetStore<T>::m_factory->template make<T>(table);
        return asset;
    }
public:
    void Init(const std::string& f, SceneFactory* sf) override {
        IAssetStore<T>::Init(f, sf);
        try {
            IAssetStore<T>::loc = std::make_unique<luabridge::LuaRef>(LuaWrapper::GetGlobalPath({"engine", "assets", f}));
        } catch (const Error& e) {
            std::cerr << e.what()<<std::endl;
        }
    }


};

template <>
class BasicAssetStore<Tex> : public IAssetStore<Tex> {
private:
    std::shared_ptr<Tex> create(const std::string& id) override {
        std::string fileName = m_gfxDir + id;
        std::shared_ptr<Tex> tex = std::make_shared<Tex>(fileName);
        return tex;

    }

    std::string m_gfxDir;
public:
    void Init(const std::string& f, SceneFactory* sf) override;
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
    pybind11::dict m_fontDict;
    pybind11::dict m_modelDict;

    std::unordered_map<std::string, std::shared_ptr<Font> > m_fonts;
    std::unordered_map<std::string, std::shared_ptr<IModel> > m_models;
    std::unordered_map<std::string, std::shared_ptr<Tex> > m_textures;

    //BasicAssetStore<Font> m_fonts;
    //BasicAssetStore<Tex> m_textures;
    //BasicAssetStore<IModel> m_models;
    BasicAssetStore<SkeletalAnimation> m_skeletalAnimations;
};






inline std::shared_ptr<SkeletalAnimation> AssetManager::GetSkeletalAnimation(const std::string & id) {
    return m_skeletalAnimations.Get(id);
}

