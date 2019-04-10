#include <gfx/components/switch.h>
#include <gfx/entity.h>
#include <gfx/error.h>


void Switch::Start() {
    int i = 0;
    for (auto& c : m_entity->GetChildren()) {
        m_states[m_stateNames[i++]] = c.second.get();
        c.second->SetActive(false);
    }
    m_currentlyActive.clear();

    ChangeState(m_initialState);
}



void Switch::ChangeState(const std::string& newState) {
    if (newState == m_currentlyActive)
        return;
    auto it = m_states.find(newState);
    if (it == m_states.end()) {
        GLIB_FAIL("Unknown state " << newState;)
    }
    auto entity = it->second;
    if (!m_currentlyActive.empty()) {
        auto old =m_states.at(m_currentlyActive);
        old->SetActive(false);
        entity->SetPosition(old->GetPosition());
    }
    entity->SetActive(true);
    m_currentlyActive = newState;
}