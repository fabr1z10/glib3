#include <monkey/states/animstate.h>
#include <monkey/entity.h>


AnimState::AnimState(const ITab& t) : State(t){
    m_anim = t.get<std::string>("anim");
    auto nextState = t.get<std::string>("next_state", "");
    if (!nextState.empty()) {
        m_changeStateAfterAnim = true;
        m_nextState = nextState;
    }
}

void AnimState::Init(const ITab &d) {
    m_renderer->setAnimation(m_anim);
}

void AnimState::Run(double) {



}

void AnimState::End() {}

void AnimState::AttachStateMachine(StateMachine * sm) {

    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();

    m_renderer = dynamic_cast<AnimationRenderer*>(m_entity->GetComponent<Renderer>());
}