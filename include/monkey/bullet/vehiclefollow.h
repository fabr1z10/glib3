#pragma once

#include "monkey/component.h"
#include "btBulletDynamicsCommon.h"

#include <monkey/camera.h>

class VehicleFollow : public Component {
public:
    VehicleFollow (const ITab&);
    void Start() override;
    void Begin() override;
    void Update(double) override;
private:
    btRaycastVehicle* m_vehicle;
    Camera* m_cam;
    glm::vec3 m_eye;
    glm::vec3 m_dir;
    glm::vec3 m_up;
};



