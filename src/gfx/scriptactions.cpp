#include <gfx/scriptactions.h>
#include <gfx/engine.h>
#include <gfx/scheduler.h>


void SuspendScript::Start() {
    auto scheduler = Engine::get().GetRef<Scheduler>("_scheduler");
    scheduler->GetScript(m_script)->SetSuspended(true);
    SetComplete();

}

void ResumeScript::Start() {
    auto scheduler = Engine::get().GetRef<Scheduler>("_scheduler");
    scheduler->GetScript(m_script)->SetSuspended(false);
    SetComplete();

}