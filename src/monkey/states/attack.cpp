#include <monkey/states/attack.h>
#include <monkey/components/stateactions.h>
#include <monkey/entity.h>
#include <GLFW/glfw3.h>


Attack::Attack(const ITable &t) : State(t) {

    m_anim = t.get<std::string>("anim");

    AddKey(GLFW_KEY_LEFT, std::make_shared<StateTransition>("walk"));
    AddKey(GLFW_KEY_RIGHT, std::make_shared<StateTransition>("walk"));

}


Attack::Attack(const Attack& orig) : State(orig) {
    m_anim = orig.m_anim;
}

std::shared_ptr<State> Attack::clone() const {
    return std::make_shared<Attack>(*this);
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