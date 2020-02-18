#include <monkey/activities/changeroom.h>
#include <monkey/engine.h>


ChangeRoom::ChangeRoom(const LuaTable & t) : Activity() {
    m_roomId = t.Get<std::string>("room");
}

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