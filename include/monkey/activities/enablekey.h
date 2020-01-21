#pragma once

#include <monkey/activity.h>

class EnableKey : public Activity {
public:
    EnableKey(int, bool);
    void Start() override;
    void Run(float dt) override {}
private:
    int m_code;
    bool m_enable;
};