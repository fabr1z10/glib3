#include "monkey/components/texanimator.h"
#include "monkey/components/renderer.h"
#include "monkey/entity.h"
#include "monkey/math/geomalgo.h"

TexAnimator::TexAnimator(const ITab & t) {
    m_T = t.get<glm::vec2> ("period");
    m_sgn.x = m_T.x > 0 ? 1.0f : (m_T.x < 0 ? -1.0f : 0.0f);
    m_sgn.y = m_T.y > 0 ? 1.0f : (m_T.y < 0 ? -1.0f : 0.0f);
    m_T.x = fabs(m_T.x);
    m_T.y = fabs(m_T.y);
}

void TexAnimator::Start() {
    m_renderer = m_entity->GetComponent<Renderer>();
    m_t = glm::vec2(0.0f);



}

void TexAnimator::Update(double dt) {
    m_t.x += dt;
    m_t.y += dt;
    if (m_t.x >= m_T.x) {
        m_t.x = m_T.x - m_t.x;
    }
    if (m_t.y >= m_T.y) {
        m_t.y = m_T.y - m_t.y;
    }
    m_offset.x = m_T.x == 0.0f ? 0.0f : (m_sgn.x * m_t.x/m_T.x);
    m_offset.y = m_T.y == 0.0f ? 0.0f : (m_sgn.y * m_t.y/m_T.y);
    m_renderer->setTextureOffset(m_offset);

}


