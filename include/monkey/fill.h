#pragma once

#include <glm/glm.hpp>
#include <monkey/asset.h>
#include <monkey/py.h>

class Fill : public Object {
public:
    virtual glm::vec4 getColor (const glm::vec2& p) = 0;
};

class SolidFill : public Fill {
public:
    SolidFill(const glm::vec4&);
    SolidFill(const ITable&);
    glm::vec4 getColor (const glm::vec2& p) override;

private:
    glm::vec4 m_color;
};

class LinearGradient : public Fill {
public:
    LinearGradient(const glm::vec4& color0, const glm::vec2 P0, const glm::vec4& color1, const glm::vec2 P1);
    LinearGradient(const ITable&);
    glm::vec4 getColor (const glm::vec2& p) override;
private:
    glm::vec3 m_color0;
    glm::vec3 m_color1;
    glm::vec2 m_P0;
    glm::vec2 m_P1;
    float m_dist;

};