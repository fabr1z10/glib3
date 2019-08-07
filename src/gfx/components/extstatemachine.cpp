#include <gfx/components/extstatemachine.h>

#include <gfx/error.h>
#include <gfx/entitywrapper.h>
#include <gfx/components/animator.h>
#include <gfx/components/collider.h>
#include <gfx/components/inputmethod.h>
#include <iostream>
#include <gfx/lua/luatable.h>

ExtendedStateMachine::ExtendedStateMachine(const std::string& initialState) : StateMachine(initialState) {
}

// forward to the active state
void ExtendedStateMachine::KeyListener (int key) {
    bool handled = false;
    if (m_currentState != nullptr) {
        handled = m_currentState->KeyListener(key);
    }
    if (!handled) {
        // global key handling...
        auto f = m_globalKeys.find(key);
        if (f != m_globalKeys.end()) {
            f->second();
        }
    }
    
}

void ExtendedStateMachine::Start () {
    m_input = m_entity->GetComponent<InputMethod>();
    if (m_input != nullptr) {
        m_input->onKeyDown.Register(this, [&](int key) { this->KeyListener(key); });
    }
}

void ExtendedStateMachine::AddKey(int key, luabridge::LuaRef callback) {
    m_globalKeys.insert(std::make_pair(key, callback));
}
