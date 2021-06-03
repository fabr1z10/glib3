#include "example.h"
#include <monkey/engine.h>
#include <monkey/entity.h>
#include <monkey/input/pytab.h>

Wrap1 get(const std::string & tag) {
    Wrap1 w;
    try {
        auto e = m_monkey->Get<Entity>(tag);
        w.setEntity(e);
    } catch (Error& e) {}

    return w;


}

Wrap1 getById(int id) {
	Wrap1 w;
	try {
		auto e = m_monkey->Get<Entity>(id);
		w.setEntity(e);
	} catch (Error& e) {}

	return w;


}

void rmv(int id) {
    if (m_monkey->isAlive(id)) {
        std::cerr << "is alive tes " << id;
        auto entity = m_monkey->Get<Entity>(id);
        m_engine->Remove(entity);
    }
}


void killScript(const std::string& scriptId) {
	try {
		auto script = m_engine->GetRunner<Scheduler>()->GetScript(scriptId);
		script->Kill();
	} catch (Error& e) {}

}


void rmvt(const std::string& tag) {
    try {
        auto entity = m_monkey->Get<Entity>(tag);
        m_engine->Remove(entity);
    } catch (const Error& err) {
        std::cerr << err.what() << "\n";
    }
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

    Wrap1::runScript(*m_engine, o);

}

void restart() {
    m_engine->EndScene();
    //m_engine->restart();
}
pybind11::list getDeviceSize() {
    glm::vec2 size=  m_engine->GetDeviceSize();
    pybind11::list c;
    c.append(size[0]);
    c.append(size[1]);
    return c;
}