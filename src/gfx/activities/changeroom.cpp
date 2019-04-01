#include <gfx/activities/changeroom.h>
#include <gfx/engine.h>

void ChangeRoom::Start() {
    luabridge::LuaRef ref = LuaWrapper::GetGlobal("variables");
    std::string oldRoom = ref["_room"].cast<std::string>();
    // call the exit script, if any
    luabridge::LuaRef room = LuaWrapper::GetGlobal("room");
    luabridge::LuaRef exitFunc = room["onexit"];
    if (exitFunc.isFunction()) {
        exitFunc(m_roomId);
    }

    ref["_room"] = m_roomId;
    ref["_previousroom"] = oldRoom;
    Engine::get().EndScene();
    SetComplete();

}