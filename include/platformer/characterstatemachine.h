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
    CharacterStateMachine(float speed, float accelerationGround, float acceleationAir, float jumpVelocity);

    void Start () override ;
    void SetState (const std::string&) override;
    void Refresh () override;

    // called to select animation based on current state and possibly other variables
    void SetRefreshFunc (luabridge::LuaRef ref);
    std::type_index GetType() override;


private:
    std::unordered_map<std::string, std::shared_ptr<Shape>> m_colliders;

    // refresh function.
    std::shared_ptr<luabridge::LuaRef> m_refreshFunc;

    float m_speed;
    float m_accGnd;
    float m_accAir;
    float m_jumpVel;

};








inline std::type_index CharacterStateMachine::GetType() {
    return std::type_index(typeid(StateMachine2));
}
