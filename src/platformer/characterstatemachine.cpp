#include <platformer/characterstatemachine.h>
#include <platformer/walk.h>
#include <platformer/jump.h>
#include <iostream>

CharacterStateMachine::CharacterStateMachine(
    float speed,
    float accelerationGround,
    float accelerationAir,
    float jumpHeight,
    float timeToJumpApex) : StateMachine2("walk"), m_accTimeGnd(accelerationGround), m_accTimeAir(accelerationAir), m_speed(speed)
{
    m_gravity = -(2.0f * jumpHeight) / (timeToJumpApex * timeToJumpApex);
    m_jumpVelocity = fabsf(m_gravity) * timeToJumpApex;
}

void CharacterStateMachine::Start () {
    AddState("walk", std::make_shared<Walk>(m_speed));
    AddState("jump", std::make_shared<Jump>(m_speed));
    SetState(m_initialState);
}

void CharacterStateMachine::SetState (const std::string& state) {
    if (state == m_currentStateId) {
        return;
    }
    StateMachine2::SetState(state);
    this->AnimationSelect();

}

void CharacterStateMachine::AnimationSelect () {
    if (m_animSelector == nullptr) {
        return;
    }
    if (m_additionalState == nullptr) {
        luabridge::LuaRef ref = m_animSelector->operator()(m_currentStateId);
    } else {
        luabridge::LuaRef ref = m_animSelector->operator()(m_currentStateId, *(m_additionalState.get()));
    }

}

void CharacterStateMachine::SetAdditionalState (luabridge::LuaRef ref) {
    m_additionalState = std::make_shared<luabridge::LuaRef>(ref);
}
void CharacterStateMachine::SetAnimFunc (luabridge::LuaRef ref) {
    m_animSelector = std::make_shared<luabridge::LuaRef>(ref);
}


void CharacterStateMachine::UpdateAddInfo (const std::string& field, luabridge::LuaRef value) {
std::cout << "updating field " << field << "\n";
}