#include <monkey/luacollision.h>
#include <monkey/entitywrapper.h>

void LuaCollisionResponse::onStart(Entity* e1, Entity* e2, const CollisionReport& report) {
    if (r_enter != nullptr) {
        glm::vec2 separationVector = report.direction * report.distance;
        r_enter->operator()(EntityWrapper(e1), EntityWrapper(e2), separationVector.x, separationVector.y);

    }
}


void LuaCollisionResponse::onEnd(Entity* e1, Entity* e2, const CollisionReport& report) {
    if (r_leave != nullptr) {
        glm::vec2 separationVector = report.direction * report.distance;
        r_leave->operator()(EntityWrapper(e1), EntityWrapper(e2), separationVector.x, separationVector.y);
    }

}

void LuaCollisionResponse::onStay(Entity*, Entity*, const CollisionReport& report) {
    if (r_stay != nullptr)
        r_stay->operator()();
}
