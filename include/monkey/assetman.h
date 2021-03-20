#pragma once

#include <monkey/scenefactory.h>


#include <monkey/assets/font.h>
#include <monkey/assets/tex.h>
#include <monkey/assets/imodel.h>
#include <monkey/skeletal/animation.hpp>
#include <monkey/assets/skeletalanimation.h>

//template <typename T>
//class IAssetStore {
//private:
//    virtual std::shared_ptr<T> create(const std::string& id) = 0;
//public:
//    std::shared_ptr<T> Get (const std::string& id) {
//
//        auto it = m_assets.find(id);
//        if (it == m_assets.end()) {
//            auto asset = create(id);
//            m_assets.insert(std::make_pair(id, asset));
//            if (m_local) {
//                m_localAssets.insert(id);
//            }
//            return asset;
//        }
//        return it->second;
//    }
//
//    virtual void Init(const std::string& f, SceneFactory* sf) {
//        m_factory = sf;
//    }
//
//    void CleanUp() {
//        for (const auto& s : m_localAssets) {
//            std::cout << "### dropping asset " << s << "\n";
//            m_assets.erase(s);
//        }
//        m_localAssets.clear();
//    }
//    void SetLocal(bool value) {
//        m_local = value;
//    }
//
//protected:
//    bool m_local;
//    std::unordered_map<std::string, std::shared_ptr<T>> m_assets;
//    std::unordered_set<std::string> m_localAssets;
//    SceneFactory* m_factory;
//};





class AssetManager {
public:
    AssetManager();
    void Init();


    std::shared_ptr<Font> GetFont (const std::string& loc);
    std::shared_ptr<Tex> GetTex (const std::string& loc);

    std::shared_ptr<IModel> GetModel (const std::string&);
    std::shared_ptr<IMesh> GetMesh (const std::string&);
    std::shared_ptr<SkAnimation> getSkeletalAnimation(const std::string &);

    // support for dynamic model / meshes
    std::shared_ptr<IMesh> getMesh (const std::string&, const YAML::Node& args);


    void SetLocal (bool);
    void CleanUp();

    template<typename T>
    std::shared_ptr<T> genericLoader (const std::string& id, std::unordered_map<std::string, std::shared_ptr<T> >& store) {
        // check if model is cached
        auto it = store.find(id);
        if (it != store.end()) {
            return it->second;
        }

        // open the file
        std::stringstream stream;
        auto l = id.find_last_of("/");
        if (l == std::string::npos) {
            GLIB_FAIL("model id must have the form: [location]/name")
        }
        std::string location = id.substr(0, l);
        std::string asset_id = id.substr(l+1);

        stream << m_homeDir << "assets/" << id.substr(0, l) << ".yaml";

        std::cerr << "# opening file: " << stream.str() << std::endl;

        auto mm = YAML::LoadFile(stream.str().c_str());
        std::cerr << mm.Type() << "\n";

        // store all models in this file
        for (const auto &i : mm) {
            std::cerr << i.first.as<std::string>() << std::endl;
            auto asset = m_factory->makeAsset<T>(i.second);
            store[location + "/" + i.first.as<std::string>()] = asset;
        }
        return store.at(id);

    }
    //PyDict getMeshTemplate (const std::string&);
private:
    YAML::Node openFile(const std::string&);
    pybind11::dict m_fontDict;
    pybind11::dict m_modelDict;
    pybind11::dict m_skeletalAnimDict;
    pybind11::dict m_mesh;

    std::unordered_map<std::string, std::shared_ptr<Font> > m_fonts;
    std::unordered_map<std::string, std::shared_ptr<IModel> > m_models;
    std::unordered_map<std::string, std::shared_ptr<IMesh> > m_meshes;
    std::unordered_map<std::string, std::shared_ptr<Tex> > m_textures;
    std::unordered_map<std::string, std::shared_ptr<SkAnimation> > m_sanim;

    // support for dynamic assets
    std::unordered_map<std::string, YAML::Node> m_meshTemplate;
    std::unordered_map<std::string, YAML::Node> m_modelTemplate;
    SceneFactory* m_factory;
    std::string m_homeDir;
    //BasicAssetStore<Font> m_fonts;
    //BasicAssetStore<Tex> m_textures;
    //BasicAssetStore<IModel> m_models;
    //BasicAssetStore<SkeletalAnimation> m_skeletalAnimations;
};







