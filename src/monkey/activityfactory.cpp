#include <monkey/activityfactory.h>
#include <monkey/walk.h>

ActivityFactory::ActivityFactory() {
    m_factories["walkto"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
        // see who is performing the action
        std::string actor = table.Get<std::string>("actor");
        glm::vec2 pos = table.Get<glm::vec2>("pos");
        return std::unique_ptr<Walk>(new Walk(actor, pos));
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