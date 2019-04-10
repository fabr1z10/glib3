#pragma once

#include <string>
#include <gfx/activities/targetactivity.h>

class Flip : public TargetActivity {
public:
    // mode = 0: just flip
    // mode = 1: flip right (ie no horizontal flip)
    // mode = 2: flip left (horizontal flip)
    Flip(int mode);
    void Start() override;
    void Run(float) override {}
private:
    int m_value;
    std::string m_actor;
};

