#include <monkey/components/charactercomponent.h>
#include <gfx/entity.h>
#include <gfx/components/animator.h>


void AnimateCharState::Init() {
    char dir = m_state->GetDirection();
    if (dir == 'w') dir='e';
    m_animator->SetAnimation(m_id + "_"+ dir);

}
void StateCharacter::Start () {
    auto animator = m_entity->GetComponent<Animator>();
    AddState( "idle", std::unique_ptr<State2>(new AnimateCharState(this, animator, "idle")));
    AddState( "walk", std::unique_ptr<State2>(new AnimateCharState(this, animator, "walk")));
    AddState( "talk", std::unique_ptr<State2>(new AnimateCharState(this, animator, "talk")));
    //StateMachine2::Start();
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