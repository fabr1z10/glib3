#pragma once

#include <monkey/component.h>
#include <glm/glm.hpp>

class InputMethod;

class ControllerVehicle : public Component {
public:
    ControllerVehicle(const ITab&);
    void Start() override;
    void Update(double) override;

private:
    InputMethod * m_input;
    float m_acceleration;
    float m_velocity;
    float m_damp;
    float m_currentSpeed;
};