#pragma once

#include <gfx/components/statemachine2.h>
#include <glm/glm.hpp>
#include <gfx/math/shape.h>
#include <gfx/lua/luawrapper.h>


struct Control {
    bool left;
    bool right;
    bool up;
    bool down;
};

class CharacterStateMachine : public StateMachine2 {
public:
    CharacterStateMachine(float speed, float accelerationGround, float acceleationAir, float jumpheight, float timeApex);

    void Start () override ;
    void SetState (const std::string&) override;

    // called to select animation based on current state and possibly other variables
    void AnimationSelect ();
    void SetAdditionalState (luabridge::LuaRef ref);
    void SetAnimFunc (luabridge::LuaRef ref);

    // plug in here player controller or AI
    void UpdateAddInfo (const std::string& field, luabridge::LuaRef value);
    glm::vec2 m_velocity;
    float m_gravity;
    float m_accTimeGnd;
    float m_accTimeAir;
    float m_jumpVelocity;
    float m_speed;

    // any additional state you want to add (might be null if u dont need it)
    std::shared_ptr<luabridge::LuaRef> m_additionalState;
    std::shared_ptr<luabridge::LuaRef> m_animSelector;

    std::unordered_map<std::string, std::shared_ptr<Shape>> m_colliders;
    // whenever state, or additional info changes, we lookup the animation and collider
    // and if needed, update it!
    std::string m_currentAnimation;
    std::string m_currentCollider;
    std::unordered_map<std::string, std::string> m_animationLookup;
    std::unordered_map<std::string, std::string> m_colliderLookup;



};





