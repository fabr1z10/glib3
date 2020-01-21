#include <monkey/activities/flip.h>
#include <monkey/activities/targetactivity.h>
#include <monkey/entity.h>
#include <monkey/engine.h>

Flip::Flip(int mode) : TargetActivity(), m_value(mode) {}

void Flip::Start() {
    TargetActivity::Start();
    if (m_value == 0) {
        m_entity->FlipX();
    } else {
        m_entity->SetFlipX(m_value == 2);
    }

    SetComplete();
}