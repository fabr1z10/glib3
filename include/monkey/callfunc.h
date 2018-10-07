#pragma once

#include <gfx/activity.h>
#include <gfx/lua/luawrapper.h>

class CallFunc : public Activity {
public:
    CallFunc(luabridge::LuaRef func) : Activity(), m_func{func} {}
    void Start() override;
    void Run (float dt) override {}
private:
    luabridge::LuaRef m_func;
};
