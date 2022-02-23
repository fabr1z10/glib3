#include <monkey/components/parallax.h>
#include <monkey/engine.h>
#include <iostream>

// factor = 0 ---> item MOVES with the camera. i.e. if cam moves from x0 to x1, then item moves by the same amount
// factor = 1 ---> item doesn't  move w.r.t the camera i.e. if cam moves from x0 to x1 item stays where it is

Parallax::Parallax (const std::string& camId, glm::vec2 factor) :
m_camId(camId), m_factor(factor) {}

Parallax::Parallax(const ITab & t) : Component(t) {
    m_camId = t.get<std::string>("cam");
    m_factor = t.get<glm::vec2>("factor");
    m_campos0 = t.get<glm::vec2>("cam0");
	//m_pos0 = t.get<glm::vec2>("pos0");
    //m_offset = t.get<glm::vec2>("offset", glm::vec2(0.0f));
}

void Parallax::Begin() {
    m_cam = Monkey::get().Get<Camera>(m_camId);
	m_entityInitPos = m_entity->GetPosition();
	m_pos0 = m_entityInitPos;
	m_ax = m_factor.x;
	m_bx = m_pos0.x - m_ax * m_campos0.x ;
	m_ay = m_factor.y;
	m_by = m_pos0.y - m_ay * m_campos0.y ;



    m_cam->OnMove.Register(this, [&] (Camera* cam) { this->onCameraMove(cam); });
    onCameraMove(m_cam);


}
void Parallax::Start() {
}


void Parallax::onCameraMove(Camera * cam) {
    glm::vec3 pos = cam->GetPosition();

    float nx = m_ax * pos.x + m_bx ;
    //nx += m_offset.x;
    float ny = m_ay * pos.y + m_by; // + m_offset.y;
    float nz = m_entityInitPos.z;
    m_entity->SetPosition(glm::vec3 (nx,  ny, nz));
}
