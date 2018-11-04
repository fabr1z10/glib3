#pragma once

#include <string>
#include <gfx/activity.h>

class Flip : public Activity {
public:
    Flip(const std::string& id, bool horizontal);
    void Start() override;
    void Run(float) override {}
private:
    bool m_value;
    std::string m_actor;
};

