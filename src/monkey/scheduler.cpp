#include <monkey/scheduler.h>
#include <monkey/error.h>
#include <iostream>

Scheduler::Scheduler(const LuaTable & table) : Runner(table) {

}

Scheduler::Scheduler(const ITable & table) : Runner(table) {

}

Scheduler::~Scheduler() {
    std::cerr << "ciao\n";
    for (auto& s : m_scripts) {
        //std::cerr << " killing a current script " << s.first << "\n";
        s.second->Kill();
        //std::cerr << "done.\n";
    }
    for (auto& s : m_queuedScripts) {
        //std::cerr << " killing a q script\n";
        s.second->Kill();
    }
    //std::cerr << "clearing scripts\n";
    m_scripts.clear();
    //std::cerr << "done.\n";
    m_queuedScripts.clear();
    //std::cerr << "scheduler killed\n";
}


void Scheduler::Update(double dt) {
    std::vector<std::string> toRemove;
    // add queued scripts
    if (!m_queuedScripts.empty()) {
        auto qs = m_queuedScripts;
        m_queuedScripts.clear();
        for (auto& q : qs) {
            m_scripts[q.first] = q.second;
            q.second->Start();
        }
    }


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
    std::string name = script->getName();
    if (name.empty()) {
        std::stringstream stream;
        stream << "_unknown_" << m_count++ ;
        name = stream.str();
    }
    AddScript(name, script);

}

bool Scheduler::HasScript(const std::string & id) const {
    return m_scripts.count(id) > 0;
}

Script* Scheduler::GetScript (const std::string& name) {
    auto it = m_scripts.find(name);
    if (it == m_scripts.end())
        GLIB_FAIL("Unknown script " << name);
    return it->second.get();
}


std::vector<std::string> Scheduler::GetActiveScripts() const {
    std::vector<std::string> s;
    for (const auto& p : m_scripts) {
        if (!p.second->IsSuspended()) {
            s.push_back(p.first);
        }
    }
    return s;
}

std::string Scheduler::toString() {
    std::stringstream stream;
    stream << "[Scheduler](tag = " << m_tag << ")";
    return stream.str();
}