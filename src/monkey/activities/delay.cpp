#include <monkey/activities/delay.h>


DelayTime::DelayTime(const ITab & t) : Activity() {
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


DelayTimeDynamic::DelayTimeDynamic(const ITab & t) : Activity() {
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
