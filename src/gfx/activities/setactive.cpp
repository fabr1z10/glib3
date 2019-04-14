#include <gfx/activities/setactive.h>
#include <gfx/ref.h>

SetActive::SetActive(const std::string &tag, bool active) : Activity(), m_tag(tag), m_active(active) {
}

void SetActive::Start() {
    Ref::Get<Ref>(m_tag)->setActive(m_active);
    SetComplete();
}