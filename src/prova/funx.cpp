#include "example.h"
#include <monkey/monkey.h>
#include <monkey/engine.h>
#include <monkey/entity.h>
#include <monkey/script.h>

Wrap1 get(const std::string & tag) {
    auto e = m_monkey->Get<Entity>(tag);
    Wrap1 w;
    w.setEntity(e);
    return w;

}


void play (pybind11::object o) {
    std::cout << "CIAO!\n";

    auto scheduler = m_engine->GetRunner<Scheduler>();
    PyTable t(o);

    auto script = std::make_shared<Script>(t);
    scheduler->AddScript(script);

}

pybind11::list getDeviceSize() {
    glm::vec2 size=  m_engine->GetDeviceSize();
    pybind11::list c;
    c.append(size[0]);
    c.append(size[1]);
    return c;
}