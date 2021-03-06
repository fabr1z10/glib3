#pragma once

#include <monkey/activity.h>
#include <monkey/camera.h>

//! Scroll class
/*! Moves a camera to a given position or by a given displacement
*/
class Scroll : public Activity {
public:
    Scroll (const std::string& camId, glm::vec2 targetPos, bool relative, float speed);
    Scroll (const ITab& t);
    void Start() override;
    void Run (float dt) override;
private:
    Camera* m_camera;
    glm::vec2 m_velocity;
    glm::vec2 m_targetPos;
    glm::vec2 m_finalPosition;
    std::string m_camId;
    bool m_relative;
    float m_speed;
    float m_distanceCovered;
    float m_distanceToCover;
};