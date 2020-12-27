#include <monkey/assetman.h>
#include <monkey/engine.h>
#include <monkey/texturedmesh.h>

namespace py = pybind11;

AssetManager::AssetManager() {
    SetLocal(false);
}

void AssetManager::Init() {

    auto& mt = Engine::get().getMainTable();
    auto assets = mt.get<py::dict>("assets");

    m_fontDict = assets["fonts"];
    m_modelDict = assets["models"];
    m_skeletalAnimDict = assets["skeletal_animations"];
    m_mesh = assets["mesh"];
}
PyDict AssetManager::getMeshTemplate(const std::string & id) {
    return PyDict(m_mesh[id.c_str()]);
}

std::shared_ptr<IMesh> AssetManager::GetMesh(const std::string & id) {
	// check if the mesh is cached
	auto iter = m_meshes.find(id);
	if (iter != m_meshes.end()) {
		return iter->second;
	}

	PyDict t(m_mesh[id.c_str()]);
	auto mesh = Engine::get().GetSceneFactory()->make2<IMesh>(t);
	m_meshes.insert(std::make_pair(id, mesh));
	return mesh;


}

std::shared_ptr<IModel> AssetManager::GetModel(const std::string & id) {
    // check if model is cached
    auto it = m_models.find(id);
    if (it != m_models.end()) {
        return it->second;
    }
    if (m_modelDict.is_none()) {
        
    } else {
    	std::unique_ptr<ITable> t;
        try {
			t = std::make_unique<PyDict>(m_modelDict[id.c_str()].cast<py::dict>());
		} catch (...) {
        	t = std::make_unique<PyTable>(m_modelDict[id.c_str()].cast<py::dict>());
		}
		auto model = Engine::get().GetSceneFactory()->make2<IModel>(*(t.get()));
        if (model->isShareable())
            m_models.insert(std::make_pair(id, model));
        return model;
    }}


std::shared_ptr<Font> AssetManager::GetFont (const std::string& fontId) {
    // check if font is cached
    auto it = m_fonts.find(fontId);
    if (it != m_fonts.end()) {
        return it->second;
    }
    
    if (m_fontDict.is_none()) {
    
    } else {
        PyTable t(m_fontDict[fontId.c_str()].cast<py::object>());
        
        auto font= Engine::get().GetSceneFactory()->make2<Font>(t);
        m_fonts.insert(std::make_pair(fontId, font));
        return font;
    }
}


std::shared_ptr<SkAnimation> AssetManager::getSkeletalAnimation(const std::string &id) {
    auto it = m_sanim.find(id);
    if (it != m_sanim.end()) {
        return it->second;
    }
    else {
        PyDict t(m_skeletalAnimDict[id.c_str()].cast<py::object>());

        auto font= Engine::get().GetSceneFactory()->make2<SkAnimation>(t);
        m_sanim.insert(std::make_pair(id, font));
        return font;
    }
}


std::shared_ptr<Tex> AssetManager::GetTex (const std::string& texId) {
    // check if tex is cached
    auto it = m_textures.find(texId);
    if (it != m_textures.end()) {
        return it->second;
    }

    std::string file = Engine::get().GetGameDirectory() + texId;
    auto tex = std::make_shared<Tex>(file);
    m_textures[texId] = tex;
    return tex;
}

void AssetManager::SetLocal (bool value) {
    //m_fonts.SetLocal(value);
    //m_models.SetLocal(value);
    //m_textures.SetLocal(value);
}


void AssetManager::CleanUp() {
    //m_fonts.CleanUp();
    //m_models.CleanUp();
    //m_textures.CleanUp();
}

