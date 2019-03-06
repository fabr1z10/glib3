#pragma once

#include <functional>
#include <gfx/components/statemachine2.h>
#include <glm/glm.hpp>
#include <gfx/math/shape.h>
#include <gfx/lua/luawrapper.h>

class Animator;
class Collider;
class InputMethod;

class ExtendedStateMachine : public StateMachine2 {
public:
    ExtendedStateMachine(const std::string& initialState);

    void Start () override ;
    void SetState (const std::string&) override;
    void Refresh () override;

    // called to select animation based on current state and possibly other variables
    void SetRefreshFunc (luabridge::LuaRef ref);


    std::type_index GetType() override;
    void SetAnimation(const std::string&);
    void SetCollider(const std::string&);
    void AddShape (const std::string& key, std::shared_ptr<Shape> value);
    void KeyListener (int) ;
    void SendMessage (luabridge::LuaRef message);
    void AddMessage (const std::string& key, std::function<void(luabridge::LuaRef)> value);
private:
    std::unordered_map<std::string, std::shared_ptr<Shape>> m_colliders;
    Animator * m_animator;
    Collider * m_collider;
    InputMethod * m_input;
    // refresh function.
    std::shared_ptr<luabridge::LuaRef> m_refreshFunc;
    std::string m_animClass;
    std::string m_collClass;
    std::string m_currentAnim;
    std::string m_currentCollider;
    std::unordered_map<std::string, std::function<void(luabridge::LuaRef)>> m_messageHandlers;
};

inline std::type_index ExtendedStateMachine::GetType() {
    return std::type_index(typeid(StateMachine2));
}






