#include <monkey/components/cursor.h>
#include <iostream>
#include <monkey/entity.h>

Cursor::Cursor(const Cursor &other) : Component(other) {
}

std::shared_ptr<Component> Cursor::clone() const {
    return std::make_shared<Cursor>(Cursor(*this));
}


void Cursor::setActive(bool value) {
    Ref::setActive(value);
    MouseListener::Enable(value);
}

void Cursor::Start() {
    Entity* e = m_entity;
    while (e->GetCamera() == nullptr)
        e = e->GetParent();
    m_cam = e->GetCamera();

}
void Cursor::CursorPosCallback(GLFWwindow*, double x, double y) {
    //glm::vec4 viewport = m_cam->GetScreenViewPort();
    if (m_cam->IsInViewport(x, y)) {
        //if (!m_entity->IsActive())
        //    m_entity->SetActive(true);
        glm::vec2 wp = m_cam->GetWorldCoordinates(glm::vec2(x,y));
        //std::cout << x << ", " << y << " " << wp.x << ", " << wp.y <<std::endl;
        m_entity->SetPosition(wp);
    } else {
        //m_entity->SetActive(false);
    }
    //glm::vec2 size = m_cam->GetSize();



}

