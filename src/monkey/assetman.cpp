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
    if (m_fontDict.is_none()) {
    } else {
        PyTable t(m_fontDict["fontId"].cast<py::object>());
        Engine::get().GetSceneFactory()->make2<Font>(t);
    }
}
void AssetManager::SetLocal (bool value) {
    m_fonts.SetLocal(value);
    m_models.SetLocal(value);
    m_textures.SetLocal(value);
}


void AssetManager::CleanUp() {
    m_fonts.CleanUp();
    m_models.CleanUp();
    m_textures.CleanUp();
}

void BasicAssetStore<Tex>::Init(const std::string &f, SceneFactory *sf) {

    IAssetStore<Tex>::Init(f, sf);
    m_gfxDir = Engine::get().GetGameDirectory() + "gfx/";
}

