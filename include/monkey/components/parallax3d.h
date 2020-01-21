#pragma once

#include <monkey/component.h>
#include <monkey/camera.h>

//! Parallax component
/*! Moves a background entity at a different speed with respect to the associated camera
*/
class Parallax3D : public Component {
public:
    Parallax3D (const std::string& camId, float z, const std::string& img);
    Parallax3D(const Parallax3D&);
    void Start() override;
    void Update(double) override {}
    std::shared_ptr<Component> clone() const override;
private:
    Entity* m_bg;
    void onCameraMove(Camera*);
    std::string m_camId;
    std::string m_img;
    PerspectiveCamera* m_cam;
    float m_halfPanelHeight;
    float m_panelWidth;
    float m_z;
    int m_camPos;
};
