#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>

class ChangeState : public Activity {
public:
    ChangeState(const std::string& actorId, const std::string& state);
    void Start() override;
    void Run (float dt) override {}
    void Reset() override {}
private:
    Entity* m_entity;
    std::string m_actorId;
    std::string m_state;
};
