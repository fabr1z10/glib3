#pragma once

#include <monkey/components/statemachine.h>
#include <glm/glm.hpp>

class InputMethod;
class Entity;
class IAnimator;


class Walk3D : public State {
public:
    Walk3D(float acceleration);
    Walk3D(const Walk3D&);
    Walk3D (const ITable&);
    std::shared_ptr<State> clone() const override;
    void Run(double) override;
    void Init (pybind11::dict&) override;
    void End () override;
    float GetSpeed() const;
    void AttachStateMachine(StateMachine*) override;
protected:
    InputMethod * m_input;
    IAnimator* m_animator;
    Entity * m_entity;
    float m_acceleration;
};

