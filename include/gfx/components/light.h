#pragma once

#include "gfx/component.h"
#include <glm/glm.hpp>

class Light : public Component {
public:
    Light (glm::vec3 color) : Component(), m_color(color) {}
    virtual ~Light();
    void Start() override;
    void Update(double) override {}
    glm::vec3 GetColor() const;
private:
    glm::vec3 m_color;
};

inline glm::vec3 Light::GetColor() const {
    return m_color;
}


