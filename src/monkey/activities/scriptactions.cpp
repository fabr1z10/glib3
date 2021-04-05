#include <monkey/activities/scriptactions.h>
#include <monkey/engine.h>
#include <monkey/scheduler.h>


SuspendScript::SuspendScript(const ITab & t)  {
    m_script = t.get<std::string>("script");
}

ResumeScript::ResumeScript(const ITab & t)  {
    m_script = t.get<std::string>("script");
}
KillScript::KillScript(const ITab & t)  {
	m_script = t.get<std::string>("script");
}
void SuspendScript::Start() {
    auto scheduler = Engine::get().GetRunner<Scheduler>();
    scheduler->GetScript(m_script)->SetSuspended(true);
    SetComplete();

}


SuspendActiveScripts::SuspendActiveScripts(bool value) : Activity(), m_value(value) {
    auto scheduler = Engine::get().GetRunner<Scheduler>();
    m_scriptsToSuspend = scheduler->GetActiveScripts();
}

void SuspendActiveScripts::Start() {
    auto scheduler = Engine::get().GetRunner<Scheduler>();
    for (const auto& s : m_scriptsToSuspend) {
        scheduler->GetScript(s)->SetSuspended(m_value);
    }
    SetComplete();

}




void ResumeScript::Start() {
    auto scheduler = Engine::get().GetRunner<Scheduler>();
    scheduler->GetScript(m_script)->SetSuspended(false);
    SetComplete();

}

void KillScript::Start() {
    auto scheduler = Engine::get().GetRunner<Scheduler>();
    if (scheduler->HasScript(m_script)) {
        scheduler->GetScript(m_script)->Kill();
    }
    SetComplete();

}