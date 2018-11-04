#pragma once

#include <gfx/activity.h>
#include <string>

class ChangeCamBounds : public Activity {
public:
    ChangeCamBounds(const std::string& cam, float xMin, float xMax, float yMin, float yMax);
    void Start() override ;
    void Run (float dt) override {}
private:
    std::string m_camId;
    float m_xMin;
    float m_xMax;
    float m_yMin;
    float m_yMax;
};
