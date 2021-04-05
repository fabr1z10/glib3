#include <monkey/fill.h>
#include <monkey/math/geom.h>

SolidFill::SolidFill(const glm::vec4 & color) : m_color(color) {
    m_color /= 255.0f;
}

SolidFill::SolidFill(const ITab & t) {
    m_color = t.get<glm::vec4>("color");
    m_color /= 255.0f;
}

glm::vec4 SolidFill::getColor(const glm::vec2&) {
    return m_color;
}

LinearGradient::LinearGradient(const glm::vec4 &color0, const glm::vec2 P0, const glm::vec4 &color1,
                               const glm::vec2 P1) : m_color0(color0), m_P0(P0), m_color1(color1), m_P1(P1)
{
    m_dist = glm::length(m_P1 - m_P0);
}

LinearGradient::LinearGradient(const ITab & t) {
    m_color0 = t.get<glm::vec3>("color0");
    m_color1 = t.get<glm::vec3>("color1");
    m_color0 /= 255.0f;
    m_color1 /= 255.0f;
    m_P0 = t.get<glm::vec2>("p0");
    m_P1 = t.get<glm::vec2>("p1");
    m_dist = glm::length(m_P1 - m_P0);

}

glm::vec4 LinearGradient::getColor(const glm::vec2 &p) {
    float l = glm::dot(p - m_P0, m_P1 - m_P0) / m_dist;
    l = Clamp(l, 0.0f, 1.0f);
    if (l <= 0.0f) {
        return glm::vec4(m_color0, 1.0f);
    } else if (l >= 1.0f) {
        return glm::vec4(m_color1, 1.0f);
    }
    glm::vec3 interpColor = (1.0f - l) * m_color0 + l * m_color1;
    return glm::vec4(interpColor, 1.0f);
}