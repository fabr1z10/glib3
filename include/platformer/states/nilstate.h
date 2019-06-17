#pragma once

#include <gfx/components/statemachine.h>

// this is the walk state used in platformers like SuperMario
class NilState : public State {
public:
    /**
     *
     * @param speed The maximum speed
     * @param acceleration The acceleration
     * @param fliph Flip entity horizontally when going left
     */
    NilState () : State() {}
    NilState (const NilState& orig) : State(orig) {}
    void Run(double) override {}
    void Init () override {}
    void End () override {}
    std::shared_ptr<State> clone() const override {
        return std::make_shared<NilState>(*this);
    }
    void AttachStateMachine(StateMachine*) override {}
};