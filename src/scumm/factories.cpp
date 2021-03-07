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

void Extension::extend(SceneFactory* f) {

    f->add2<WalkArea> ("scumm.components.walkarea");
    f->add2<CharacterController> ("scumm.components.character_controller");

    f->add2<StateCharacter> ("components.character");
//
    f->add2<Walk> ("scumm.action.walk");

    f->add2<Turn> ("scumm.action.turn");
    f->add2<Say> ("scumm.action.say");
    f->add2<EnableBlock> ("scumm.action.enable_block");
    //f->add<EnableBlock> ("enable_wall");

    //LuaWrapper::addMethod("get_direction", [&] (EntityWrapper* e) { return getDirection(e); });

//    f->addActivityFactory("walk", std::make_unique<WalkToActFactory>());
//    f->addActivityFactory("turn", std::make_unique<TurnActFactory>());
//    f->addActivityFactory("say", std::make_unique<SayActFactory>());
//    f->addActivityFactory("enable_wall", std::make_unique<EnableBlockActFactory>());
}




//std::shared_ptr<Activity> WalkToActFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//
//    glm::vec2 pos = table.Get<glm::vec2>("pos");
//    if (table.HasKey("id")) {
//        int id = table.Get<int>("id");
//        return std::make_shared<Walk>(id, pos);
//    } else {
//
//        auto tag = table.Get<std::string>("tag");
//        return std::make_shared<Walk>(tag, pos);
//    }
//
//};

//std::shared_ptr<Activity> TurnActFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//
//
//    char dir = table.Get<std::string>("dir")[0];
//
//    auto action =  std::make_shared<Turn>(dir);
//    setTarget(table, action.get());
//    return action;
//
//};
//
//std::shared_ptr<Activity> SayActFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//
//
//    std::vector<std::string> lines = table.GetVector<std::string>("lines");
//    glm::vec4 color = table.Get<glm::vec4>("color");
//    color/=255.0f;
//    glm::vec2 offset = table.Get<glm::vec2>("offset");
//    std::shared_ptr<Say> say ;
//    if (table.HasKey("id")) {
//        int id = table.Get<int>("id");
//        say = std::make_shared<Say>(id, lines, color, offset);
//    } else {
//        auto tag = table.Get<std::string>("tag");
//        say = std::make_shared<Say>(tag, lines, color, offset);
//
//    }
//    bool animate = table.Get<bool>("animate", true);
//    if (table.HasKey("animstart")) {
//        std::string animStart = table.Get<std::string>("animstart");
//        say->SetAnimationStart(animStart);
//        //animate = false;
//    }
//    if (table.HasKey("animend")) {
//        std::string animEnd = table.Get<std::string>("animend");
//        say->SetAnimationEnd(animEnd);
//        //animate = false;
//    }
//
//    say->SetNoAnim(!animate);
//    return std::move(say);
////};
////
//
//std::shared_ptr<Activity> EnableBlockActFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    std::string id = table.Get<std::string>("walkarea");
//    int wallId = table.Get<int>("wall");
//    bool active = table.Get<bool>("active");
//
//    return std::make_shared<EnableBlock>(id, wallId, active);
//};
//
