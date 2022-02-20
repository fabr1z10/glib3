#pragma once

#include <monkey/component.h>

class Scaler : public Component {
public:
    Scaler(const ITab&);
    void Start() override;
    void Update(double) override;

private:
    glm::vec3 m_scale;
    float m_a;
    float m_b;

};