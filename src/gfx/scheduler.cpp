#include <gfx/scheduler.h>
#include <gfx/error.h>

void Scheduler::Update(double dt) {
    std::vector<std::string> toRemove;
    // add queued scripts
    for (auto& q : m_queuedScripts) {
        m_scripts[q.first] = q.second;
        q.second->Start();
    }
    m_queuedScripts.clear();

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
    if (m_scripts.count(name) > 0) {
        // a script with the same name already exists. Suspend it
        m_scripts[name]->SetSuspended(true);
    }
    m_queuedScripts[name] = script;

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
