#include <gfx/assetman.h>
#include <gfx/engine.h>
#include <gfx/lua/luatable.h>

AssetManager::AssetManager() {
    SetLocal(false);
}

std::shared_ptr<Font> FontBuilder::operator()(const std::string & fontId) const {
    std::cout << "*** load font " << fontId << " ... \n";
    luabridge::LuaRef fonts = LuaWrapper::GetGlobal("fonts");
    luabridge::LuaRef font = fonts[fontId];
    if (font.isNil()) {
        return nullptr;
    }
    LuaTable table(font);
    std::string file = table.Get<std::string>("file");
    if (file[0] == '.') {
        file.replace(0, 2, Engine::get().GetDirectory());
    }
    auto f = std::make_shared<Font>();
    f->loadFromFile(file, 36);
    return f;
}

std::shared_ptr<IModel> ModelBuilder::operator()(const std::string & modelId) const {

    luabridge::LuaRef modelsDef = LuaWrapper::GetGlobal("models");
    if (modelsDef.isNil()) {
        GLIB_FAIL("No models available!")
    }
    std::cout << "*** load asset " << modelId << " ... \n";
    luabridge::LuaRef modelDef = modelsDef[modelId];
    if (modelDef.isNil()) {
        return nullptr;
    }
    auto asset = Engine::get().GetSceneFactory()->makeModel(modelDef);
    return asset;
}

std::shared_ptr<Tex> TexBuilder::operator()(const std::string & file) const {
    std::cout << "*** loading texture " << file << "...\n";

    std::string fileName = Engine::get().GetDirectory() + file;
    auto texture = std::make_shared<Tex>(fileName, nearest);
    return texture;
}

void AssetManager::SetLocal (bool value) {
    m_fonts2.SetLocal(value);
    m_models2.SetLocal(value);
    m_textures2.SetLocal(value);
}


void AssetManager::CleanUp() {
    m_fonts2.CleanUp();
    m_models2.CleanUp();
    m_textures2.CleanUp();
}

//void AssetManager::AddFont(const std::string &name, const std::string &file) {
//    auto font = std::make_shared<Font>();
//    font->loadFromFile(m_directory + file, 36);
//    m_fonts.insert(std::make_pair(name, font));
//}

//Font* AssetManager::GetFont(const std::string & name) const {
//    auto it = m_fonts.find(name);
//    if (it == m_fonts.end()) {
//        GLIB_FAIL("Unknown font " << name);
//    }
//    return it->second.get();
//}

//
//
//Tex* AssetManager::GetTexture(const std::string& filename) {
//    auto iter = m_textures.find(filename);
//    if (iter == m_textures.end()) {
//        std::string file = (m_directory + filename);
//        try {
//            auto texture = std::make_shared<Tex>(file, nearest);
//            m_textures[filename] = texture;
//            return texture.get();
//        }
//        catch (std::exception& err) {
//            GLIB_FAIL("Error opening image " << filename);
//        }
//    }
//    return iter->second.get();
//}
//
//
//
//void AssetManager::AddModel (const std::string& name, std::shared_ptr<IModel> mesh) {
//    m_models[name] = mesh;
//}
//
//void AssetManager::RemoveModel(const std::string& name){
//    m_models.erase(name);
//}
//
//bool AssetManager::HasModel(const std::string &name) const {
//    return m_models.count(name) > 0;
//}
//
//std::shared_ptr<IModel> AssetManager::GetModel(const std::string& name) const {
//    auto it = m_models.find(name);
//    if (it == m_models.end()){
//        // try to dynamically load the model
//
//        GLIB_FAIL("Unknown model " << name);
//    }
//    return it->second;
//}
//
//void AssetManager::Clear() {
//    m_models.clear();
//    m_textures.clear();
//}
