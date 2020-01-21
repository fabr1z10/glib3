//#include <monkey/activities/changestate.h>
//#include <monkey/engine.h>
//#include <monkey/components/statemachine.h>
//
//ChangeState::ChangeState(const std::string& actorId, const std::string& state) : Activity(), m_actorId(actorId), m_state(state) {}
//
//void ChangeState::Start() {
//    m_entity = Engine::get().GetRef<Entity>(m_actorId);
//    m_entity->GetComponent<StateMachine>()->ChangeState(m_state);
//    SetComplete();
//}
//
