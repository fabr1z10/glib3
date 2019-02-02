#pragma once

#include <gfx/component.h>
#include <gfx/camera.h>

//! Parallax component
/*! Moves a background entity at a different speed with respect to the associated camera
*/
class Parallax : public Component {
public:
    Parallax (const std::string& camId, float factor, float width, float height);
    void Start() override;
    void Update(double) override {}
private:
    void onCameraMove(Camera*);
    std::string m_camId;
    OrthographicCamera* m_cam;
    float m_factor;
    float m_width;
    float m_height;
    float m_horizontalTranslation;
    float m_verticalTranslation;
    glm::vec2 m_camSize;
    //glm::vec3 m_previousPos;
    float m_x0;
    float m_deltaX;
    //int m_prevn;
};
