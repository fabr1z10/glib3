#pragma once

#include <monkey/activity.h>

class Repeat : public Activity {
public:
    //Repeat(luabridge::LuaRef func, float interval);
    Repeat (const ITab&);
    void Start() override;
    void Run (float dt) override;
private:
    pybind11::function m_func;
    //luabridge::LuaRef m_func;
    float m_interval;
    float m_timer;
};
