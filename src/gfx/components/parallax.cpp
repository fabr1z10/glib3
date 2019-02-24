#include <gfx/components/parallax.h>
#include <gfx/engine.h>
#include <iostream>


Parallax::Parallax (const std::string& camId, float factor, float width, float height) : m_camId(camId), m_factor(factor), m_width(width),
m_height(height) {}

Parallax::Parallax(const Parallax& orig) : Component(orig),
m_factor(orig.m_factor), m_width(orig.m_width), m_height(orig.m_height), m_camId(orig.m_camId){
    
}

std::shared_ptr<Component> Parallax::clone() const {
    return std::make_shared<Parallax>(Parallax(*this));
}
void Parallax::Start() {
    m_cam = Engine::get().GetRef<OrthographicCamera>(m_camId);
    // at time 0, we place the background panel in such a way that I see its bottom left corner at the bottom left of the viewport
    m_cam->OnMove.Register(this, [&] (Camera* cam) { this->onCameraMove(cam); });

    // at the beginning, the distance between cam and panel is cam_halfwidth + width, so the first point is


    glm::vec3 camPos = m_cam->GetPosition();
    glm::vec2 size = m_cam->GetSize();
    m_camSize = glm::vec2(size.x * 0.5f, size.y * 0.5f);
    // compute the period after which we need to shift the panel
    // clearly for factor 1, no need to update (you also don't want to divide by zero!)
    m_deltaX = m_width / (1.0 - m_factor);
    m_x0 = camPos.x + (m_width - 2*m_camSize.x) / (1.0 - m_factor) - m_deltaX;





    glm::vec2 panelPos (camPos.x - m_camSize.x - m_width, camPos.y - m_camSize.y);

    m_entity->SetPosition(panelPos);
    m_horizontalTranslation = m_width ;//- 2*m_camSize.x;
    m_verticalTranslation = m_height ;//- 2*m_camSize.y;
    // as the camera moves, we always need to make sure that
    // P_x - panel_x in [c_w / 2, panel_width - c_w/2]
    // P_y - panel_y in [c_h / 2, panel_width - c_h/2]
    // if this is not satisfied, find (i, j) such that moving the panel by (ic_w, jc_h) satisfies the requirement
}


void Parallax::onCameraMove(Camera * cam) {
    glm::vec3 pos = cam->GetPosition();
    //glm::vec3 panel = m_entity->GetPosition();
    // IDEA: every time camera moves, I get its x
    int n = static_cast<int>((pos.x - m_x0) / m_deltaX );
    float refX = m_x0 + n * m_deltaX;
    float deltaCam = pos.x - refX;
    float xPanel = (refX - (m_width -m_camSize.x)) + m_factor * deltaCam;
    m_entity->SetPosition(glm::vec2(xPanel, pos.y - m_camSize.y));
//
//
//    glm::vec3 panelCurrentPos = m_entity->GetPosition();
//    //std::cout << "camera moved to " << pos.x << " " << pos.y << std::endl;
//    // find the displacement by the panel pos
//    glm::vec3 delta = pos - m_previousPos;
//    glm::vec3 panelDelta (delta.x * m_factor, delta.y * m_factor, 0.0f);
//    glm::vec3 panelPos = m_entity->GetPosition() + panelDelta;
//    // check conditions
//    // 1. Horizontal scrolling
//    glm::vec3 relativeCamPos = pos - panelPos;
//    std::cout << "Rel cam pos = " << relativeCamPos.x << ", " << relativeCamPos.y << "\n";
//    if (relativeCamPos.x < m_camSize.x) {
//        // camera is left of panel, move the panel backward
//        int i = static_cast<int>(std::ceil((panelPos.x + m_camSize.x - pos.x) / m_horizontalTranslation));
//        std::cout << "Moving cam by " <<i << " unit\n";
//        panelDelta.x -= i*m_horizontalTranslation;
//    } else if (relativeCamPos.x > m_width*2 - m_camSize.x) {
//        // camera is right of panel, move the panel forward
//
//        int i = static_cast<int>(std::ceil((pos.x - panelPos.x - m_width + m_camSize.x) / m_horizontalTranslation));
//        std::cout << "Moving cam by " <<i << " unit\n";
//        panelDelta.x += i*m_horizontalTranslation;
//    }
//    // 2. Vertical scrolling
    // m_entity->MoveOrigin(panelDelta);


//    m_entity->Get
//    m_entity->Move(glm::vec3(delta.x*m_factor, delta.y*m_factor,0.0f));
//    // check conditions
//
//
//
    //m_previousPos = pos;
}
