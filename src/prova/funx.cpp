#include "example.h"
#include <monkey/monkey.h>
#include <monkey/engine.h>
#include <monkey/entity.h>
#include <monkey/script.h>
#include <monkey/entities/textview.h>

Wrap1 get(const std::string & tag) {
    auto e = m_monkey->Get<Entity>(tag);
    Wrap1 w;
    w.setEntity(e);
    return w;

}

void rmv(int id) {
    if (m_monkey->isAlive(id)) {
        std::cerr << "is alive tes " << id;
        auto entity = m_monkey->Get<Entity>(id);
        m_engine->Remove(entity);
    }
}

void rmvt(const std::string& tag) {
    auto entity = m_monkey->Get<Entity>(tag);
    m_engine->Remove(entity);
}

std::vector<float> campos(const std::string& camId) {
    glm::vec3 pos = m_monkey->Get<Camera>(camId)->GetPosition();
    return {pos.x, pos.y, pos.z};
}
//void addLine(const std::string& tag, pybind11::object& o) {
//    auto entity = m_monkey->Get<Entity>(tag);
//    auto* t = dynamic_cast<TextView*>(entity);
//    t->AddItem(o);
//}

void play (pybind11::object o) {
    std::cout << "CIAO!\n";

    auto scheduler = m_engine->GetRunner<Scheduler>();
    PyTable t(o);

    auto script = std::make_shared<Script>(t);
    scheduler->AddScript(script);

}

void restart() {
    m_engine->restart();
}
pybind11::list getDeviceSize() {
    glm::vec2 size=  m_engine->GetDeviceSize();
    pybind11::list c;
    c.append(size[0]);
    c.append(size[1]);
    return c;
}