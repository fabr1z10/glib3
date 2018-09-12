#pragma once

#include <gfx/activity.h>
#include <string>

class SuspendScript : public Activity {
public:
    SuspendScript(const std::string& script) : Activity(), m_script{script} {}
    void Start() override ;
    void Run (float dt) override {}
private:
    std::string m_script;
};


class ResumeScript : public Activity {
public:
    ResumeScript(const std::string& script) : Activity(), m_script{script} {}
    void Start() override ;
    void Run (float dt) override {}
private:
    std::string m_script;
};

class KillScript : public Activity {
public:
    KillScript(const std::string& script) : Activity(), m_script{script} {}
    void Start() override ;
    void Run (float dt) override {}
private:
    std::string m_script;
};
