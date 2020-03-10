#include <monkey/activities/setactive.h>
#include <monkey/monkey.h>
#include <monkey/lua/luatable.h>

SetActive::SetActive(const std::string &tag, bool active) : Activity(), m_tag(tag), m_active(active) {
}

SetActive::SetActive(const LuaTable & t) : Activity() {
    m_tag = t.Get<std::string>("tag");
    m_active = t.Get<bool>("active");

}

void SetActive::Start() {
    Monkey::get().Get<Ref>(m_tag)->setActive(m_active);
    SetComplete();
}