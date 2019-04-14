#include <gfx/ref.h>
#include <gfx/engine.h>

int Ref::g_idCount = 0;

std::unordered_map<int, std::weak_ptr<Ref> > Ref::g_refs;
std::unordered_map<std::string, std::weak_ptr<Ref> > Ref::g_taggedRefs;


Ref::Ref() : m_id{g_idCount++}, m_active{true} {
}

Ref::Ref(const Ref & orig) : m_id{g_idCount++}, m_active{orig.m_active} {
}

Ref::~Ref() {
    if (!m_tag.empty()) {
        g_taggedRefs.erase(m_tag);
    }
    g_refs.erase(m_id);
}

bool Ref::isAlive(int id) {
    return (g_refs.count(id) > 0 && !g_refs.at(id).expired());
}



void Ref::SetTag(const std::string & tag) {
    m_tag = tag;
    Ref::g_taggedRefs.insert(std::make_pair(m_tag, g_refs.at(m_id)));
}


void Ref::dump () {
    for (const auto& item : g_refs) {
        auto ptr = item.second.lock();
        if (ptr) {
            std::cout << item.first << " .. " << ptr->toString() << "\n";
        } else {
            std::cout << item.first << " !! invalid\n";
        }
    }

}

std::string Ref::toString() {
    std::stringstream stream;
    stream << "[Ref](tag = " << m_tag << ")";
    return stream.str();
}