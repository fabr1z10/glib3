#include <gfx/ref.h>
#include <gfx/engine.h>

int Ref::g_idCount = 0;

Ref::~Ref() {
    if (!m_tag.empty()) {
        Engine::get().RemoveTaggedRef(m_tag);
        m_tag.clear();
    }
}


void Ref::SetTag(const std::string & tag) {
    m_tag = tag;
    Engine::get().AddTaggedRef(m_tag, this);
}
