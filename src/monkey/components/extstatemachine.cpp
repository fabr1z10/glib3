#include <monkey/components/extstatemachine.h>

#include <monkey/error.h>
#include <monkey/entitywrapper.h>
#include <monkey/components/animator.h>
#include <monkey/components/collider.h>
#include <monkey/components/inputmethod.h>
#include <iostream>
#include <monkey/lua/luatable.h>

ExtendedStateMachine::ExtendedStateMachine(const std::string& initialState) : StateMachine(initialState) {
}

ExtendedStateMachine::ExtendedStateMachine(const ExtendedStateMachine& orig) : StateMachine(orig)
{
    m_globalKeys = orig.m_globalKeys;
}

std::shared_ptr<Component> ExtendedStateMachine::clone() const {
    return std::make_shared<ExtendedStateMachine>(*this);
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
