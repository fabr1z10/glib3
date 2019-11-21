#include <gfx/components/ellipsemover.h>
#include <gfx/math/geom.h>
#include <gfx/entity.h>

EllipseMover::EllipseMover(float xrad, float yrad, float period, glm::vec2 origin) : Mover(), m_xrad(xrad), m_yrad(yrad), m_period(period), m_origin(origin) {
    m_angularSpeed = (2.0 * M_PI) / period;
    m_ab = xrad*yrad;
}

EllipseMover::EllipseMover(const EllipseMover & orig) : Mover(orig), m_xrad(orig.m_xrad), m_yrad(orig.m_yrad),
                                                        m_period(orig.m_period), m_angularSpeed(orig.m_angularSpeed) {

}

std::shared_ptr<Component> EllipseMover::clone() const {
    return std::make_shared<EllipseMover>(*this);
}

std::type_index EllipseMover::GetType() {
    return std::type_index(typeid(Mover));
}

void EllipseMover::Start() {
    m_timer = 0.0f;
}

void EllipseMover::Update(double dt) {
    if (m_xrad == 0.0f && m_yrad == 0.0f) {
        m_entity->SetPosition(m_origin);
        return;
    }
    m_timer += static_cast<float>(dt);
    if (m_timer >= m_period) {
        m_timer = m_timer-m_period;
    }
    float angle = m_angularSpeed * m_timer;
    float ca = cos(angle);
    float sa = sin(angle);
    float a = m_yrad*ca;
    float b = m_xrad*sa;
    float radius = m_ab / sqrt(a*a+b*b);
    float x = radius * ca;
    float y = radius * sa;
    glm::vec2 P = m_origin + glm::vec2(x, y);
    m_entity->SetPosition(P);


}