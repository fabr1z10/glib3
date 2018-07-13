#include <gfx/scheduler.h>
#include <gfx/error.h>

void Scheduler::Update(double dt) {
    if (!m_active)
        return;
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

void Scheduler::AddScript(std::shared_ptr<Script> script) {
    std::stringstream stream;
    stream << "_unknown_" << m_count++ ;
    AddScript(stream.str(), script);

}

Script* Scheduler::GetScript (const std::string& name) {
    auto it = m_scripts.find(name);
    if (it == m_scripts.end())
        GLIB_FAIL("Unknown script " << name);
    return it->second.get();
}
