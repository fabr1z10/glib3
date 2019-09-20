#include <gfx/activities/repeat.h>

Repeat::Repeat(luabridge::LuaRef func, float interval) : Activity(),
    m_func{func}, m_interval(interval), m_timer(0.0f)
{}

void Repeat::Start() {
    m_func();
    m_timer = 0.0f;
}

void Repeat::Run(float dt) {
    m_timer += dt;
    if (m_timer >= m_interval) {
        m_timer = 0.0f;
        m_func();
    }
    // never ends ... only way is to kill the script it belongs to
}
