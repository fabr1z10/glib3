#include <gfx/statemachine.h>
#include <gfx/error.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


void State::Init(Entity* entity) {
    m_entity = entity;
}

void StateMachine::Start() {
    for (auto& s : m_states)
        s.second->Init(m_entity);
    ChangeState(m_initialState);
}

void StateMachine::AddState(const std::string & name, std::shared_ptr<State> state) {
    m_states[name] = state;
}


void StateMachine::ChangeState(const std::string& state) {
    if (m_currentState != nullptr)
        m_currentState->End();

    auto it = m_states.find(state);
    if (it == m_states.end()) {
        GLIB_FAIL("Don't know state " << state);
    }
    m_currentState = it->second.get();
    m_currentState->Start();

}

void StateMachine::Update(double dt) {

    if (m_currentState != nullptr) {
        if (m_currentState->Run(dt)) {
            ChangeState(m_currentState->GetNextState());
        }
    }




}

// key triggered state change
void KeyboardControlledStateMachine::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
    {

        if (m_currentState != nullptr) {
            auto it = m_transitions.find(m_currentState->GetId());
            if (it != m_transitions.end())
            {
                auto it2 = it->second.find(key);
                if (it2 != it->second.end()) {
                    ChangeState(it2->second);
                }
            }
        }
    }
}


