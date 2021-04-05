#pragma once

#include <monkey/activity.h>
#include <string>

class ChangeCamBounds : public Activity {
public:
    ChangeCamBounds(const std::string& cam, float xMin, float xMax, float yMin, float yMax);
    ChangeCamBounds(const ITab&);
    void Start() override ;
    void Run (float dt) override {}
private:
    std::string m_camId;
    float m_xMin;
    float m_xMax;
    float m_yMin;
    float m_yMax;
};
