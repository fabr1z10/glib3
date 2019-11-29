#pragma once

#include <gfx/properties.h>
#include <glm/glm.hpp>

// properties for dynamics
class Depth25 : public Properties {
public:
    Depth25(float gravity, float x, float depth, float elevation);
    Depth25(const Depth25&);
    std::type_index GetType() override;
    void step(float dt);
    void move(float dx, float ddepth, float delev);
    float getElevation () const;
    void setElevation(float);
    glm::vec3 getActualPos() const;
    glm::vec3 getScreenPos() const;
    void Start() override;
private:
    float m_gravity;
    float m_vy;
    float m_x;
    float m_depth;
    float m_elevation;
};

inline std::type_index Depth25::GetType() {
    return std::type_index(typeid(Properties));
}

inline glm::vec3 Depth25::getActualPos() const {
    return glm::vec3(m_x, m_depth, 0.0f);
}

inline float Depth25::getElevation() const {
    return m_elevation;
}

inline void Depth25::setElevation(float e) {
    m_elevation = e;
}