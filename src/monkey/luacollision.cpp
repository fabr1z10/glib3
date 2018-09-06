#include "monkey/luacollision.h"
#include "monkey/entitywrapper.h"

void LuaCollisionResponse::onStart(Entity* e1, Entity* e2, const CollisionReport& report) {
    if (r_enter != nullptr)
        r_enter->operator()(EntityWrapper(e2));
}


void LuaCollisionResponse::onEnd(Entity* e1, Entity* e2, const CollisionReport& report) {
    if (r_leave != nullptr)
        r_leave->operator()(EntityWrapper(e2));
}

void LuaCollisionResponse::onStay(Entity*, Entity*, const CollisionReport& report) {
    if (r_stay != nullptr)
        r_stay->operator()();
}
