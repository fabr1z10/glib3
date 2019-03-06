#include <gfx/components/extstatemachine.h>

#include <gfx/error.h>
#include <gfx/entitywrapper.h>
#include <gfx/components/animator.h>
#include <gfx/components/collider.h>
#include <gfx/components/inputmethod.h>
#include <iostream>
#include <gfx/lua/luatable.h>

ExtendedStateMachine::ExtendedStateMachine(const std::string& initialState) : StateMachine2(initialState) {
}

void ExtendedStateMachine::AddShape (const std::string& key, std::shared_ptr<Shape> value) {
    m_colliders.insert(std::make_pair(key, value));
}

// forward to the active state
void ExtendedStateMachine::KeyListener (int key) {
    if (m_currentState != nullptr) {
        m_currentState->KeyListener(key);
    }
    // global key handling...
}

void ExtendedStateMachine::Start () {
    m_animator = m_entity->GetComponent<Animator>();
    m_collider = m_entity->GetComponent<Collider>();
    m_input = m_entity->GetComponent<InputMethod>();
    m_input->onKeyDown.Register(this, [&] (int key) { this->KeyListener(key); });

    for (auto& s : m_states) {
        s.second->AttachStateMachine(this);
    }
    Refresh();
}

void ExtendedStateMachine::SetAnimation(const std::string& anim) {
    m_animator->SetAnimation(m_animClass + anim);
    m_currentAnim = anim;
}


void ExtendedStateMachine::SetCollider(const std::string& collider) {
    auto it = m_colliders.find(m_collClass + collider);
    if (it == m_colliders.end()) {
        GLIB_FAIL("Don't know shape: " << collider);
    }
    m_currentCollider = collider;
    m_collider->SetShape(it->second);

}


void ExtendedStateMachine::SetState (const std::string& state) {
    if (state == m_currentStateId) {
        return;
    }
    Refresh();
    StateMachine2::SetState(state);


}

void ExtendedStateMachine::Refresh() {
    if (m_refreshFunc != nullptr) {
        luabridge::LuaRef classes = (*m_refreshFunc.get())(EntityWrapper(this->GetObject()));
        m_animClass = classes[1].cast<std::string>();
        m_collClass = classes[2].cast<std::string>();
        if (!m_currentAnim.empty()) SetAnimation(m_currentAnim);
        if (!m_currentCollider.empty()) SetCollider(m_currentCollider);
    }
}

void ExtendedStateMachine::SetRefreshFunc (luabridge::LuaRef ref) {
    m_refreshFunc = std::make_shared<luabridge::LuaRef>(ref);
}

//void ExtendedStateMachine::SetActive(bool value) {
//    Component::SetActive(value);
//}


void ExtendedStateMachine::SendMessage(luabridge::LuaRef message) {
    LuaTable table(message);
    std::string key = table.Get<std::string>("key");
    bool refresh = table.Get<bool>("trigger_refresh", false);
    auto it = m_messageHandlers.find(key);
    if (it == m_messageHandlers.end()) {
        std::cout << "Mmh, do not know message " << key << "\n";
    } else {
        it->second(message);
    }
    if (refresh) {
        Refresh();
    }


}

void ExtendedStateMachine::AddMessage(const std::string &key, std::function<void(luabridge::LuaRef)> value) {
    m_messageHandlers.insert(std::make_pair(key, value));
}