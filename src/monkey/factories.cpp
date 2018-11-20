#include <monkey/factories.h>
#include <monkey/components/walkarea.h>
//#include <monkey/components/scaling.h>
#include <gfx/engine.h>
#include <monkey/activities/walk.h>
#include <monkey/activities/turn.h>
#include <monkey/activities/say.h>
//
// /
// Read the walk-area
std::unique_ptr<Component> WalkAreaComponentFactory::Create(luabridge::LuaRef& ref) {
    LuaTable table(ref);
    int priority = table.Get<int>("priority");
    std::string targetId = table.Get<std::string>("target");
    auto factory = Engine::get().GetSceneFactory();
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    auto shape = factory->GetShared<Shape>(shapeR);
    std::unique_ptr<WalkArea> hotspot (new WalkArea(shape, priority, targetId));
//
//    // see if it has a depthfunc
//    if (table.HasKey("scaling")) {
//        luabridge::LuaRef sref = table.Get<luabridge::LuaRef>("scaling");
//        luabridge::LuaRef depthRef = sref["depth"];
//        auto depthFunc = GetFunc2D(depthRef);
//        hotspot->SetDepthFunction(std::move(depthFunc));
//        luabridge::LuaRef scaleRef = sref["scale"];
//        auto scaleFunc = GetFunc2D(scaleRef);
//        hotspot->SetScalingFunction(std::move(scaleFunc));
//    }
//
    if (table.HasKey("blockedlines")) {
        luabridge::LuaRef ref = table.Get<luabridge::LuaRef>("blockedlines");
        for (int i = 0; i < ref.length(); ++i) {
            luabridge::LuaRef bl = ref[i+1];
            LuaTable t(bl);
            glm::vec2 A = t.Get<glm::vec2>("A");
            glm::vec2 B = t.Get<glm::vec2>("B");
            bool active = t.Get<bool>("active");
            hotspot->AddBlockedLine(A, B, active);
        }
    }
    hotspot->SetTag("walkarea");
    return hotspot;
}


std::unique_ptr<Activity> WalkToActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    std::string actor = table.Get<std::string>("actor");
    glm::vec2 pos = table.Get<glm::vec2>("pos");
    return std::unique_ptr<Walk>(new Walk(actor, pos));
};

std::unique_ptr<Activity> TurnActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    std::string actor = table.Get<std::string>("actor");
    std::string dir = table.Get<std::string>("dir");

    return std::unique_ptr<Turn>(new Turn(actor, dir));
};


std::unique_ptr<Activity> SayActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    std::string actor = table.Get<std::string>("actor");
    std::vector<std::string> lines = table.GetVector<std::string>("lines");
    glm::vec4 color = table.Get<glm::vec4>("color");
    color/=255.0f;
    glm::vec2 offset = table.Get<glm::vec2>("offset");


    return std::unique_ptr<Say>(new Say(actor, lines, color, offset));
};

//
//void ScalingComponentFactory::operator() (luabridge::LuaRef& ref, Entity* parent) {
//    parent->AddComponent(std::make_shared<ScalingDepthComponent>());
//}