#include <monkey/assetman.h>
#include <monkey/engine.h>
#include <monkey/scenefactory.h>


void AssetManager::init(const ITab & t, pybind11::object scripts) {
    m_assets = t["assets"];
    if (scripts.is_none()) {
        std::cerr << "no scripts available!\n";
    } else {
        m_scripts = scripts;
//
//
//        std::cerr << "fiwoirfj = " << m_scripts.attr("pollo").attr("ciao").attr("jingo").get_type() << "\n";
//        get<Func>("pollo.ciao.jingo");
//        get<Func>("pollo.ciao.jingo");
    }
   // m_scripts = t["scripts"];
    std::cerr << m_assets->has("001");
}

template<> std::shared_ptr<Font> AssetManager::get(const std::string& id) {
    auto it = m_fonts.find(id);
    if (it != m_fonts.end()) {
        return it->second;
    }
    // create the font
    // extract the itab
    auto assetDesc = m_assets->operator[](id);
    auto font = Engine::get().GetSceneFactory()->make2<Font>(*assetDesc.get());
    m_fonts[id] = font;
    return font;
}


template<> std::shared_ptr<Model> AssetManager::get(const std::string& id) {
    auto it = m_models.find(id);
    if (it != m_models.end()) {
        std::cout << "cache hit for " << id << "!\n";
        return it->second;
    }
    // create the model
    // extract the itab
    auto assetDesc = m_assets->operator[](id);
    auto model = Engine::get().GetSceneFactory()->make2<Model>(*assetDesc.get());
    m_models[id] = model;
    return model;
}

template<> std::shared_ptr<IMesh> AssetManager::get(const std::string& id) {
	auto it = m_meshes.find(id);
	if (it != m_meshes.end()) {
		std::cout << "cache hit for " << id << "!\n";
		return it->second;
	}
	// create the model
	// extract the itab
	auto assetDesc = m_assets->operator[](id);
	auto mesh = Engine::get().GetSceneFactory()->make2<IMesh>(*assetDesc.get());
	m_meshes[id] = mesh;
	return mesh;
}

template<> std::shared_ptr<SkAnimation> AssetManager::get(const std::string& id) {
    auto it = m_skeletalAnimations.find(id);
    if (it != m_skeletalAnimations.end()) {
        std::cout << "cache hit for " << id << "!\n";
        return it->second;
    }
    // create the model
    // extract the itab
    auto assetDesc = m_assets->operator[](id);
    auto anim = Engine::get().GetSceneFactory()->make2<SkAnimation>(*assetDesc.get());
    m_skeletalAnimations[id] = anim;
    return anim;
}

template<> std::shared_ptr<Tex> AssetManager::get(const std::string& texId) {
    auto it = m_textures.find(texId);
    if (it != m_textures.end()) {
        return it->second;
    }

    std::string file = Engine::get().GetGameDirectory() + texId;
    auto tex = std::make_shared<Tex>(file);
    m_textures[texId] = tex;
    return tex;
}

template<> std::shared_ptr<Func> AssetManager::get(const std::string& id) {
    std::stringstream test(id);
    std::string segment;
    pybind11::object tmp = m_scripts;
    while (std::getline(test, segment, '.'))
        tmp = tmp.attr(segment.c_str());
    std::cerr << "filo = " << tmp.get_type() << "\n";
    return std::make_shared<Func>(tmp);
}
//#include <monkey/engine.h>
//#include <monkey/texturedmesh.h>
//#include "yaml-cpp/yaml.h"
//#include <fstream>
//#include <monkey/input/yamltab.h>
//#include <monkey/input/pytab.h>
//
//namespace py = pybind11;
//
//AssetManager::AssetManager() {
//    SetLocal(false);
//
//}
//
//void AssetManager::Init() {
//
//    auto& mt = Engine::get().getMainTable();
//    auto assets = mt.get<py::object>("assets").cast<py::dict>();
//
//    m_fontDict = assets["fonts"];
//    m_modelDict = assets["models"];
//    m_skeletalAnimDict = assets["skeletal_animations"];
//    m_mesh = assets["mesh"];
//    this->m_factory = Engine::get().GetSceneFactory();
//    this->m_homeDir = Engine::get().GetGameDirectory();
//}
////PyDict AssetManager::getMeshTemplate(const std::string & id) {
////    return PyDict(m_mesh[id.c_str()]);
////}
//
//YAML::Node AssetManager::openFile(const std::string & id) {
//    std::stringstream stream;
//    auto l = id.find_last_of("/");
//    if (l == std::string::npos) {
//        GLIB_FAIL("mesh id must have the form: [location]/name")
//    }
//    std::string location = id.substr(0, l);
//    std::string asset_id = id.substr(l+1);
//    stream << Engine::get().GetGameDirectory() << "assets/" << id.substr(0, l) << ".yaml";
//
//    auto mm = YAML::LoadFile(stream.str().c_str());
//    return mm;
//}
//
//std::shared_ptr<ITab> AssetManager::getRaw(const std::string & locator) {
//	size_t n = locator.find_last_of("/");
//	auto file = openFile(locator);
//	for (const auto &i : file) {
//		if (i.first.as<std::string>() == locator.substr(n+1)) {
//			return std::make_shared<YAMLTab>((i.second));
//		}
//	}
//	return nullptr;
//
//}
//
//std::shared_ptr<IMesh> AssetManager::getMesh(const std::string & locator, const ITab& args) {
//    auto factory = Engine::get().GetSceneFactory();
//    // check if node template is cached.
//    auto iter = m_templates.find(locator);
//    if (iter != m_templates.end()) {
//        // ok, create
//        return factory->makeDynamicAsset<IMesh>(YAMLTab(iter->second), args);
//    }
//    std::string location = locator.substr(0, locator.find_last_of("/"));
//    auto file = openFile(locator);
//    for (const auto &i : file) {
//        m_templates[location + "/" + i.first.as<std::string>()] = i.second;
//    }
//    return factory->makeDynamicAsset<IMesh>(YAMLTab(m_templates.at(locator)), args);
//}
//
//std::shared_ptr<IMesh> AssetManager::GetMesh(const std::string & id) {
//	// check if the mesh is cached
//	auto iter = m_meshes.find(id);
//	if (iter != m_meshes.end()) {
//		return iter->second;
//	}
//    // open the file
//    std::stringstream stream;
//    auto l = id.find_last_of("/");
//    if (l == std::string::npos) {
//        GLIB_FAIL("mesh id must have the form: [location]/name")
//    }
//    std::string location = id.substr(0, l);
//    std::string asset_id = id.substr(l+1);
//
//    stream << Engine::get().GetGameDirectory() << "assets/" << id.substr(0, l) << ".yaml";
//
//    std::cerr << "# opening file: " << stream.str() << std::endl;
////    std::ifstream fin("test.yaml");
////    YAML::Parser parser(fin);
////
////    YAML::Node doc;
//    auto mm = YAML::LoadFile(stream.str().c_str());
//    std::cerr << mm.Type() << "\n";
//    auto factory = Engine::get().GetSceneFactory();
//    // store all models in this file
//    for (const auto &i : mm) {
//        std::cerr << i.first.as<std::string>() << std::endl;
//        auto model = factory->makeAsset<IMesh>(YAMLTab(i.second));
//
//        m_meshes[location + "/" + i.first.as<std::string>()] = model;
//        //std::cerr << i.second.as<std::string>() << std::endl;
//        //YAML::Emitter e;
//        //e << i.second;
//        //std::cerr << e.c_str();
//    }
//    return m_meshes.at(id);
//
//}
//
//
//std::shared_ptr<Model> AssetManager::getModel(const pybind11::object &obj) {
//    try {
//        auto id = obj.cast<std::string>();
//        return GetModel(id);
//    } catch(pybind11::cast_error&) {
//        auto tp = obj.cast<pybind11::tuple>();
//        auto id = tp[0].cast<std::string>();
//        auto args = PyTab(tp[1].cast<pybind11::dict>());
//        return genericLoaderArgs<Model>(id, args);
//        // TODO CIAPPO
//        //return nullptr;
//    }
//}
//
//std::shared_ptr<Model> AssetManager::GetModel(const std::string & id) {
//    return genericLoader<Model>(id, m_models);
//}
//
//
//
//std::shared_ptr<Font> AssetManager::GetFont (const std::string& fontId) {
//    // check if font is cached
//    auto it = m_fonts.find(fontId);
//    if (it != m_fonts.end()) {
//        return it->second;
//    }
//
//
//    if (m_fontDict.is_none()) {
//
//    } else {
//        PyTab t(m_fontDict[fontId.c_str()].cast<py::object>());
//        auto font= Engine::get().GetSceneFactory()->make2<Font>(t);
//        m_fonts.insert(std::make_pair(fontId, font));
//        return font;
//    }
//}
//
//std::shared_ptr<SkAnimation> AssetManager::getSkeletalAnimation(const ITab& id) {
//	auto str = id.as<std::string>("");
//	if (str.empty()) {
//		auto templateId = id[0]->as<std::string>();
//		auto args = id[1];
//		return genericLoaderArgs<SkAnimation>(templateId, *args.get());
//	} else {
//		return genericLoader<SkAnimation>(str, m_sanim);
//	}
//
//}
//
//std::shared_ptr<SkAnimation> AssetManager::getSkeletalAnimation(const std::string &id) {
//
//    return genericLoader<SkAnimation>(id, m_sanim);
////    auto it = m_sanim.find(id);
////    if (it != m_sanim.end()) {
////        return it->second;
////    }
////    else {
////        PyDict t(m_skeletalAnimDict[id.c_str()].cast<py::object>());
////
////        auto font= Engine::get().GetSceneFactory()->make2<SkAnimation>(t);
////        m_sanim.insert(std::make_pair(id, font));
////        return font;
////    }
//}
//
//
//std::shared_ptr<Tex> AssetManager::GetTex (const std::string& texId) {
//    // check if tex is cached
//    auto it = m_textures.find(texId);
//    if (it != m_textures.end()) {
//        return it->second;
//    }
//
//    std::string file = Engine::get().GetGameDirectory() + texId;
//    auto tex = std::make_shared<Tex>(file);
//    m_textures[texId] = tex;
//    return tex;
//}
//
//void AssetManager::SetLocal (bool value) {
//    //m_fonts.SetLocal(value);
//    //m_models.SetLocal(value);
//    //m_textures.SetLocal(value);
//}
//
//
//void AssetManager::CleanUp() {
//    //m_fonts.CleanUp();
//    //m_models.CleanUp();
//    //m_textures.CleanUp();
//}
//
