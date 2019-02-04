#include <gfx/components/statemachine2.h>
#include <gfx/error.h>

void StateMachine2::Begin() {
    SetState(m_initialState);
}

void StateMachine2::Update(double dt) {

    if (m_currentState != nullptr) {
        m_currentState->Run(dt);
    }
}


void StateMachine2::ResetState() {
    if (m_currentState == nullptr)
        return;
    m_currentState = nullptr;
    std::string state(m_currentStateId);
    m_currentStateId.clear();
    SetState(state);
}

void StateMachine2::SetState(const std::string & state) {
    if (state == m_currentStateId) {
        return;
    }
    m_currentStateId= state;
    if (m_currentState != nullptr) {
        m_currentState->End();
    }
    auto it = m_states.find(state);
    if (it == m_states.end()) {
        GLIB_FAIL("unknown state " << state);
    }
    m_currentState = it->second.get();
    m_currentState->Init();
}

