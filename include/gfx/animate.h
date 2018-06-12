#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>



class Animate : public Activity {
public:
    Animate(int activityId, const std::string& actorId, const std::string& animId, bool flipX = false);
    Animate(int activityId, Entity* entity, const std::string& animId, bool flipX = false);
    void Start() override;
    void Run (float dt) override {}
private:
    bool m_flipX;
    Entity* m_entity;
    std::string m_animId;
    std::string m_actorId;
};