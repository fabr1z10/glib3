#include <gfx/ref.h>
#include <gfx/engine.h>

int Ref::g_idCount = 0;
std::unordered_map<int, Ref*> Ref::g_refs;

Ref::Ref() : m_id{g_idCount++}{
    g_refs[m_id] = this;
}

Ref::~Ref() {
    //std::cout << "destroying ref\n";
    if (!m_tag.empty()) {
        Engine::get().RemoveTaggedRef(m_tag);
        m_tag.clear();
    }
    g_refs.erase(m_id);

}

bool Ref::IsAlive(int id) {
    return g_refs.count(id) > 0;
}

Ref* Ref::Get(int id) {
    auto it = g_refs.find(id);
    if (it == g_refs.end())
        return nullptr;
    return it->second;

}


void Ref::SetTag(const std::string & tag) {
    m_tag = tag;
    Engine::get().AddTaggedRef(m_tag, this);
}
