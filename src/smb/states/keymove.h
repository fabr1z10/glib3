#pragma once

#include <monkey/components/statemachine.h>

class InputMethod;

// this is the walk state used in platformers like SuperMario
class KeyMove : public State {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    KeyMove (const ITab&);
    void Run(double) override;
    void Init (pybind11::dict&) override;
    void End () override;
    void AttachStateMachine(StateMachine*) override;

private:
    float m_speed;
    float m_rotationSpeed;
    InputMethod * m_input;
    Entity * m_entity;

};


