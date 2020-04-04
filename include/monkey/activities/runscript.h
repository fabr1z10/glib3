#pragma once

#include <monkey/activity.h>
#include <monkey/script.h>
#include <monkey/py.h>

class RunScript : public Activity {
public:

    RunScript (const ITable& t);
    void Start() override;
    void Run (float dt) override;
private:
    std::shared_ptr<Script> m_script;
};