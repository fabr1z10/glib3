#pragma once

#include <gfx/activity.h>
#include <gfx/lua/luawrapper.h>

class Repeat : public Activity {
public:
    Repeat(luabridge::LuaRef func, float interval);
    void Start() override;
    void Run (float dt) override;
private:
    luabridge::LuaRef m_func;
    float m_interval;
    float m_timer;
};
