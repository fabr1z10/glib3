#include <gfx/state.h>

void State::Init(Entity* e) {
    if (m_initializer != nullptr)
        m_initializer->Init(e);
    if (m_behaviour != nullptr)
        m_behaviour->Init(e);
}

void State::Start() {
    if (m_initializer != nullptr)
        m_initializer->Start();
    if (m_behaviour != nullptr)
        m_behaviour->ResetState();

}
bool State::Run(double dt) {
    if (m_behaviour != nullptr)
        return m_behaviour->Run(dt);
    return false;
}
