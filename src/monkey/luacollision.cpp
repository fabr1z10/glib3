#include <monkey/luacollision.h>
#include <monkey/python/wrap1.h>

void LuaCollisionResponse::setOnEnter(pybind11::function& ref) {
    m_onEnter = ref;
}

void LuaCollisionResponse::setOnLeave(pybind11::function& ref) {
    m_onLeave = ref;
}

void LuaCollisionResponse::setOnStay(pybind11::function& ref) {
    m_onStay = ref;
}

void LuaCollisionResponse::onStart(Entity* e1, Entity* e2, const CollisionReport& report) {
    if (m_onEnter) {
        glm::vec2 separationVector = report.direction * report.distance;
        auto obj1 = Wrap1::create(e1);
        auto obj2 = Wrap1::create(e2);
        m_onEnter(obj1, obj2, separationVector.x, separationVector.y);
    }
}


void LuaCollisionResponse::onEnd(Entity* e1, Entity* e2, const CollisionReport& report) {
    if (m_onLeave) {
        glm::vec2 separationVector = report.direction * report.distance;
        auto obj1 = Wrap1::create(e1);
        auto obj2 = Wrap1::create(e2);
        m_onLeave(obj1, obj2, separationVector.x, separationVector.y);
    }

}

void LuaCollisionResponse::onStay(Entity*, Entity*, const CollisionReport& report) {
    if (m_onStay) {
        // TODO!!!
        m_onStay();
    }
}
