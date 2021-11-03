#include <monkey/components/extstatemachine.h>

#include <monkey/error.h>
#include <monkey/components/animator.h>
#include <monkey/components/collider.h>
#include <monkey/components/inputmethod.h>
#include <iostream>
#include <monkey/scenefactory.h>

ExtendedStateMachine::ExtendedStateMachine(const std::string& initialState) : StateMachine(initialState) {
}


ExtendedStateMachine::ExtendedStateMachine(const ITab & t) {
    m_initialState = t.get<std::string>("initialState");
    m_currentState = nullptr;
    auto factory = Engine::get().GetSceneFactory();


    t.foreach("states", [&] (const ITab& table) {
        auto state = factory->make2<State>(table);
        this->AddState(state->getId(), state);
    });

//        luabridge::LuaRef statesRef = table.Get<luabridge::LuaRef>("states");
//        for (int i = 0; i < statesRef.length(); ++i) {
//            luabridge::LuaRef stateRef = statesRef[i+1];
//            std::string key = stateRef["id"].cast<std::string>();
//            luabridge::LuaRef stateDef = stateRef["state"];
//            auto state = factory->make<State>(stateDef);
//            ptr->AddState(key, state);
//        }
//
//        table.ProcessVector("keys", [ptr] (luabridge::LuaRef ref) {
//            int key = ref["id"].cast<int>();
//            luabridge::LuaRef callback = ref["func"];
//            ptr->AddKey(key, callback);
//        });
//
//        return ptr;
//
//    }

}

// forward to the active state
void ExtendedStateMachine::KeyListener (int key) {
    bool handled = false;
    if (m_currentState != nullptr) {
        handled = m_currentState->KeyListener(key);
    }
    if (!handled) {
        // global key handling...
        //auto f = m_globalKeys.find(key);
        //if (f != m_globalKeys.end()) {
        //    f->second();
        // }
    }
    
}

void ExtendedStateMachine::Start () {
    m_input = m_entity->GetComponent<InputMethod>();
    if (m_input != nullptr) {
        m_input->onKeyDown.Register(this, [&](int key) { this->KeyListener(key); });
    }
}

