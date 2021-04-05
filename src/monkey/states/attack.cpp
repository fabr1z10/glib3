#include <monkey/states/attack.h>
#include <monkey/components/stateactions.h>
#include <monkey/entity.h>
#include <GLFW/glfw3.h>


Attack::Attack(const ITab &t) : State(t) {

    m_anim = t.get<std::string>("anim");

    AddKey(GLFW_KEY_LEFT, std::make_shared<StateTransition>("walk"));
    AddKey(GLFW_KEY_RIGHT, std::make_shared<StateTransition>("walk"));

}



void Attack::Run(double dt) {
    if (m_animator->IsComplete()) {
        m_sm->SetState("walk");
    }
}


void Attack::Init(pybind11::dict& d) {
    std::string anim = m_anim;
    if (!d.empty()) {
        anim = d["anim"].cast<std::string>();
    }
    m_animator->SetAnimation(anim);

}


void Attack::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    auto entity = sm->GetObject();
    m_animator = entity->GetComponent<IAnimator>();


}