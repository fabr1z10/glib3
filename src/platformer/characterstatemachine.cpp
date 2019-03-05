#include <platformer/characterstatemachine.h>
#include <platformer/walk.h>
#include <platformer/jump.h>
#include <platformer/duck.h>
#include <iostream>

#include <gfx/error.h>
#include <gfx/entitywrapper.h>
#include <gfx/components/animator.h>
#include <gfx/components/collider.h>
#include <gfx/components/inputmethod.h>

CharacterStateMachine::CharacterStateMachine(
    float speed,
    float accelerationGround,
    float accelerationAir,
    float jumpVelocity,
    bool canDuck,
    bool flip,
    const std::string& idle,
    const std::string& walk,
    const std::string& turn,
    const std::string& duck,
    const std::string& jumpUp,
    const std::string& jumpDown) : ExtendedStateMachine("walk")
{
    auto w = std::make_shared<Walk> (speed, accelerationGround, jumpVelocity, idle, walk, turn, flip);
    AddState ("walk", w);
    AddState ("jump", std::make_shared<Jump> (speed, accelerationAir, jumpUp, jumpDown, flip));
    AddState ("duck", std::make_shared<Duck> (accelerationGround, duck));

    // add messages
    AddMessage("enable_duck", [w] (luabridge::LuaRef ref) {
        bool value = ref.cast<bool>();
        w->SetCanDuck(value);
    } );

}
//
//void CharacterStateMachine::AddShape (const std::string& key, std::shared_ptr<Shape> value) {
//    m_colliders.insert(std::make_pair(key, value));
//}
//
//// forward to the active state
//void CharacterStateMachine::KeyListener (int key) {
//    if (m_currentState != nullptr) {
//        m_currentState->KeyListener(key);
//    }
//
//}
//
//void CharacterStateMachine::Start () {
//    m_animator = m_entity->GetComponent<Animator>();
//    m_collider = m_entity->GetComponent<Collider>();
//    m_input = m_entity->GetComponent<InputMethod>();
//    m_input->onKeyDown.Register(this, [&] (int key) { this->KeyListener(key); });
//
//    for (auto& s : m_states) {
//        s.second->AttachStateMachine(this);
//    }
//    Refresh();
//}
//
//void CharacterStateMachine::SetAnimation(const std::string& anim) {
//    m_animator->SetAnimation(m_animClass + anim);
//}
//
//
//void CharacterStateMachine::SetCollider(const std::string& collider) {
//    auto it = m_colliders.find(m_collClass + collider);
//    if (it == m_colliders.end()) {
//        GLIB_FAIL("Don't know shape: " << collider);
//    }
//    m_collider->SetShape(it->second);
//}
//
//
//void CharacterStateMachine::SetState (const std::string& state) {
//    if (state == m_currentStateId) {
//        return;
//    }
//    Refresh();
//    StateMachine2::SetState(state);
//
//
//}
//
//void CharacterStateMachine::Refresh() {
//    luabridge::LuaRef classes = (*m_refreshFunc.get())(EntityWrapper(this->GetObject()));
//    m_animClass = classes[1].cast<std::string>();
//    m_collClass = classes[2].cast<std::string>();
//}
//
//void CharacterStateMachine::SetRefreshFunc (luabridge::LuaRef ref) {
//    m_refreshFunc = std::make_shared<luabridge::LuaRef>(ref);
//}
//
