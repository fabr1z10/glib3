#include <monkey/changeroom.h>
#include <gfx/engine.h>
#include <monkey/monkey.h>

void ChangeRoom::Start() {
    Monkey& m = Monkey::get();
    m["variables"].Set("_room", m_roomId);
    Engine::get().EndScene();
    SetComplete();

}