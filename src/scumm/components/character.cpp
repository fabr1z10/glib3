#include "character.h"
#include <monkey/entity.h>
#include <monkey/components/animator.h>

CharacterController::CharacterController(const ITab &t) : Component(t) {
    m_dir = t.get<std::string>("dir")[0];
    m_speed = t.get<float>("speed");
    m_textOffset = t.get<glm::vec2>("text_offset");
    m_textColor = t.get<glm::vec4>("text_color");
    m_textColor /= 255.0f;

}


void CharacterController::Start() {
    m_animator = m_entity->GetComponent<IAnimator>();
    if (m_animator == nullptr) {
        GLIB_FAIL("animator required");
    }
    turn(m_dir);
}

void CharacterController::turn(char dir) {
    m_dir = dir;
    std::string anim = "idle_" + std::string(1,dir == 'w' ? 'e' : dir);
    m_entity->SetFlipX(dir == 'w');
    m_animator->SetAnimation(anim);

}

StateCharacter::StateCharacter(float speed, char dir, const std::string& initialState) :
    StateMachine(initialState), m_speed(speed), m_dir(dir) {
}


StateCharacter::StateCharacter(const ITab &t) : StateMachine() {
    m_dir = t.get<std::string>("dir")[0];
    m_speed = t.get<float>("speed");
    m_initialState = t.get<std::string>("state");
}

void AnimateCharState::AttachStateMachine(StateMachine * sm) {
    m_state = dynamic_cast<const StateCharacter*>(sm);
    m_animator = sm->GetObject()->GetComponent<IAnimator>();
    if (m_animator == nullptr) {
        GLIB_FAIL("Animate char state needs an animator!");
    }
}

void AnimateCharState::Init(pybind11::dict&) {
    char dir = m_state->GetDirection();
    if (dir == 'w') dir='e';
    m_animator->SetAnimation(m_id + "_"+ dir);

}


void StateCharacter::Start () {
    AddState( "idle", std::make_shared<AnimateCharState>("idle"));
    AddState( "walk", std::make_shared<AnimateCharState>("walk"));
    AddState( "talk", std::make_shared<AnimateCharState>("talk"));
    for (auto& s : m_states) {
        s.second->AttachStateMachine(this);
    }
}



void StateCharacter::Begin() {
    SetDirection(m_dir);
}



void StateCharacter::SetDirection(char dir) {
    m_entity->SetFlipX(dir == 'w');
    m_dir = dir;
    ResetState();
}
