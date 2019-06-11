#pragma once

#include <gfx/components/statemachine2.h>

// this is the walk state used in platformers like SuperMario
class NilState : public State2 {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    NilState () : State2() {}
    NilState (const NilState& orig) : State2(orig) {}
    void Run(double) override {}
    void Init () override {}
    void End () override {}
    std::shared_ptr<State2> clone() const override {
        return std::make_shared<NilState>(*this);
    }
    void AttachStateMachine(StateMachine2*) override {}
};