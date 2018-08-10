#include <monkey/activityfactory.h>
#include <monkey/walk.h>
#include "gfx/noop.h"
#include "gfx/animate.h"
#include "monkey/say.h"
#include "monkey/callfunc.h"
#include "gfx/scroll.h"
#include "monkey/changeroom.h"
#include "gfx/delay.h"
#include "gfx/move.h"

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
    m_factories["callfunc"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
        luabridge::LuaRef ref = table.Get<luabridge::LuaRef>("func");
        return std::unique_ptr<CallFunc>(new CallFunc(ref));
    };
    m_factories["scroll"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
        std::string camId = table.Get<std::string>("cam");
        bool relative{false};
        glm::vec2 displacement(0.0f);
        if (table.HasKey("by")) {
            relative = true;
            displacement = table.Get<glm::vec2>("by");
        } else {
            displacement = table.Get<glm::vec2>("to");
        }
        float speed = table.Get<float>("speed");
        return std::unique_ptr<Scroll>(new Scroll(camId, displacement, relative, speed));
    };
    m_factories["gotoroom"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
        std::string roomId = table.Get<std::string>("room");
        return std::unique_ptr<ChangeRoom>(new ChangeRoom(roomId));
    };
    m_factories["animate"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
        std::string actor = table.Get<std::string>("actor");
        std::string anim = table.Get<std::string>("anim");
        int flip{0};
        if (table.HasKey("flipx")) {
            flip = table.Get<bool>("flipx") ? 2 : 1;
        }
        int loopCount = table.Get<int>("loop", 0);
        auto act = std::unique_ptr<Animate>(new Animate(actor, anim, flip));
        act->SetLoop(loopCount);
        return (std::move(act));
    };
    m_factories["delay"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
        float sec = table.Get<float>("sec");
        return std::unique_ptr<DelayTime>(new DelayTime(sec));
    };
    m_factories["move"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
        std::string actor = table.Get<std::string>("actor");
        bool relative = true;
        glm::vec2 dest;
        if (table.HasKey("to")) {
            relative = false;
            dest = table.Get<glm::vec2>("to");
        } else if (table.HasKey("by")) {
            relative = true;
            dest = table.Get<glm::vec2>("by");
        } else {
            GLIB_FAIL("move action requires to or by attribute.")
        }
        float speed = table.Get<float>("speed", 0.0f);
        bool immediate = table.Get<bool>("immediate", false);
        return std::unique_ptr<MoveTo>(new MoveTo(actor, dest, speed, relative, immediate));
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
