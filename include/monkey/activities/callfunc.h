#pragma once

#include <monkey/activity.h>

class CallFunc : public Activity {
public:
    CallFunc(const ITable& t);
    void Start() override;
    void Run (float dt) override {}
private:
    pybind11::function m_f;
};
