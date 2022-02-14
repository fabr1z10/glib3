#pragma once

#include <monkey/activities/targetactivity.h>
#include <monkey/entity.h>
#include <monkey/handle.h>

class SplitQuad : public TargetActivity {
public:
    SplitQuad(const ITab&);
    virtual ~SplitQuad() { /*std::cerr << "clearing a target act\n";*/ }

    void Start() override;

    void Run(float) override {}
private:
    int m_pieces;
    float m_angularSpeed;
    float m_xSpeedFactor;
    float m_gravity;
};

