#pragma once

#include <platformer/states/platformerstate.h>
#include <glm/glm.hpp>

class EnemyWalk2D : public PlatformerState {
public:
    // dir = 1 for right, -1 for left
    EnemyWalk2D(float speed, int dir, bool enableFlip, bool flipPlatformEnd);
    void ResetState() override;
    void ResetState(luabridge::LuaRef) override;
    bool Run (double) override;
private:
    float m_speed;
    int m_dir;
    bool m_enableFlip;
    bool m_flipPlatformEnd;
};

