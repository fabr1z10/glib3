#pragma once

#include <functional>
#include <monkey/components/statemachine.h>
#include <glm/glm.hpp>
#include <monkey/math/shape.h>

class Animator;
class Collider;
class InputMethod;

// like state machine, plus you can forward input key events
// to the correct state
class ExtendedStateMachine : public StateMachine {
public:
    ExtendedStateMachine(const std::string& initialState);
    ExtendedStateMachine(const ExtendedStateMachine&);
    ExtendedStateMachine(const ITable&);
    std::shared_ptr<Component> clone() const override;
    
    void Start () override ;
    void KeyListener (int key);
    std::type_index GetType() override;
private:
    InputMethod * m_input;
};

inline std::type_index ExtendedStateMachine::GetType() {
    return std::type_index(typeid(StateMachine));
}






