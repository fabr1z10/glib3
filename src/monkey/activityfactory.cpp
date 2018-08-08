#include <monkey/activityfactory.h>
#include <monkey/walk.h>
#include "gfx/noop.h"
#include "gfx/animate.h"

ActivityFactory::ActivityFactory() {
    m_factories["walkto"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
        // see who is performing the action
        std::string actor = table.Get<std::string>("actor");
        glm::vec2 pos = table.Get<glm::vec2>("pos");
        return std::unique_ptr<Walk>(new Walk(actor, pos));
    };
    m_factories["noop"] = [] (LuaTable&) -> std::unique_ptr<Activity> {
        return std::unique_ptr<NoOp>(new NoOp());
    };
    m_factories["turn"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
        // see who is performing the action
        std::string actor = table.Get<std::string>("actor");
        std::string dir = table.Get<std::string>("face");
        std::string anim;
        int flip = 1;
        if (dir == "east") {
            anim = "idle_right";
        } else if (dir == "west") {
            anim = "idle_right";
            flip = 2;
        } else if (dir == "north") {
            anim = "idle_back";
        } else if (dir == "south") {
            anim = "idle_front";
        } else {
            GLIB_FAIL("Unknown direction " << dir)
        }
        return std::unique_ptr<Animate>(new Animate(actor, anim, flip));
    };
}

std::unique_ptr<Activity> ActivityFactory::createActivity(LuaTable& table) {
    std::string type = table.Get<std::string>("type");
    auto it = m_factories.find(type);
    if (it == m_factories.end()) {
        GLIB_FAIL("Unknown activity type " << type);
    }
    return it->second(table);
}