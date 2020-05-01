#include <monkey/activities/delay.h>
#include <monkey/lua/luatable.h>

DelayTime::DelayTime(const LuaTable & t) : Activity() {
    m_time = t.Get<float>("sec");
}

DelayTime::DelayTime(const ITable & t) : Activity() {
    m_time = t.get<float>("sec");
}

void DelayTime::Start()  {
    m_elapsed = 0.0f;
}

void DelayTime::Run(float dt) {
    m_elapsed +=dt;
    if (m_elapsed >= m_time) {
        SetComplete();
    }
}

DelayTimeDynamic::DelayTimeDynamic(const LuaTable & t) : Activity() {

}

DelayTimeDynamic::DelayTimeDynamic(const ITable & t) : Activity() {
    m_func = t.get<pybind11::function>("func");
}

void DelayTimeDynamic::Start()  {
    m_time = m_func().cast<float>();
    m_elapsed = 0.0f;
}

void DelayTimeDynamic::Run(float dt) {
    m_elapsed +=dt;
    if (m_elapsed >= m_time) {
        SetComplete();
    }
}
