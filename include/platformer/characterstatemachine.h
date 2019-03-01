#pragma once

#include <gfx/components/statemachine2.h>
#include <glm/glm.hpp>
#include <gfx/math/shape.h>
#include <gfx/lua/luawrapper.h>

class Animator;
class Collider;

struct Control {
    bool left;
    bool right;
    bool up;
    bool down;
};

class CharacterStateMachine : public StateMachine2 {
public:
    CharacterStateMachine(
        float speed,
        float accelerationGround,
        float acceleationAir,
        float jumpVelocity,
        // animation
        const std::string& idle,
        const std::string& walk,
        const std::string& turn,
        const std::string& duck,
        const std::string& jumpUp,
        const std::string& jumpDown);

    void Start () override ;
    void SetState (const std::string&) override;
    void Refresh () override;

    // called to select animation based on current state and possibly other variables
    void SetRefreshFunc (luabridge::LuaRef ref);
    std::type_index GetType() override;
    void SetAnimation(const std::string&);
    void SetCollider(const std::string&);
    void AddShape (const std::string& key, std::shared_ptr<Shape> value);
private:
    std::unordered_map<std::string, std::shared_ptr<Shape>> m_colliders;
    Animator * m_animator;
    Collider * m_collider;
    // refresh function.
    std::shared_ptr<luabridge::LuaRef> m_refreshFunc;
    std::string m_animClass;
    std::string m_collClass;
};








inline std::type_index CharacterStateMachine::GetType() {
    return std::type_index(typeid(StateMachine2));
}
