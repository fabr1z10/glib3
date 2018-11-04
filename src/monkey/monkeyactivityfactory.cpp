#include <monkey/monkeyactivityfactory.h>
#include <monkey/activities/enableblock.h>
#include <monkey/activities/walk.h>
#include <monkey/activities/say.h>

MonkeyActivityFactory::MonkeyActivityFactory() : BasicActivityFactory() {

    m_factories["activatewall"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
        int wallId = table.Get<int>("wall");
        bool active = table.Get<bool>("active");
        return std::unique_ptr<EnableBlock>(new EnableBlock(wallId, active));
    };

    m_factories["say"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
        std::string actor = table.Get<std::string>("actor");
        std::vector<std::string> msg = table.GetVector<std::string>("message");
        glm::vec4 color = table.Get<glm::vec4>("color");
        glm::vec2 offset = table.Get<glm::vec2>("offset", glm::vec2(0.0f));
        color/=255.0f;
        auto say = std::unique_ptr<Say>(new Say(actor, msg, color, offset));
        std::string animStart = table.Get<std::string>("animstart", "");
        std::string animEnd = table.Get<std::string>("animend","");
        bool noAnim = table.Get<bool>("noanim", false);
        say->SetAnimationEnd(animEnd);
        say->SetAnimationStart(animStart);
        say->SetNoAnim(noAnim);
        return std::move(say);
    };

    m_factories["walkto"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
        // see who is performing the action
        std::string actor = table.Get<std::string>("actor");
        glm::vec2 pos = table.Get<glm::vec2>("pos");
        return std::unique_ptr<Walk>(new Walk(actor, pos));
    };
}