#include <monkey/components/statemachine.h>
#include <monkey/error.h>
#include <monkey/engine.h>
#include <monkey/input/pytab.h>
#include <monkey/scenefactory.h>


State::State(const ITab& t) : Ref(t) {
    m_id = t.get<std::string>("id");
    auto factory = Engine::get().GetSceneFactory();
    if (t.has("keys")) {
        t.foreach("keys", [&](const ITab &p) {
            // TODO CIAPPO
            auto key = p.get<int>("key");
            auto tbl = PyTab(p.get<pybind11::object>("action"));

            auto action = factory->make2<StateAction>(tbl);
            m_actions.insert(std::make_pair(key, action));

        });
    }

}

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





void StateMachine::Begin() {
    for (auto& s : m_states) {
        s.second->AttachStateMachine(this);
    }
    auto n = pybind11::none();
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

void StateMachine::SetState(const std::string& state) {
    pybind11::dict n;
    SetState(state, PyTab(n));
}

void StateMachine::SetState(const std::string & state, const ITab& d) {
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
    m_currentState->Init(d);
}

//void StateMachine::SetState(const std::string & state, luabridge::LuaRef ref) {
//    if (state == m_currentStateId) {
//        return;
//    }
//    m_currentStateId= state;
//    if (m_currentState != nullptr) {
//        m_currentState->End();
//    }
//    auto it = m_states.find(state);
//    if (it == m_states.end()) {
//        GLIB_FAIL("unknown state " << state);
//    }
//    m_currentState = it->second.get();
//    m_currentState->Init(ref);
//}


State* StateMachine::GetState (const std::string& state) {
    return m_states.at(state).get();
}


void State::onCollide() {

}