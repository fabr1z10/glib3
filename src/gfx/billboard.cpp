#include "gfx/billboard.h"
#include "gfx/engine.h"
#include "gfx/entity.h"
#include "gfx/renderer.h"
#include <iostream>

Billboard::Billboard(const std::string& camId) : Component(), m_camId(camId) {}

void Billboard::Start() {
    m_cam = Engine::get().GetRef<Camera>(m_camId);
    m_renderer = m_entity->GetComponent<Renderer>();
}

void Billboard::Update(double) {

    glm::mat4 m = (m_cam->m_viewMatrix);
    glm::mat3 rotMat(m);
    glm::vec3 d(m[3]);
    float sc=1.0f;
    glm::vec3 retVec = -d * rotMat;
    //return retVec;
    glm::vec3 pos = m_entity->GetPosition();
    glm::vec3 camDir = pos - retVec;
    camDir.x =0;
    //camDir.y = std::abs(camDir.y);
    std::cout << "---\n";
    if (m_entity->GetTag() == "pippo") {
    std::cout << camDir.x << "," << camDir.y << "," << camDir.z << "\n";
    std::cout << retVec.x << "," << retVec.y << "," << retVec.z << "\n";
    
    }
    glm::vec3 e = -glm::normalize(camDir);
    glm::vec3 right(m[0]);
    right = glm::normalize(right);
    glm::mat4 tt(1.0f);
    tt[0][0] = 1.0;
    tt[0][1] = 0;
    tt[0][2] = 0;
    
    tt[2][0] = e.x;
    tt[2][1] = e.y;
    tt[2][2] = e.z;
    
    glm::vec3 ii = -glm::cross(right, e);
    tt[1][0] = 0;//ii.x;
    tt[1][1] = 0;//ii.y;
    tt[1][2] = 1;//ii.z;
    m_renderer->SetRenderingTransform(tt);
}
