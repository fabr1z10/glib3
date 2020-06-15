#include <monkey/activities/setactive.h>
#include <monkey/monkey.h>

SetActive::SetActive(const std::string &tag, bool active) : Activity(), m_tag(tag), m_active(active) {
}

void SetActive::Start() {
    Monkey::get().Get<Ref>(m_tag)->setActive(m_active);
    SetComplete();
}