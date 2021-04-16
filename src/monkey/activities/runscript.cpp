#include <monkey/activities/runscript.h>
#include <monkey/engine.h>
#include <monkey/scheduler.h>
#include <monkey/input/pytab.h>

RunScript::RunScript(const ITab& t) : Activity() {

	if (t.has("func")) {
		m_scriptBuilder = t.get<pybind11::function>("func");
	} else {
		auto ts = t["script"];
		m_script = std::make_shared<Script>(*ts);
	}
}

void RunScript::Start() {
	if (m_scriptBuilder) {
		m_script = std::make_shared<Script>(PyTab(m_scriptBuilder()));

	}
    auto scheduler = Engine::get().GetRunner<Scheduler>();
    scheduler->AddScript(m_script);


}

void RunScript::Run(float dt) {
    if (m_script->IsComplete()) {
        SetComplete();
    }
}

void RunScript::Reset() {
	Activity::Reset();
	m_script->Restart();
	m_script->Start();
}

