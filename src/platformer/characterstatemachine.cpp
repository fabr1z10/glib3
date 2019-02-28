#include <platformer/characterstatemachine.h>
#include <platformer/walk.h>
#include <platformer/jump.h>
#include <iostream>
#include <gfx/entitywrapper.h>

CharacterStateMachine::CharacterStateMachine(
    float speed,
    float accelerationGround,
    float accelerationAir,
    float jumpVelocity) : StateMachine2("walk"), m_accGnd(accelerationGround), m_accAir(accelerationAir), m_speed(speed), m_jumpVel(jumpVelocity)
{
  //  m_gravity = -(2.0f * jumpHeight) / (timeToJumpApex * timeToJumpApex);
//    m_jumpVelocity = fabsf(m_gravity) * timeToJumpApex;
}

void CharacterStateMachine::Start () {
    AddState("walk", std::make_shared<Walk>(m_speed, m_accGnd, m_jumpVel));
    AddState("jump", std::make_shared<Jump>(m_speed, m_accAir));
    SetState(m_initialState);
}

void CharacterStateMachine::SetState (const std::string& state) {
    if (state == m_currentStateId) {
        return;
    }
    StateMachine2::SetState(state);
    Refresh();

}

void CharacterStateMachine::Refresh() {
    (*m_refreshFunc.get())(EntityWrapper(this->GetObject()));
}

void CharacterStateMachine::SetRefreshFunc (luabridge::LuaRef ref) {
    m_refreshFunc = std::make_shared<luabridge::LuaRef>(ref);
}

