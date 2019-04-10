#include <gfx/activities/scale.h>
#include <gfx/entity.h>
#include <gfx/engine.h>

ScaleTo::ScaleTo(float duration, float scale) : TargetActivity(), m_duration{duration}, m_scale{scale}
{}


void ScaleTo::Start() {
    TargetActivity::Start();
    // get the initial scale

    if (m_duration == 0.0f) {

        // immediate rescale
        m_entity->SetScale(m_scale);
        SetComplete();

    } else {
        float scale = m_entity->GetScale();
        m_scaleSpeed = (m_scale - scale) / m_duration;
        m_currScale = scale;
        m_elapsedTime = 0.0f;
    }


}


void ScaleTo::Run(float dt) {
    m_elapsedTime += dt;
    if (m_elapsedTime >= m_duration) {
        m_entity->SetScale(m_scale);
        SetComplete();
    } else {
        m_currScale = m_currScale + m_scaleSpeed * dt;
        m_entity->SetScale(m_currScale);
    }

}