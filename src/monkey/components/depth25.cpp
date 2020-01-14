#include <monkey/components/depth25.h>
#include <monkey/entity.h>


Depth25::Depth25(float gravity, float x, float depth, float elevation) : Properties(), m_gravity(gravity), m_x(x),
                                                                m_depth(depth), m_elevation(elevation), m_velocity(glm::vec3(0.0f))
{
    m_getters.insert(std::make_pair("vx", std::unique_ptr<Accessor<float>>(new Accessor<float>(&(m_velocity.x), true))));


}

float Depth25::step(float dt) {

    // update the vertical velocity and elevation
    m_velocity.y += m_gravity * dt;
    float s= m_velocity.y * dt;
    m_elevation += s;
    return s;



}

void Depth25::Start() {

    m_entity->SetPosition(getScreenPos());
    m_velocity = glm::vec3(0.0f);
}

glm::vec3 Depth25::getScreenPos() const {
    return glm::vec3(m_x, m_depth + m_elevation, -m_depth*0.01f);
}

glm::vec3 Depth25::move(float dx, float ddepth, float delev) {
    float scale =  m_entity->GetScale();
    m_x += scale*dx;
    m_depth += scale*ddepth;
    m_elevation += scale*delev;
	// TODO: do we neeed this?
	return glm::vec3(0.0f);
}