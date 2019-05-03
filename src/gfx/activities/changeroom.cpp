#include <gfx/activities/changeroom.h>
#include <gfx/engine.h>

void ChangeRoom::Start() {
    luabridge::LuaRef ref = LuaWrapper::GetGlobalPath({"engine","state"});
    std::string oldRoom = ref["room"].cast<std::string>();
    // call the exit script, if any
    luabridge::LuaRef room = LuaWrapper::GetGlobal("room");
    luabridge::LuaRef exitFunc = room["onexit"];
    if (exitFunc.isFunction()) {
        exitFunc(m_roomId);
    }

    ref["room"] = m_roomId;
    ref["previousRoom"] = oldRoom;
    Engine::get().EndScene();
    SetComplete();

}