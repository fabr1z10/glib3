#include <monkey/factories.h>
#include <monkey/components/walkarea.h>
//#include <monkey/components/scaling.h>
#include <gfx/engine.h>
#include <monkey/activities/walk.h>
#include <monkey/activities/turn.h>
#include <monkey/activities/say.h>
#include <monkey/activities/enableblock.h>
#include <monkey/components/charactercomponent.h>

std::shared_ptr<Component> CharacterStateFactory::Create(luabridge::LuaRef& ref) {
    LuaTable table(ref);
    char dir = table.Get<std::string>("dir")[0];
    float speed = table.Get<float>("speed");
    std::string initialState = table.Get<std::string>("state");
    auto c = Ref::Create<StateCharacter>(speed, dir, initialState);
    return c;
}


// Read the walk-area
std::shared_ptr<Component> WalkAreaComponentFactory::Create(luabridge::LuaRef& ref) {
    LuaTable table(ref);
    int priority = table.Get<int>("priority");
    std::string targetId = table.Get<std::string>("target");
    auto factory = Engine::get().GetSceneFactory();
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    auto shape = factory->makeShape(shapeR);


    auto hotspot = Ref::Create<WalkArea>(shape, priority, targetId);

    if (table.HasKey("depth")) {
        luabridge::LuaRef dref = table.Get<luabridge::LuaRef>("depth");
        auto depthFunc = GetFunc2D(dref);
        hotspot->SetDepthFunction(depthFunc);
    }
    if (table.HasKey("scale")) {
        luabridge::LuaRef dref = table.Get<luabridge::LuaRef>("scale");
        auto scaleFunc = GetFunc2D(dref);
        hotspot->SetScalingFunction(scaleFunc);
    }
    if (table.HasKey("handler")) {
        luabridge::LuaRef dref = table.Get<luabridge::LuaRef>("handler");
        auto f = std::make_shared<LuaFunction>(dref);
        hotspot->SetHandler(f);
    }


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
    //hotspot->SetTag("walkarea");
    return hotspot;
}


std::shared_ptr<Activity> WalkToActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    glm::vec2 pos = table.Get<glm::vec2>("pos");
    if (table.HasKey("id")) {
        int id = table.Get<int>("id");
        return std::make_shared<Walk>(id, pos);
    } else {

        auto tag = table.Get<std::string>("tag");
        return std::make_shared<Walk>(tag, pos);
    }

};

std::shared_ptr<Activity> TurnActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);


    char dir = table.Get<std::string>("dir")[0];

    auto action =  std::make_shared<Turn>(dir);
    setTarget(table, action.get());
    return action;

};


std::shared_ptr<Activity> SayActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);


    std::vector<std::string> lines = table.GetVector<std::string>("lines");
    glm::vec4 color = table.Get<glm::vec4>("color");
    color/=255.0f;
    glm::vec2 offset = table.Get<glm::vec2>("offset");
    std::shared_ptr<Say> say ;
    if (table.HasKey("id")) {
        int id = table.Get<int>("id");
        say = std::make_shared<Say>(id, lines, color, offset);
    } else {
        auto tag = table.Get<std::string>("tag");
        say = std::make_shared<Say>(tag, lines, color, offset);

    }
    bool animate = table.Get<bool>("animate", true);
    if (table.HasKey("animstart")) {
        std::string animStart = table.Get<std::string>("animstart");
        say->SetAnimationStart(animStart);
        //animate = false;
    }
    if (table.HasKey("animend")) {
        std::string animEnd = table.Get<std::string>("animend");
        say->SetAnimationEnd(animEnd);
        //animate = false;
    }

    say->SetNoAnim(!animate);
    return std::move(say);
};


std::shared_ptr<Activity> EnableBlockActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    int wallId = table.Get<int>("wall");
    bool active = table.Get<bool>("active");

    return std::make_shared<EnableBlock>(wallId, active);
};


//
//void ScalingComponentFactory::operator() (luabridge::LuaRef& ref, Entity* parent) {
//    parent->AddComponent(std::make_shared<ScalingDepthComponent>());
//}
