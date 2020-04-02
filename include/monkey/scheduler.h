#pragma once

#include <monkey/runner.h>
#include <monkey/script.h>
#include <unordered_map>

class Scheduler : public Runner {
public:
    Scheduler() : Runner(), m_count{0} {}
    Scheduler(const ITable&);
    Scheduler(const LuaTable&);
    ~Scheduler() override;
    void Update(double) override;
    void AddScript (const std::string& name, std::shared_ptr<Script> script);
    void AddScript (std::shared_ptr<Script> script);
    void KillScript (const std::string& name);
    void Clear ();
    bool HasScript(const std::string&) const;
    Script* GetScript (const std::string&);
    using ParentClass = Scheduler;
    std::vector<std::string> GetActiveScripts() const;
    std::string toString() override;
private:
    std::unordered_map<std::string, std::shared_ptr<Script> > m_queuedScripts;
    std::unordered_map<std::string, std::shared_ptr<Script> > m_scripts;
    int m_count;
};


inline void Scheduler::Clear () {
    m_scripts.clear();
}

