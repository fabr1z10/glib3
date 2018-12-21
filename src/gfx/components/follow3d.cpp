#include <gfx/components/follow3d.h>
#include <gfx/engine.h>

Follow3D::Follow3D (const std::string& cam, float distance, float elevation) :
        Component(), m_camId{cam}, m_distance{distance}, m_elevation{elevation}
{
}

void Follow3D::Start() {
    m_cam = Engine::get().GetRef<Camera>(m_camId);
    m_entity->onMove.Register(this, [&](Entity* e) { this->onMove(e);});
    onMove(m_entity);
}

void Follow3D::onMove(Entity *) {
    auto wt = m_entity->GetWorldTransform();
    // get the fwd vector
    glm::vec3 fwd(wt[1][0], wt[1][1], wt[1][2]);
    glm::vec3 pos(wt[3][0], wt[3][1], wt[3][2]);
    pos -= fwd*m_distance;
    pos += glm::vec3(0.0f, 0.0f, m_elevation);
    glm::vec3 up(wt[2][0], wt[2][1], wt[2][2]);
    m_cam->SetPosition(pos, fwd, up);
}
void Follow3D::Update (double dt) {


}
