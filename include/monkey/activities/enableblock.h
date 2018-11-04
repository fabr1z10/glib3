#pragma once

#pragma once

#include <gfx/activity.h>

class EnableBlock : public Activity {
public:
    EnableBlock(int wall, bool active) : Activity(), m_wall{wall}, m_active{active} {}
    void Start() override;
    void Run (float dt) override {}
private:
    int m_wall;
    bool m_active;
};
