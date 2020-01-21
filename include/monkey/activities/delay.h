#pragma once

#include <monkey/activity.h>
#include <monkey/entity.h>
#include <monkey/lua/luawrapper.h>

class DelayTime : public Activity {
public:
    DelayTime(float sec) : Activity(), m_time{sec}, m_elapsed{0.0f} {}
    void Start() override ;
    void Run (float dt) override;
private:
    float m_time;
    float m_elapsed;
};

class DelayTimeDynamic : public Activity {
public:
    DelayTimeDynamic(luabridge::LuaRef func) : Activity(), m_func{func}, m_elapsed{0.0f} {}
    void Start() override ;
    void Run (float dt) override;
private:
    luabridge::LuaRef m_func;
    float m_time;
    float m_elapsed;
};
