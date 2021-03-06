#include <monkey/activities/enablekey.h>
#include <monkey/engine.h>

EnableKey::EnableKey(int code, bool enable) : Activity(), m_code(code), m_enable(enable) {}

void EnableKey::Start() {
    Engine::get().GetKeyboard().EnableKey(m_code, m_enable);
    SetComplete();
}