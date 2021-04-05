#include <monkey/components/scriptplayer.h>
#include <monkey/scheduler.h>
#include <monkey/engine.h>

ScriptPlayer::ScriptPlayer(const ITab&) {}

ScriptPlayer::~ScriptPlayer() noexcept {
    // stop all scripts associated to this entity
    for (const auto& script : m_scripts) {
        script->Kill();
    }
}

void ScriptPlayer::play(std::shared_ptr<Script> script) {
    Engine::get().GetRunner<Scheduler>()->AddScript(script);
    m_scripts.push_back(script);

}


void ScriptPlayer::killScripts() {
    for (const auto& s : m_scripts) {
        s->Kill();
    }
}
