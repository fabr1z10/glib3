#pragma once

#include <gfx/component.h>
#include "gfx/camera.h"
#include <string>

class Renderer;

class Billboard : public Component {
    
public:
    Billboard (const std::string& cam);
    void Start() override;
    void Update(double) override;
    using ParentClass = Billboard;
private:
    std::string m_camId;
    Camera* m_cam;
    Renderer* m_renderer;
};
