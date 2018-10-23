#pragma once

#include <gfx/component.h>
#include <gfx/camera.h>

//! Parallax component
/*! Moves a background entity at a different speed with respect to the associated camera
*/
class Parallax : public Component {
public:
    Parallax (const std::string& camId, float factor, float reset);
    void Start() override;
    void Update(double) override {}
private:
    void onCameraMove(Camera*);
    std::string m_camId;
    Camera* m_cam;
    float m_factor;
    float m_reset;
    glm::vec3 m_previousPos;
};