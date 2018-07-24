#pragma once

#include <gfx/activity.h>
#include <gfx/camera.h>

//! Scroll class
/*! Moves a camera to a given position or by a given displacement
*/
class Scroll : public Activity {
public:
    Scroll (int activityId, const std::string& camId, glm::vec2 targetPos, bool relative, float speed);
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