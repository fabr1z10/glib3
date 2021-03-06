#pragma once

#include <monkey/activity.h>
#include <monkey/script.h>

class RunScript : public Activity {
public:

    RunScript (const ITab& t);
    void Start() override;
    void Run (float dt) override;
    void Reset() override;
private:
    std::shared_ptr<Script> m_script;
    pybind11::function m_scriptBuilder;
};