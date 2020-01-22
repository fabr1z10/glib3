#include "factories.h"
//
#include "components/walkarea.h"
#include "components/character.h"
//
#include "activities/turn.h"
#include "activities/walk.h"
#include "activities/say.h"
#include "activities/enableblock.h"

#include <monkey/scenefactory.h>
#include <monkey/engine.h>

extern "C" void hello(SceneFactory* f) {

    f->addComponentFactory("walkarea", std::make_unique<WalkAreaComponentFactory>());
    f->addComponentFactory("character", std::make_unique<CharacterComponentFactory>());

    f->addActivityFactory("walk", std::make_unique<WalkToActFactory>());
    f->addActivityFactory("turn", std::make_unique<TurnActFactory>());
    f->addActivityFactory("say", std::make_unique<SayActFactory>());
    f->addActivityFactory("enable_wall", std::make_unique<EnableBlockActFactory>());
}

std::shared_ptr<Component> CharacterComponentFactory::Create(luabridge::LuaRef& ref) {
    LuaTable table(ref);
    char dir = table.Get<std::string>("dir")[0];
    float speed = table.Get<float>("speed");
    std::string initialState = table.Get<std::string>("state");
    auto c = std::make_shared<StateCharacter>(speed, dir, initialState);
    return c;
}

// Read the walk-area
std::shared_ptr<Component> WalkAreaComponentFactory::Create(luabridge::LuaRef& ref) {

    LuaTable table(ref);
    int priority = table.Get<int>("priority");
    auto factory = Engine::get().GetSceneFactory();
    luabridge::LuaRef rshape = table.Get<luabridge::LuaRef>("shape");
    auto shape = factory->makeShape(rshape);
    std::shared_ptr<WalkArea> hotspot = std::make_shared<WalkArea>(shape, priority);

    if (table.HasKey("onenter")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onenter");
        hotspot->SetOnEnter(r);
    }

    if (table.HasKey("onleave")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onleave");
        hotspot->SetOnLeave(r);
    }

    if (table.HasKey("onclick")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onclick");
        std::unique_ptr<LuaFunction> f(new LuaFunction(r));
        hotspot->SetOnClick(std::move(f));
    }

    if (table.HasKey("onrmbclick")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onrmbclick");
        std::unique_ptr<LuaFunction> f(new LuaFunction(r));
        hotspot->SetOnRightMouseButtonClick(std::move(f));
    }
    if (table.HasKey("onmove")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onmove");
        hotspot->SetOnMove(r);
    }
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
    std::string id = table.Get<std::string>("walkarea");
    int wallId = table.Get<int>("wall");
    bool active = table.Get<bool>("active");

    return std::make_shared<EnableBlock>(id, wallId, active);
};

