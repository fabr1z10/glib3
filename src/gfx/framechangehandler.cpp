#include <gfx/framechangehandler.h>
#include <gfx/engine.h>
#include <gfx/lua/luatable.h>

void IFrameChangeHandler::SetMesh (std::shared_ptr<IMesh> mesh) {
    // get the additional info for this mesh
    luabridge::LuaRef ref = Engine::get().GetAssetManager().GetMeshInfo(mesh->GetId());
    for (int i = 0; i < ref.length(); ++i) {
        luabridge::LuaRef r = ref[i+1];
        LuaTable t(r);
        std::string anim = t.Get<std::string>("anim");

        int frame = t.Get<int>("frame", -1);
        luabridge::LuaRef data = t.Get<luabridge::LuaRef>("data");
        Init(data, anim, frame);
    }
}
