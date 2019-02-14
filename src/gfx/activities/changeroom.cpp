#include <gfx/activities/changeroom.h>
#include <gfx/engine.h>

void ChangeRoom::Start() {
    luabridge::LuaRef ref = LuaWrapper::GetGlobal("variables");
    std::string oldRoom = ref["_room"].cast<std::string>();
    ref["_room"] = m_roomId;
    ref["_previousRoom"] = oldRoom;
    Engine::get().EndScene();
    SetComplete();

}