#include "monkey/bullet/vehiclefollow.h"
#include "monkey/bullet/vehicle.h"
#include "monkey/entity.h"


VehicleFollow::VehicleFollow(const ITab& tab) {
    m_eye = tab.get<glm::vec3>("eye", glm::vec3(0.0f, 2.0f, -15.0f));
    m_dir = tab.get<glm::vec3>("dir", glm::vec3(0.0f, 0.0f, 1.0f));
    m_up = tab.get<glm::vec3>("up", glm::vec3(0.0f, 1.0f, 0.0f));
}

void VehicleFollow::Start() {
    m_cam = Monkey::get().Get<Camera>("maincam");

}

void VehicleFollow::Begin() {
    auto m = m_entity->GetWorldTransform();
    auto eye = m * glm::vec4(m_eye, 1.0f);
    auto dir = m * glm::vec4(m_dir, 0.0f);
    auto up = m * glm::vec4(m_up, 0.0f);

    m_cam->SetPosition(eye, dir, up);
    //m_previousPosition = pos
}

void VehicleFollow::Update(double) {
    auto m = m_entity->GetWorldTransform();
    auto eye = m * glm::vec4(m_eye, 1.0f);
    auto dir = m * glm::vec4(m_dir, 0.0f);
    auto up = m * glm::vec4(m_up, 0.0f);

    m_cam->SetPosition(eye, dir, up);

}