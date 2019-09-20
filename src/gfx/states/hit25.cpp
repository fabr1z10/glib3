#include <gfx/states/hit25.h>
#include <gfx/components/stateactions.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>

Hit25::Hit25(const std::string &anim) : m_anim(anim)
{
    // if player presses L/R while hitting, resume walk
    AddKey(GLFW_KEY_LEFT, std::make_shared<StateTransition>("walk"));
    AddKey(GLFW_KEY_RIGHT, std::make_shared<StateTransition>("walk"));
}


Hit25::Hit25(const Hit25& orig) : State(orig) {
    m_anim = orig.m_anim;
}

std::shared_ptr<State> Hit25::clone() const {
    return std::make_shared<Hit25>(*this);
}

void Hit25::Run(double dt) {
    if (m_animator->IsComplete()) {
        m_sm->SetState("walk");
    }
}


void Hit25::Init() {
    m_animator->SetAnimation(m_anim);
}


void Hit25::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    auto entity = sm->GetObject();
    m_animator = entity->GetComponent<IAnimator>();


}