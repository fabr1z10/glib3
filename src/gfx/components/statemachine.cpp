#include <gfx/components/statemachine.h>
#include <gfx/error.h>

void State::AddKey(int key, std::shared_ptr<StateAction> action) {
    m_actions.insert(std::make_pair(key, action));

}

void State::AttachStateMachine(StateMachine * sm) {
    m_sm = sm;
}

bool State::KeyListener(int key) {
    auto f = m_actions.find(key);
    if (f == m_actions.end())
        return false;
    f->second->Run(m_sm);
    return true;
}

StateMachine::StateMachine(const StateMachine& orig) : Component(orig), m_initialState(orig.m_initialState)
{
    m_currentState = nullptr;
    for (auto& i : orig.m_states) {
        AddState(i.first, i.second->clone());
    }
}

std::shared_ptr<Component> StateMachine::clone() const {
    return std::make_shared<StateMachine>(StateMachine(*this));
}


void StateMachine::Begin() {
    for (auto& s : m_states) {
        s.second->AttachStateMachine(this);
    }
    SetState(m_initialState);
}

void StateMachine::Update(double dt) {
    if (!m_active)
        return;
    if (m_currentState != nullptr) {
        m_currentState->Run(dt);
    }
}


void StateMachine::ResetState() {
    m_currentState = nullptr;

    std::string state(m_currentStateId);
    if (state.empty())
        state = m_initialState;
    m_currentStateId.clear();
    SetState(state);
}

void StateMachine::SetState(const std::string & state) {
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

State* StateMachine::GetState (const std::string& state) {
    return m_states.at(state).get();
}
