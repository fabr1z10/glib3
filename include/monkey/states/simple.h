#pragma once

#include <monkey/components/statemachine.h>
#include <glm/glm.hpp>

class IAnimator;

class NullState : public State {
public:
    NullState ();
    NullState (const ITable&);
    NullState (const NullState&);
    std::shared_ptr<State> clone() const override;
    void Run(double) override;
    void Init (pybind11::dict&) override;
    void End () override;
};

class SimpleState : public State {
public:
    SimpleState(const std::string& anim);
    SimpleState(const SimpleState&);
    SimpleState(const ITable&);
    std::shared_ptr<State> clone() const override;
    void Run(double) override;
    void Init (pybind11::dict&) override;
    void End () override;
    void AttachStateMachine(StateMachine*) override;
protected:
    std::string m_anim;
    IAnimator* m_animator;
    Entity * m_entity;
};