#pragma once

#include <gfx/components/extstatemachine.h>
#include <glm/glm.hpp>
#include <gfx/math/shape.h>
#include <gfx/lua/luawrapper.h>

class CharacterStateMachine : public ExtendedStateMachine {
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

    std::type_index GetType() override;
private:
    std::unordered_map<std::string, std::shared_ptr<Shape>> m_colliders;
    Animator * m_animator;
    Collider * m_collider;
    InputMethod * m_input;
    // refresh function.
    std::shared_ptr<luabridge::LuaRef> m_refreshFunc;
    std::string m_animClass;
    std::string m_collClass;
};

inline std::type_index CharacterStateMachine::GetType() {
    return std::type_index(typeid(StateMachine2));
}
