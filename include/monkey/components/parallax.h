#pragma once

#include <monkey/component.h>
#include <monkey/camera.h>

//! Parallax component
/*! Moves a background entity at a different speed with respect to the associated camera
*/
class Parallax : public Component {
public:
    Parallax (const std::string& camId, glm::vec2 factor);
    Parallax(const ITab&);
    void Start() override;
    void Begin() override;
    void Update(double) override {}
private:
    void onCameraMove(Camera*);
    std::string m_camId;
    Camera* m_cam;
    glm::vec2 m_campos0;
    glm::vec2 m_pos0;
    glm::vec2 m_factor;
    glm::vec3 m_camInitPos;
    glm::vec3 m_entityInitPos;
    float m_ax;
    float m_bx;
    float m_ay;
    float m_by;
    //glm::vec2 m_offset;
};
