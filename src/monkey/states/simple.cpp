#include <monkey/states/simple.h>
#include <monkey/components/ianimator.h>
#include <monkey/entity.h>

NullState::NullState() : State() {}

NullState::NullState(const ITable & t) : State(t) {

}

NullState::NullState(const NullState& t) : State(t) {

}

std::shared_ptr<State> NullState::clone() const {
    return std::make_shared<NullState>(*this);
}

void NullState::Init() {}

void NullState::End() {}

void NullState::Run (double dt) {

}


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


