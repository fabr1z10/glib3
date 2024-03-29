#include <monkey/activities/changeroom.h>
#include <monkey/engine.h>



ChangeRoom::ChangeRoom(const ITab & t) : Activity() {
    m_roomId = t.get<std::string>("room");
    m_args = t.get<pybind11::object>("args", pybind11::none());
}


void ChangeRoom::Start() {
    auto& t = Engine::get().getMainTable();

    auto oldRoom = t.get<std::string>("room");
    auto obj = t.as<pybind11::object>();
    obj.attr("room") =  m_roomId;
    obj.attr("room_args") = m_args;
    obj.attr("previous_room") = oldRoom;
//    luabridge::LuaRef ref = LuaWrapper::GetGlobalPath({"engine","state"});
//    std::string oldRoom = ref["room"].cast<std::string>();
//    // call the exit script, if any
//    luabridge::LuaRef room = LuaWrapper::GetGlobal("room");
//    luabridge::LuaRef exitFunc = room["onexit"];
//    if (exitFunc.isFunction()) {
//        exitFunc(m_roomId);
//    }
//
//    ref["room"] = m_roomId;
//    ref["previousRoom"] = oldRoom;
    Engine::get().EndScene();
    SetComplete();

}