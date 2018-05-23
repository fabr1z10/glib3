#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>



class Animate : public Activity {
public:
    Animate(int activityId, Entity* entity, const std::string& animId);
    void Start() override;
    void Run (float dt) override {}
private:
    Entity* m_entity;
    std::string m_animId;
};