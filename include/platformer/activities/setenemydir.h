#pragma once

#include <gfx/activities/targetactivity.h>

class SetEnemyDirection : public TargetActivity {
public:
    SetEnemyDirection(bool left);
    void Start() override;
    void Run (float dt) override  {}
private:
    bool m_left;
};
