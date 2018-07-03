#pragma once

#include <gfx/activity.h>
#include <string>

class SuspendScript : public Activity {
public:
    SuspendScript(int activityId, const std::string& script) : Activity(activityId), m_script{script} {}
    void Start() override ;
    void Run (float dt) override {}
private:
    std::string m_script;
};


class ResumeScript : public Activity {
public:
    ResumeScript(int activityId, const std::string& script) : Activity(activityId), m_script{script} {}
    void Start() override ;
    void Run (float dt) override {}
private:
    std::string m_script;
};
