#include <monkey/assetman.h>
#include <monkey/engine.h>
#include <monkey/lua/luatable.h>

namespace py = pybind11;

AssetManager::AssetManager() {
    SetLocal(false);
}

void AssetManager::Init() {

    auto& mt = Engine::get().getMainTable();
    auto assets = mt.get<py::dict>("data");

    m_fontDict = assets["assets"]["fonts"];
    m_modelDict = assets["assets"]["spritemodels"];
//    auto factory = Engine::get().GetSceneFactory();
//    m_fonts.Init("fonts", factory);
//    m_models.Init("models", factory);
//    m_textures.Init("tex", factory
//    );
}

std::shared_ptr<IModel> AssetManager::GetModel(const std::string & id) {
    // check if model is cached
    auto it = m_models.find(id);
    if (it != m_models.end()) {
        return it->second;
    }
    if (m_modelDict.is_none()) {
        
    } else {
        PyDict t(m_modelDict[id.c_str()].cast<py::dict>());
        auto font= Engine::get().GetSceneFactory()->make2<IModel>(t);
        m_models.insert(std::make_pair(id, font));
        return font;
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

void BasicAssetStore<Tex>::Init(const std::string &f, SceneFactory *sf) {

    IAssetStore<Tex>::Init(f, sf);
    m_gfxDir = Engine::get().GetGameDirectory() + "gfx/";
}

