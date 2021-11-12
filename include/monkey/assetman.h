#pragma once




#include <monkey/assets/font.h>
#include <monkey/assets/tex.h>
#include <monkey/assets/model.h>
#include <monkey/skeletal/animation.hpp>
#include <monkey/assets/skeletalanimation.h>
#include <monkey/input/yamltab.h>
#include <monkey/assets/func.h>


class AssetManager {
public:

    AssetManager() = default;

    void init(const ITab&, pybind11::object scripts);

    template <typename T>
    std::shared_ptr<T> get(const std::string& id) {
        GLIB_FAIL("IMMM");
    }


private:
    std::unique_ptr<ITab> m_assets;
    pybind11::module m_scripts;
   // std::unique_ptr<ITab> m_scripts;
    std::unordered_map<std::string, std::shared_ptr<Font> > m_fonts;
    std::unordered_map<std::string, std::shared_ptr<Model> > m_models;
    std::unordered_map<std::string, std::shared_ptr<Tex> > m_textures;
    //std::unordered_map<std::string, std::shared_ptr<Func> > m_scr;
    //std::unordered_map<std::string, std::shared_ptr<SkAnimation> > m_sanim;
};

template<> std::shared_ptr<Font> AssetManager::get(const std::string& id);

template<> std::shared_ptr<Model> AssetManager::get(const std::string& id);

template<> std::shared_ptr<Tex> AssetManager::get(const std::string& id);

template<> std::shared_ptr<Func> AssetManager::get(const std::string& id);

//
////template <typename T>
////class IAssetStore {
////private:
////    virtual std::shared_ptr<T> create(const std::string& id) = 0;
////public:
////    std::shared_ptr<T> Get (const std::string& id) {
////
////        auto it = m_assets.find(id);
////        if (it == m_assets.end()) {
////            auto asset = create(id);
////            m_assets.insert(std::make_pair(id, asset));
////            if (m_local) {
////                m_localAssets.insert(id);
////            }
////            return asset;
////        }
////        return it->second;
////    }
////
////    virtual void Init(const std::string& f, SceneFactory* sf) {
////        m_factory = sf;
////    }
////
////    void CleanUp() {
////        for (const auto& s : m_localAssets) {
////            std::cout << "### dropping asset " << s << "\n";
////            m_assets.erase(s);
////        }
////        m_localAssets.clear();
////    }
////    void SetLocal(bool value) {
////        m_local = value;
////    }
////
////protected:
////    bool m_local;
////    std::unordered_map<std::string, std::shared_ptr<T>> m_assets;
////    std::unordered_set<std::string> m_localAssets;
////    SceneFactory* m_factory;
////};
//
//
//
//
//
//class __attribute__ ((visibility ("default"))) AssetManager {
//public:
//    AssetManager();
//    void Init();
//    std::shared_ptr<Model> getModel (const pybind11::object& obj);
//
//
//    std::shared_ptr<Font> GetFont (const std::string& loc);
//    std::shared_ptr<Tex> GetTex (const std::string& loc);
//
//    std::shared_ptr<Model> GetModel (const std::string&);
//    std::shared_ptr<IMesh> GetMesh (const std::string&);
//
//	std::shared_ptr<SkAnimation> getSkeletalAnimation(const ITab&);
//    std::shared_ptr<SkAnimation> getSkeletalAnimation(const std::string &);
//
//    // support for dynamic model / meshes
//    std::shared_ptr<IMesh> getMesh (const std::string&, const ITab& args);
//
//    std::shared_ptr<ITab> getRaw(const std::string&);
//
//    void SetLocal (bool);
//    void CleanUp();
//
//    template<typename T>
//    std::shared_ptr<T> genericLoaderArgs (const std::string& id, const ITab& args) {
//        // check if node template is cached.
//        auto iter = m_templates.find(id);
//        if (iter != m_templates.end()) {
//            // ok, create
//            return m_factory->makeDynamicAsset<T>(YAMLTab(iter->second), args);
//        }
//        std::string location = id.substr(0, id.find_last_of("/"));
//        auto file = openFile(id);
//        for (const auto &i : file) {
//            m_templates[location + "/" + i.first.as<std::string>()] = i.second;
//        }
//        return m_factory->makeDynamicAsset<T>(YAMLTab(m_templates.at(id)), args);
//    }
//
//    template<typename T>
//    std::shared_ptr<T> genericLoader (const std::string& id, std::unordered_map<std::string, std::shared_ptr<T> >& store) {
//        // check if model is cached
//        auto it = store.find(id);
//        if (it != store.end()) {
//            return it->second;
//        }
//
//        // open the file
//        std::stringstream stream;
//        auto l = id.find_last_of("/");
//        if (l == std::string::npos) {
//            GLIB_FAIL("model id must have the form: [location]/name")
//        }
//        std::string location = id.substr(0, l);
//        std::string asset_id = id.substr(l+1);
//
//        stream << m_homeDir << "assets/" << id.substr(0, l) << ".yaml";
//
//        std::cerr << "# opening file: " << stream.str() << std::endl;
//
//        auto mm = YAML::LoadFile(stream.str().c_str());
//        std::cerr << mm.Type() << "\n";
//
//        // store all models in this file
//        for (const auto &i : mm) {
//            std::cerr << i.first.as<std::string>() << std::endl;
//            auto asset = m_factory->makeAsset<T>(YAMLTab(i.second));
//            store[location + "/" + i.first.as<std::string>()] = asset;
//        }
//        return store.at(id);
//
//    }
//private:
//    YAML::Node openFile(const std::string&);
//    pybind11::dict m_fontDict;
//    pybind11::dict m_modelDict;
//    pybind11::dict m_skeletalAnimDict;
//    pybind11::dict m_mesh;
//
//    std::unordered_map<std::string, std::shared_ptr<Font> > m_fonts;
//    std::unordered_map<std::string, std::shared_ptr<Model> > m_models;
//    std::unordered_map<std::string, std::shared_ptr<IMesh> > m_meshes;
//    std::unordered_map<std::string, std::shared_ptr<Tex> > m_textures;
//    std::unordered_map<std::string, std::shared_ptr<SkAnimation> > m_sanim;
//
//    // support for dynamic assets
//    std::unordered_map<std::string, YAML::Node> m_templates;
//    //std::unordered_map<std::string, YAML::Node> m_modelTemplate;
//    SceneFactory* m_factory;
//    std::string m_homeDir;
//    //BasicAssetStore<Font> m_fonts;
//    //BasicAssetStore<Tex> m_textures;
//    //BasicAssetStore<IModel> m_models;
//    //BasicAssetStore<SkeletalAnimation> m_skeletalAnimations;
//};
//
//
//
//
//


