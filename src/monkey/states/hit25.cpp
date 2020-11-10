#include <monkey/states/hit25.h>
#include <monkey/components/stateactions.h>
#include <monkey/entity.h>
#include <GLFW/glfw3.h>

Hit25::Hit25(const std::string &anim) : m_anim(anim)
{
    // if player presses L/R while hitting, resume walk
    AddKey(GLFW_KEY_LEFT, std::make_shared<StateTransition>("walk"));
    AddKey(GLFW_KEY_RIGHT, std::make_shared<StateTransition>("walk"));
}

Hit25::Hit25(const ITable &t) : State(t) {
    m_anim = t.get<std::string>("anim");
}


void Hit25::Run(double dt) {
    if (m_animator->IsComplete()) {
        m_sm->SetState("walk");
    }
}


void Hit25::Init(pybind11::dict& d) {
    std::string anim = m_anim;
    if (!d.empty()) {
        anim = d["anim"].cast<std::string>();
    }
    m_animator->SetAnimation(anim);

}


void Hit25::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    auto entity = sm->GetObject();
    m_animator = entity->GetComponent<IAnimator>();


}