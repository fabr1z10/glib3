#include <spriteview/sv.h>


SpriteView::SpriteView() {
    // initialize lua
    LuaWrapper::Init();




}
void SpriteView::Start() {
    Engine &g = Engine::get();
    g.MainLoop();
}

void SpriteView::LoadFonts() {
    Engine::get().GetAssetManager().AddFont("main", "/usr/share/fonts/truetype/ubuntu/UbuntuMono-B.ttf");
    LuaWrapper::setLuaPath(m_dir+"/");
    luabridge::setGlobal(LuaWrapper::L, m_dir+"/", "_path");
    Engine::get().GetAssetManager().SetDirectory(m_dir+"/");
    LuaWrapper::Load(m_dir + "/loadspr.lua");


}