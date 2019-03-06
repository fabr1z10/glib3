#include <gfx/components/statemachine2.h>
#include <gfx/error.h>

StateMachine2::StateMachine2(const StateMachine2& orig) : Component(orig), m_initialState(orig.m_initialState)
{
    for (auto& i : orig.m_states) {
        AddState(i.first, i.second->clone());
    }
}

std::shared_ptr<Component> StateMachine2::clone() const {
    return std::make_shared<StateMachine2>(StateMachine2(*this));
}


void StateMachine2::Begin() {
    SetState(m_initialState);
}

void StateMachine2::Update(double dt) {
    if (!m_active)
        return;
    if (m_currentState != nullptr) {
        m_currentState->Run(dt);
    }
}


void StateMachine2::ResetState() {
    m_currentState = nullptr;

    std::string state(m_currentStateId);
    if (state.empty())
        state = m_initialState;
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

