#include <gfx/scriptactions.h>
#include <gfx/engine.h>
#include <gfx/scheduler.h>


void SuspendScript::Start() {
    auto scheduler = Engine::get().GetRunner<Scheduler>();
    scheduler->GetScript(m_script)->SetSuspended(true);
    SetComplete();

}

void ResumeScript::Start() {
    auto scheduler = Engine::get().GetRunner<Scheduler>();
    scheduler->GetScript(m_script)->SetSuspended(false);
    SetComplete();

}

void KillScript::Start() {
    auto scheduler = Engine::get().GetRunner<Scheduler>();
    scheduler->GetScript(m_script)->Kill();
    SetComplete();

}