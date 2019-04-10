#include <gfx/activities/blink.h>
#include <gfx/entity.h>
#include <gfx/engine.h>
#include <gfx/components/renderer.h>

Blink::Blink(const std::string& actorId, float totalDuration, float blinkDuration) :
        TargetActivity(), m_duration(totalDuration), m_blinkDuration(blinkDuration)
{}




void Blink::Start() {
    TargetActivity::Start();
    m_renderer = m_entity->GetComponent<Renderer>();

    if (m_renderer == nullptr)
        GLIB_FAIL("Error! No renderer found for " << m_actorId);
    m_timer = 0.0f;
    m_timer2 = 0.0f;
    m_visible = true;
}

void Blink::Run(float dt) {
    m_timer += dt;
    m_timer2 += dt;
    if (m_timer2 >= m_blinkDuration) {

        m_visible = !m_visible;
        glm::vec4 color = m_visible ? glm::vec4(1.0f) : glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
        m_renderer->SetTint(color);
        m_timer2=0.0f;
    }
    if (m_timer >= m_duration) {
        m_renderer->SetTint(glm::vec4(1.0f));
        SetComplete();
    }




}