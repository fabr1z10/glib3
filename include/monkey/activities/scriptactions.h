#pragma once

#include <monkey/activity.h>
#include <string>

class SuspendScript : public Activity {
public:
    SuspendScript(const std::string& script) : Activity(), m_script{script} {}
    SuspendScript(const LuaTable&);
    void Start() override ;
    void Run (float dt) override {}
private:
    std::string m_script;
};

class SuspendActiveScripts : public Activity {
public:
    SuspendActiveScripts(bool) ;
    void Start() override ;
    void Run (float dt) override {}
private:
    bool m_value;
    std::vector<std::string> m_scriptsToSuspend;
};


class ResumeScript : public Activity {
public:
    ResumeScript(const std::string& script) : Activity(), m_script{script} {}
    ResumeScript(const LuaTable&);
    void Start() override ;
    void Run (float dt) override {}
private:
    std::string m_script;
};

class KillScript : public Activity {
public:
    KillScript(const std::string& script) : Activity(), m_script{script} {}
    KillScript(const LuaTable&);
    void Start() override ;
    void Run (float dt) override {}
private:
    std::string m_script;
};
