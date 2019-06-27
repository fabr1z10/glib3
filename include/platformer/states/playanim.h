#pragma once

#include <gfx/components/statemachine.h>
#include <platformer/states/platformerstate.h>

class PlayAnim : public StateAction {
public:
    PlayAnim(PlatformerState* state, const std::string& anim);
    void Run (StateMachine*) override;
private:
    PlatformerState* m_state;
    std::string m_anim;
};

