#include <monkey/states/simple.h>
#include <monkey/components/ianimator.h>
#include <monkey/entity.h>

SimpleState::SimpleState(const std::string &anim) : State(), m_anim(anim) {}

SimpleState::SimpleState(const SimpleState&) {

}

std::shared_ptr<State> SimpleState::clone() const {
    return std::make_shared<SimpleState>(*this);
}

void SimpleState::AttachStateMachine(StateMachine * sm) {
    //m_sm = sm;
    m_entity = sm->GetObject();

    m_animator = m_entity->GetComponent<IAnimator>();
}

void SimpleState::Init() {
    m_animator->SetAnimation(m_anim);
}

void SimpleState::End() {

}

void SimpleState::Run (double dt) {}



//#inc