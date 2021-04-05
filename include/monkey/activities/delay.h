#pragma once

#include <monkey/activity.h>
#include <monkey/entity.h>

class DelayTime : public Activity {
public:
    DelayTime(float sec) : Activity(), m_time{sec}, m_elapsed{0.0f} {}
    DelayTime(const ITab&);
    void Start() override ;
    void Run (float dt) override;
private:
    float m_time;
    float m_elapsed;
};

class DelayTimeDynamic : public Activity {
public:
    //DelayTimeDynamic(luabridge::LuaRef func) : Activity(), m_func{func}, m_elapsed{0.0f} {}
    DelayTimeDynamic(const ITab&);
    void Start() override ;
    void Run (float dt) override;
private:
    pybind11::function m_func;
    float m_time;
    float m_elapsed;
};
