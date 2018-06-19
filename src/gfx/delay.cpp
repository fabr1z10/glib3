#include <gfx/delay.h>

void DelayTime::Start()  {
    m_elapsed = 0.0f;
}

void DelayTime::Run(float dt) {
    m_elapsed +=dt;
    if (m_elapsed >= m_time) {
        SetComplete();
    }
}