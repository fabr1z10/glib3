#include <gfx/components/statemachine.h>
#include <gfx/error.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gfx/entitywrapper.h>

void StateMachine::Start() {
    for (auto& s : m_states)
        s.second->Init(m_entity);
    ChangeState(m_initialState);
}

void StateMachine::AddState(const std::string & name, std::shared_ptr<State> state) {
    m_states[name] = state;
}




void StateMachine::ChangeState(const std::string& state) {
    //if (m_currentState != nullptr)
    //    m_currentState->End();

    auto it = m_states.find(state);
    if (it == m_states.end()) {
        GLIB_FAIL("Don't know state " << state);
    }
    m_currentState = it->second.get();
    m_currentState->Start();

}

void StateMachine::Update(double dt) {
    if (!m_active)
        return;
    if (m_currentState != nullptr) {
        if (m_currentState->Run(dt)) {
            ChangeState(m_currentState->GetNextState());
        }
    }
}

void RandomTransitionStateMachine::Update(double dt) {
    if (m_currentState != nullptr) {
        if (m_currentState->Run(dt)) {
            ChangeState(m_currentState->GetNextState());
        } else {
            // check transition
            auto p = m_transition.Next(m_currentState->GetId());
            if (p.first) {
                ChangeState(p.second);
            }

        }
    }

}

// key triggered state change
void KeyboardControlledStateMachine::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (m_currentState != nullptr) {
        std::cout << key << ", " << action << ", " << m_currentState->GetId() <<"\n";
        KeyPress kp;
        kp.action = action;
        kp.key =key;
        kp.state = m_currentState->GetId();
        auto it = m_transitions.find(kp);
        if (it != m_transitions.end()) {
            it->second->Run(this);
        }
    }
}


void KeyboardControlledStateMachine::AddKey(const std::string& currentState, int key, bool press, std::unique_ptr<StateEvent> ev)
{
    KeyPress k;
    k.action = press ? GLFW_PRESS : GLFW_RELEASE;
    k.key = key;
    k.state = currentState;
    m_transitions[k] = std::move(ev);
}

void SEChangeState::Run(StateMachine * s) {
    s->ChangeState(m_nextState);
}

void SECallback::Run(StateMachine * s) {
    m_ref(EntityWrapper(s->GetObject()));
}
