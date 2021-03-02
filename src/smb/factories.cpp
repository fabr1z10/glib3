#include "factories.h"

#include <monkey/scenefactory.h>
#include <monkey/components/stateactions.h>
#include "states/jumpattack.h"

//#include "states/platformerstate.h"
#include "states/walkside.h"
#include "states/foewalk.h"
#include "states/foechase.h"
#include "states/foedead.h"
#include "states/koopashell.h"

//#include <platformer/states/walk4way.h>
//#include <platformer/states/walk3d.h>
//#include <platformer/states/walkside.h>
//#include <platformer/states/hit.h>
//#include <platformer/states/playanim.h>
//#include <platformer/states/hitjump.h>
#include "states/jump2d.h"
#include "states/ishit.h"
#include "states/bounce.h"
#include "states/keymove.h"
#include "states/keymovef.h"
#include "states/walkside3d.h"
//#include <platformer/states/jump3d.h>
//#include <platformer/states/ch1.h>
//#include <platformer/states/duck.h>
//#include <platformer/states/enemy25.h>
//
//#include <platformer/states/nilstate.h>
//#include <platformer/activities/dropcharacters.h>
//#include <monkey/lua/luatable.h>

//#include <platformer/input/enemyinput.h>
//#include <platformer/input/basicenemyinput.h>
//#include <platformer/input/enemy3d.h>
//#include <monkey/engine.h>
//#include <platformer/activities/setenemydir.h>


void Extension::extend(SceneFactory* f) {
    std::cout << "smb extension\n";
//
    f->add2<WalkSide> ("state.walkside");
	f->add2<WalkSide3D> ("state.walkside3d");
    f->add2<Jump2D> ("state.jump");
    f->add2<FoeWalk> ("state.foewalk");
    f->add2<FoeChase> ("state.foechase");
    f->add2<IsHit> ("state.hit");
	f->add2<JAttack> ("state.jattack");
    f->add2<FoeDead> ("state.foedead");
    f->add2<KoopaShell> ("state.koopashell");
    f->add2<Bounce>("state.bounce");
    f->add2<KeyMove>("state.keymove");
	f->add2<KeyMoveF>("state.keymovef");
    //f->addStateFactory("walkside", std::make_unique<WalkSideFactory>());
//    f->addStateFactory("jump", std::make_unique<Jump2DFactory>());
//
//    f->addStateFactory("foewalk", std::make_unique<FoeWalkFactory>());
//    f->addStateFactory("foedead", std::make_unique<FoeDeadFactory>());
//    f->addStateFactory("koopashell", std::make_unique<KoopaShellFactory>());

}


////
////std::unique_ptr<StateBehaviour> Idle2DStateFactory::Create(luabridge::LuaRef & r) {
////    LuaTable table(r);
////    float acc = table.Get<float>("acceleration");
////    return std::unique_ptr<Idle2D>(new Idle2D(acc));
////}
////
////std::unique_ptr<StateBehaviour> Walk2DStateFactory::Create(luabridge::LuaRef & r) {
////    LuaTable table(r);
////    float acc = table.Get<float>("acceleration");
////    float speed = table.Get<float>("speed");
////    return std::unique_ptr<Walk2D>(new Walk2D(acc, speed));
////}
////
////std::unique_ptr<StateBehaviour> Jump2DStateFactory::Create(luabridge::LuaRef & r) {
////    LuaTable table(r);
////    float acc = table.Get<float>("acceleration");
////    float speed = table.Get<float>("speed");
////    std::string animDown = table.Get<std::string>("animdown", "");
////    return std::unique_ptr<Jump2D>(new Jump2D(acc, speed, !animDown.empty(), animDown));
////}
////
////std::unique_ptr<StateBehaviour> EnemyWalk2DStateFactory::Create(luabridge::LuaRef & r) {
////    LuaTable table(r);
////    float speed = table.Get<float>("speed");
////    int dir = table.Get<int>("dir", 1);
////    bool enableFlip = table.Get<bool>("flip");
////    bool flipWhenPlatformEnds = table.Get<bool>("flip_when_platform_ends", false);
////    return std::unique_ptr<EnemyWalk2D>(new EnemyWalk2D(speed, dir, enableFlip, flipWhenPlatformEnds));
////}
////
////std::unique_ptr<StateBehaviour> EnemyBounce2DStateFactory::Create(luabridge::LuaRef & r) {
////    LuaTable table(r);
////    float speed = table.Get<float>("speed");
////    float vy = table.Get<float>("vy");
////    bool enableFlip = table.Get<bool>("flip");
////    return std::unique_ptr<EnemyBounce2D>(new EnemyBounce2D(speed, vy, enableFlip));
////}
//
//std::shared_ptr<Component> BasicEnemyInputCompFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    int status = table.Get<bool>("status", true);
//    bool flipIfPlatformEnds = table.Get<bool>("flip", true);
//    return std::make_shared<BasicEnemyInputMethod>(status, flipIfPlatformEnds);
//}
//
//std::shared_ptr<Component> EnemyInputCompFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    int status = table.Get<bool>("status", true);
//    bool flipIfPlatformEnds = table.Get<bool>("flip", true);
//    float attackProb = table.Get<float>("attack_prob", 0.0f);
//    glm::vec2 tp = table.Get<glm::vec2>("trans_probs", glm::vec2(0.0f));
//    float turnProb = table.Get<float>("turn_prob", 0.0f);
//
//    auto eim = std::make_shared<EnemyInputMethod>(status, flipIfPlatformEnds, attackProb);
//    table.ProcessVector("attack_moves", [eim] (luabridge::LuaRef ref) {
//        int key = ref["key"].cast<int>();
//        int odds = ref["odds"].cast<int>();
//        eim->AddAttackMove(key, odds);
//    });
//    eim->setTransitionProbabilities(tp[0], tp[1]);
//    eim->setTurnProbability(turnProb);
//    return eim;
//
//}
//
//
//
//std::shared_ptr<Component> Enemy3DInputCompFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    bool left = table.Get<bool>("left", true);
//    bool flipIfPlatformEnds = table.Get<bool>("flip", true);
//    auto eim = std::make_shared<Enemy3DInputMethod>(left, flipIfPlatformEnds);
//    return eim;
//
//}
//
//std::shared_ptr<State> EnemyWalk25StateFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    float speed = table.Get<float>("speed");
//    float acceleration = table.Get<float>("acceleration");
//    float reach = table.Get<float>("reach");
//
//    return std::make_shared<EnemyWalk25>(reach, speed, acceleration, true);
//
//
//}
//
////
////std::shared_ptr<Component> CharacterStateCompFactory::Create(luabridge::LuaRef &ref) {
////    LuaTable table(ref);
////    float speed = table.Get<float>("speed");
////    float accGnd = table.Get<float>("acceleration_ground");
////    float accAir = table.Get<float>("acceleration_air");
////    float jumpHeight = table.Get<float>("jump_velocity");
////    bool canDuck = table.Get<bool>("can_duck");
////    bool flip = table.Get<bool>("flip");
////    luabridge::LuaRef animTable = table.Get<luabridge::LuaRef>("anims");
////    LuaTable at (animTable);
////
////    std::string anim_idle = at.Get<std::string>("idle","");
////    std::string anim_walk = at.Get<std::string>("walk","");
////    std::string anim_turn = at.Get<std::string>("turn","");
////    std::string anim_duck = at.Get<std::string>("duck", "");
////    std::string anim_jump_up = at.Get<std::string>("jump_up","");
////    std::string anim_jump_down = at.Get<std::string>("jump_down","");
////
////
////
////    auto ptr = std::make_shared<CharacterStateMachine>(speed, accGnd, accAir, jumpHeight, canDuck, flip,
////            anim_idle, anim_walk, anim_turn, anim_duck, anim_jump_up, anim_jump_down);
////
////    if (table.HasKey("f")) {
////        ptr->SetRefreshFunc(table.Get<luabridge::LuaRef>("f"));
////    }
////
////    luabridge::LuaRef rColliders = table.Get<luabridge::LuaRef>("colliders");
////    auto factory = Engine::get().GetSceneFactory();
////    for (int i = 0; i < rColliders.length(); ++i) {
////        luabridge::LuaRef rColl = rColliders[i+1];
////        std::string key = rColl["key"].cast<std::string>();
////        luabridge::LuaRef rShape = rColl["value"];
////        std::shared_ptr<Shape> shape = factory->makeShape(rShape);
////        ptr->AddShape(key, shape);
////    }
////    return ptr;
////}
