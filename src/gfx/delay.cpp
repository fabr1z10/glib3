#include <gfx/delay.h>

void DelayTime::Run(float dt) {
    m_elapsed +=dt;
    if (m_elapsed >= m_time) {
        SetComplete();
    }
}