#pragma once

#include <monkey/component.h>
#include <glm/glm.hpp>

// properties for dynamics
class Depth25 : public Component {
public:
    Depth25(float gravity, float x, float depth, float elevation);
    Depth25(const Depth25&);
    float step(float dt);
    glm::vec3 move(float dx, float ddepth, float delev);
    float getElevation () const;
    float getDepth() const {return m_depth;}
    void setElevation(float);
    glm::vec3 getActualPos() const;
    glm::vec3 getScreenPos() const;
    void Start() override;
    void setVelocityY(float);
    float getVelocityY() const;
    glm::vec3& getVelocity();
private:
    glm::vec3 m_velocity;
    float m_gravity;
    //float m_vy;
    float m_x;
    float m_depth;
    float m_elevation;
};



inline glm::vec3 Depth25::getActualPos() const {
    return glm::vec3(m_x, m_depth, 0.0f);
}

inline float Depth25::getElevation() const {
    return m_elevation;
}

inline void Depth25::setVelocityY(float vy) {
    m_velocity.y = vy;
}


inline float Depth25::getVelocityY() const {
    return m_velocity.y;
}

inline void Depth25::setElevation(float e) {
    m_elevation = e;
}

inline glm::vec3& Depth25::getVelocity() {
    return m_velocity;
}