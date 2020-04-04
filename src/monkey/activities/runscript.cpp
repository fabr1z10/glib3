#include <monkey/activities/runscript.h>
#include <monkey/engine.h>
#include <monkey/scheduler.h>

RunScript::RunScript(const ITable& t) : Activity() {

    auto ts = t.get<PyTable>("script");
    m_script = std::make_shared<Script>(ts);
}

void RunScript::Start() {
    auto scheduler = Engine::get().GetRunner<Scheduler>();
    scheduler->AddScript(m_script);

}

void RunScript::Run(float dt) {
    if (m_script->IsComplete()) {
        SetComplete();
    }
}

