#include <monkey/ref.h>
#include <monkey/engine.h>

//int Ref::g_idCount = 0;

//std::unordered_map<int, std::weak_ptr<Ref> > Ref::g_refs;
//std::unordered_map<std::string, std::weak_ptr<Ref> > Ref::g_taggedRefs;


Ref::Ref() : m_id{Monkey::get().getNextId()}, m_active{true} {
    Monkey::get().add(m_id, this);
}

Ref::Ref(const Ref & orig) : m_id{Monkey::get().getNextId()}, m_active{orig.m_active} {
    Monkey::get().add(m_id, this);
}

Ref::~Ref() {
    auto& m = Monkey::get();
    if (!m_tag.empty()) {
        m.remove(m_tag);
    }
    m.remove(m_id);
}




void Ref::SetTag(const std::string & tag) {
    auto& m = Monkey::get();
    if (!m_tag.empty()) {
        m.remove(m_tag);
    }
    m_tag = tag;
    m.add(tag, this);
}


void Ref::dump () {

}

std::string Ref::toString() {
    std::stringstream stream;
    stream << "[Ref](tag = " << m_tag << ")";
    return stream.str();
}