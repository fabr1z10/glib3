#include <monkey/states/simple.h>
#include <monkey/components/ianimator.h>
#include <monkey/entity.h>

NullState::NullState() : State() {}

NullState::NullState(const ITab & t) : State(t) {

}


void NullState::Init(const ITab&) {}

void NullState::End() {}

void NullState::Run (double dt) {

}


SimpleState::SimpleState(const std::string &anim) : State(), m_anim(anim) {}

SimpleState::SimpleState(const ITab& t) : State(t) {
    m_anim = t.get<std::string>("anim");
    m_endOnAnimComplete = t.get<bool>("end_on_anim_complete", false);
    m_nextState = t.get<std::string>("next", "");
}


void SimpleState::AttachStateMachine(StateMachine * sm) {
    m_sm = sm;
    m_entity = sm->GetObject();
    m_animator = m_entity->GetComponent<IAnimator>();

}

void SimpleState::Init(const ITab& d) {
//    PyDict dict(d);
//    if (dict.hasKey("anim")) {
//        m_anim = dict.get<std::string>("anim");
//    }
    m_animator->SetAnimation(m_anim);
}

void SimpleState::End() {

}

void SimpleState::Run (double dt) {
//    if (m_endOnAnimComplete && !m_nextState.empty() && m_animator->IsComplete()) {
//        m_sm->SetState(m_nextState);
//    }
}


