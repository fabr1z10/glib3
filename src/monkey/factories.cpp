#include <monkey/factories.h>
#include <monkey/components/walkarea.h>
//#include <monkey/components/scaling.h>
#include <gfx/engine.h>
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
//
//void ScalingComponentFactory::operator() (luabridge::LuaRef& ref, Entity* parent) {
//    parent->AddComponent(std::make_shared<ScalingDepthComponent>());
//}