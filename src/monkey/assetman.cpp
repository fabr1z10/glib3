#include <monkey/assetman.h>
#include <monkey/engine.h>
#include <monkey/lua/luatable.h>

namespace py = pybind11;

AssetManager::AssetManager() {
    SetLocal(false);
}

void AssetManager::Init() {

    auto& mt = Engine::get().getMainTable();
    auto assets = mt.get<py::dict>("assets");

    m_fontDict = assets["fonts"];

//    auto factory = Engine::get().GetSceneFactory();
//    m_fonts.Init("fonts", factory);
//    m_models.Init("models", factory);
//    m_textures.Init("tex", factory
//    );
}

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


std::shared_ptr<Tex> AssetManager::GetTex (const std::string& fontId) {
    // check if font is cached
    auto it = m_textures.find(fontId);
    if (it != m_textures.end()) {
        return it->second;
    }
    std::string file = Engine::get().GetGameDirectory() + fontId;
    auto tex = std::make_shared<Tex>(file);
    m_textures[fontId] = tex;
    return tex;
}
void AssetManager::SetLocal (bool value) {
    //m_fonts.SetLocal(value);
    //m_models.SetLocal(value);
    //m_textures.SetLocal(value);
}


void AssetManager::CleanUp() {
    //m_fonts.CleanUp();
    m_models.CleanUp();
    //m_textures.CleanUp();
}

void BasicAssetStore<Tex>::Init(const std::string &f, SceneFactory *sf) {

    IAssetStore<Tex>::Init(f, sf);
    m_gfxDir = Engine::get().GetGameDirectory() + "gfx/";
}

