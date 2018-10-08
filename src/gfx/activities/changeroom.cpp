#include <gfx/activities/changeroom.h>
#include <gfx/engine.h>
#include <gfx/monkey.h>

void ChangeRoom::Start() {
    Monkey& m = Monkey::get();
    std::string oldRoom = m["variables"].Get<std::string>("_room");
    m["variables"].Set("_previousroom", oldRoom);
    m["variables"].Set("_room", m_roomId);
    Engine::get().EndScene();
    SetComplete();

}