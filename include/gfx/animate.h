#pragma once

#include <gfx/activity.h>
#include <gfx/entity.h>

class Renderer;

class Animate : public Activity {
public:
    Animate(int activityId, const std::string& actorId, const std::string& animId, bool flipX = false);
    Animate(int activityId, Entity* entity, const std::string& animId, bool flipX = false);
    void Start() override;
    void Reset() override {
        Activity::Reset();
        m_entity = nullptr;
    }
    void Run (float dt) override ;
    void SetLoop (int);
private:
    int m_loop;
    bool m_flipX;
    Entity* m_entity;
    Renderer* m_renderer;
    std::string m_animId;
    std::string m_actorId;
};

inline void Animate::SetLoop (int count) {
    m_loop = count;
}