#pragma once

#include <gfx/component.h>
#include <gfx/script.h>
#include <unordered_map>

class Scheduler : public Component {
public:
    Scheduler() : Component(), m_count{0}{}
    void Start() override{}
    void Update(double) override;
    void AddScript (const std::string& name, std::shared_ptr<Script> script);
    void AddScript (std::shared_ptr<Script> script);
    void KillScript (const std::string& name);
    void Clear ();
    Script* GetScript (const std::string&);
    using ParentClass = Scheduler;
private:
    std::unordered_map<std::string, std::shared_ptr<Script> > m_scripts;
    int m_count;
};


inline void Scheduler::Clear () {
    m_scripts.clear();
}

