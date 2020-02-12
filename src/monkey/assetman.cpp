#include <monkey/assetman.h>
#include <monkey/engine.h>
#include <monkey/lua/luatable.h>

AssetManager::AssetManager() {
    SetLocal(false);
}

void AssetManager::Init() {
    auto factory = Engine::get().GetSceneFactory();
    m_fonts.Init("fonts", factory);
    m_models.Init("models", factory);
    m_textures.Init("tex", factory
    );
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

