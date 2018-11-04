#pragma once

#include <gfx/activity.h>
#include <string>

class VirtualKey : public Activity {
public:
    VirtualKey(int keyCode, int action);

    void Start() override;

    void Run(float dt) override {}

private:
    int m_keyCode;
    int m_action;
};