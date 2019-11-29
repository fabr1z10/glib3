#include <gfx/components/depth25.h>
#include <gfx/entity.h>


Depth25::Depth25(float gravity, float x, float depth, float elevation) : Properties(), m_gravity(gravity), m_x(x),
                                                                m_depth(depth), m_elevation(elevation) {}

float Depth25::step(float dt) {

    // update the vertical velocity and elevation
    m_vy += m_gravity * dt;
    float s= m_vy*dt;
    m_elevation += s;
    return s;



}

void Depth25::Start() {

    m_entity->SetPosition(getScreenPos());
}

glm::vec3 Depth25::getScreenPos() const {
    return glm::vec3(m_x, m_depth + m_elevation, m_depth*0.01f);
}

void Depth25::move(float dx, float ddepth, float delev) {
    float scale =  m_entity->GetScale();
    m_x += scale*dx;
    m_depth += scale*ddepth;
    m_elevation += scale*delev;

}