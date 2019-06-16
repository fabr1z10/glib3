#pragma once

#include <functional>
#include <gfx/components/statemachine2.h>
#include <glm/glm.hpp>
#include <gfx/math/shape.h>
#include <gfx/lua/luawrapper.h>

class Animator;
class Collider;
class InputMethod;

// like state machine, plus you can forward input key events
// to the correct state
class ExtendedStateMachine : public StateMachine2 {
public:
    ExtendedStateMachine(const std::string& initialState);

    void Start () override ;
    void KeyListener (int key);
    void AddKey (int, luabridge::LuaRef callback);
    std::type_index GetType() override;
private:
    std::unordered_map<int, luabridge::LuaRef> m_globalKeys;
    InputMethod * m_input;
};

inline std::type_index ExtendedStateMachine::GetType() {
    return std::type_index(typeid(StateMachine2));
}






