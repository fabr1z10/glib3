#include <monkey/components/charactercomponent.h>
#include <gfx/entity.h>
#include <gfx/components/animator.h>

StateCharacter::StateCharacter(const StateCharacter& orig) : StateMachine2(orig), m_dir(orig.m_dir) {
    
}

std::shared_ptr<Component> StateCharacter::clone() const {
    return std::make_shared<StateCharacter>(StateCharacter(*this));
}

void AnimateCharState::AttachStateMachine(StateMachine2 * sm) {
    m_state = dynamic_cast<const StateCharacter*>(sm);
    m_animator = sm->GetObject()->GetComponent<Animator>();
}

void AnimateCharState::Init() {
    char dir = m_state->GetDirection();
    if (dir == 'w') dir='e';
    m_animator->SetAnimation(m_id + "_"+ dir);

}

std::shared_ptr<State2> AnimateCharState::clone() const {
    return std::make_shared<AnimateCharState>(AnimateCharState(*this));
}

void StateCharacter::Start () {
    AddState( "idle", std::make_shared<AnimateCharState>("idle"));
    AddState( "walk", std::make_shared<AnimateCharState>("walk"));
    AddState( "talk", std::make_shared<AnimateCharState>("talk"));
}



void StateCharacter::Begin() {
    SetDirection(m_dir);
}

StateCharacter::StateCharacter(char dir, const std::string& initialState) : StateMachine2(initialState), m_dir(dir) {

}

void StateCharacter::SetDirection(char dir) {
    m_entity->SetFlipX(dir == 'w');
    m_dir = dir;
    ResetState();
}