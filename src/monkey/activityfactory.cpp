//#include <monkey/activityfactory.h>
//#include <monkey/activities/noop.h>
//#include <monkey/activities/animate.h>
//#include <monkey/activities/callfunc.h"
//#include <monkey/activities/scroll.h"
//#include <monkey/activities/changeroom.h"
//#include <monkey/activities/delay.h"
//#include <monkey/activities/move.h"
//#include <monkey/activities/scriptactions.h"
//#include <monkey/math/geom.h>
//#include <monkey/activities/showmessage.h>
//#include <monkey/activities/rotate.h>
//#include <monkey/activities/collisioncheck.h>
//#include <monkey/compfactories.h>
//#include <monkey/activities/changestate.h>
//
//
//BasicActivityFactory::BasicActivityFactory() {
//
////    m_factories["noop"] = [] (LuaTable&) -> std::unique_ptr<Activity> {
////        return std::unique_ptr<NoOp>(new NoOp());
////    };
//    m_factories["turn"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
//        // see who is performing the action
//        std::string actor = table.Get<std::string>("actor");
//        std::string dir = table.Get<std::string>("face");
//        std::string anim;
//        int flip = 1;
//        if (dir == "east") {
//            anim = "idle_right";
//        } else if (dir == "west") {
//            anim = "idle_right";
//            flip = 2;
//        } else if (dir == "north") {
//            anim = "idle_back";
//        } else if (dir == "south") {
//            anim = "idle_front";
//        } else {
//            GLIB_FAIL("Unknown direction " << dir)
//        }
//        return std::unique_ptr<Animate>(new Animate(actor, anim, flip));
//    };
//
//
//
//
//
//
//
//
//
//
//    m_factories["suspendscript"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
//        std::string s = table.Get<std::string>("script");
//        return std::unique_ptr<SuspendScript>(new SuspendScript(s));
//    };
//    m_factories["resumescript"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
//        std::string s = table.Get<std::string>("script");
//        return std::unique_ptr<ResumeScript>(new ResumeScript(s));
//    };
//    m_factories["killscript"] = [] (LuaTable& table) -> std::unique_ptr<Activity> {
//        std::string s = table.Get<std::string>("script");
//        return std::unique_ptr<KillScript>(new KillScript(s));
//    };
//
//}
//
//std::unique_ptr<Activity> BasicActivityFactory::createActivity(LuaTable& table) {
//    std::string type = table.Get<std::string>("type");
//    auto it = m_factories.find(type);
//    if (it == m_factories.end()) {
//        GLIB_FAIL("Unknown activity type " << type);
//    }
//    return it->second(table);
//}
