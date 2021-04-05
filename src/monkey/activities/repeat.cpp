#include <monkey/activities/repeat.h>

Repeat::Repeat(const ITab & t) : Activity() {
    m_func = t.get<pybind11::function>("func");
    m_interval = t.get<float>("every");
}

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
