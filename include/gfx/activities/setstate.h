#pragma once

#include <gfx/activity.h>
#include <string>

class SetState : public Activity {
public:
    SetState (const std::string& actorId, const std::string& state) : Activity(), m_actorId(actorId), m_state(state) {}
    void Start() override;
    void Run (float dt) override {}
private:
    std::string m_actorId;
    std::string m_state;

};
