#include <gfx/scheduler.h>

void Scheduler::Update(double dt) {
    std::vector<std::string> toRemove;
    for (auto& s : m_scripts) {
        s.second->Run(dt);
        if (s.second->IsComplete()) {
            toRemove.push_back(s.first);
        }
    }

    for (auto& s : toRemove)
        m_scripts.erase(s);
}
void Scheduler::AddScript(const std::string &name, std::shared_ptr<Script> script) {
    if (m_scripts.count(name) > 0)
        m_scripts.erase(name);
    m_scripts[name] = script;
    script->Start();

}

