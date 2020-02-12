#include "factories.h"

#include <monkey/scenefactory.h>
#include <monkey/components/stateactions.h>

#include "states/platformerstate.h"
#include "states/walkside.h"
#include "states/foewalk.h"
#include "states/foedead.h"
#include "states/koopashell.h"

//#include <platformer/states/walk4way.h>
//#include <platformer/states/walk3d.h>
//#include <platformer/states/walkside.h>
//#include <platformer/states/hit.h>
//#include <platformer/states/playanim.h>
//#include <platformer/states/hitjump.h>
#include "states/jump2d.h"
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
//
//    f->addStateFactory("walkside", std::make_unique<WalkSideFactory>());
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


std::shared_ptr<State> PlatformerStateFactory::Create(luabridge::LuaRef &ref) {
    throw;
}

void PlatformerStateFactory::init(const LuaTable& table, std::shared_ptr<State> state) {
    // need to do this although looks like shit
    auto platformer_state = std::static_pointer_cast<PlatformerState>(state);
    // loop through
    table.ProcessVector("keys", [platformer_state] (luabridge::LuaRef ref) {
        int id = ref["id"].cast<int>();
        std::string action = ref["action"].cast<std::string>();
        if (action == "changestate") {
            std::string nextState = ref["state"].cast<std::string>();
            platformer_state->AddKey(id, std::make_shared<StateTransition>(nextState));
        } else if (action == "callback") {
            luabridge::LuaRef func = ref["func"];
            platformer_state->AddKey(id, std::make_shared<StateCallback>(func));
        }
//        else if (action == "playanim") {
//            std::string anim = ref["anim"].cast<std::string>();
//            platformer_state->AddKey(id, std::make_shared<PlayAnim>(platformer_state.get(), anim));
//
//        }
    });

}
//
//std::shared_ptr<Activity> DropCharactersActFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    auto act = std::make_shared<DropCharacters>();
//    setTarget(table, act.get());
//
//    return act;
//};
//
//std::shared_ptr<Activity> SetEnemyDirActFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    // get id
//    //int id = getId(table);
//    bool left = table.Get<bool>("left");
//    auto act = std::make_shared<SetEnemyDirection>(left);
//    setTarget(table, act.get());
//    return act;
//}
//
//std::shared_ptr<State> Walk4WayStateFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    float speed = table.Get<float>("speed");
//    float a = table.Get<float>("acceleration");
//    bool fliph = table.Get<bool>("fliph");
//    return std::make_shared<Walk4Way>(speed, a, fliph);
//
//
//
//}
//
std::shared_ptr<State> WalkSideFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    float speed = table.Get<float>("speed");
    float a = table.Get<float>("acceleration");
    bool fliph = table.Get<bool>("fliph");
    float jumpSpeed= table.Get<float>("jumpspeed");
    auto state = std::make_shared<WalkSide>(speed, a, fliph, jumpSpeed);

    if (table.HasKey("jump_state")) {
        state->setJumpState(table.Get<std::string>("jump_state"));
    }
    if (table.HasKey("walk_anim")) {
        state->setWalkAnimation(table.Get<std::string>("walk_anim"));
    }
    if (table.HasKey("idle_anim")) {
        state->setIdleAnimation(table.Get<std::string>("idle_anim"));
    }

    init(table, state);
    return state;
}
//
//std::shared_ptr<State> Walk3DFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    float speed = table.Get<float>("speed");
//    float a = table.Get<float>("acceleration");
//    bool fliph = table.Get<bool>("fliph");
//    float jumpSpeed= table.Get<float>("jumpspeed");
//    auto state = std::make_shared<Walk3D>(speed, a, fliph, jumpSpeed);
//    init(table, state);
//    return state;
//}
//
//
//std::shared_ptr<State> DuckFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    float a = table.Get<float>("acceleration");
//    auto state = std::make_shared<Duck>(a);
//    init(table, state);
//    return state;
//}
//void DuckFactory::init(const LuaTable & table, std::shared_ptr<State> state) {
//    PlatformerStateFactory::init(table, state);
//
//}
//
//
void WalkSideFactory::init(const LuaTable & table, std::shared_ptr<State> state) {
    PlatformerStateFactory::init(table, state);

}
//
//void Walk3DFactory::init(const LuaTable & table, std::shared_ptr<State> state) {
//    PlatformerStateFactory::init(table, state);
//
//}
std::shared_ptr<State> Jump2DFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    float speed = table.Get<float>("speed");
    float a = table.Get<float>("acceleration");
    bool fliph = table.Get<bool>("fliph");
    //float jumpSpeed= table.Get<float>("jumpspeed");
    std::string animUp = table.Get<std::string>("animup");
    std::string animDown = table.Get<std::string>("animdown");
    bool bounce = table.Get<bool>("bounce", false);
    float bounceFactor = table.Get<float>("bouncefactor", 0.0f);
    auto ptr = std::make_shared<Jump2D>(a, speed, fliph, animUp, animDown, bounce, bounceFactor);
    if (table.HasKey("walk_state")) {
        ptr->setWalkState(table.Get<std::string>("walk_state"));
    }
    init(table, ptr);
    return ptr;



}
//
//std::shared_ptr<State> Jump3DFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    float speed = table.Get<float>("speed");
//    float a = table.Get<float>("acceleration");
//    bool fliph = table.Get<bool>("fliph");
//    //float jumpSpeed= table.Get<float>("jumpspeed");
//    std::string animUp = table.Get<std::string>("animup");
//    std::string animDown = table.Get<std::string>("animdown");
//    bool bounce = table.Get<bool>("bounce", false);
//    float bounceFactor = table.Get<float>("bouncefactor", 0.0f);
//    auto ptr = std::make_shared<Jump3D>(a, speed, fliph, animUp, animDown, bounce, bounceFactor);
//    init(table, ptr);
//    return ptr;
//
//
//
//}
void Jump2DFactory::init(const LuaTable & table, std::shared_ptr<State> state) {
    PlatformerStateFactory::init(table, state);

}
//void Jump3DFactory::init(const LuaTable & table, std::shared_ptr<State> state) {
//    PlatformerStateFactory::init(table, state);
//
//}
//std::shared_ptr<State> HitFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    std::string anim = table.Get<std::string>("anim");
//    float acc = table.Get<float>("acceleration");
//    return std::make_shared<Hit>(anim, acc);
//}
//std::shared_ptr<State> HitJumpFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    std::string anim = table.Get<std::string>("anim");
//    float acc = table.Get<float>("acceleration");
//    float speed = table.Get<float>("speed");
//    return std::make_shared<HitJump>(anim, speed, acc);
//}
////std::shared_ptr<State> HitJumpFactory::Create(luabridge::LuaRef &ref) {
////    LuaTable table(ref);
////    std::string anim = table.Get<std::string>("anim");
////    int frame = table.Get<int>("frame");
////    auto shape = table.Get<std::shared_ptr<Shape>>("shape");
////    int mask = table.Get<int>("mask");
////    int tag = table.Get<int>("tag");
////
////    float acc = table.Get<float>("acceleration");
////    float speed = table.Get<float>("speed");
////    return std::make_shared<HitJump>(anim, frame, shape, mask, tag, acc, speed);
////}
////
//std::shared_ptr<State> CustomHit1StateFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    std::string target = table.Get<std::string>("target");
//    std::string animUp = table.Get<std::string>("animup");
//    std::string animDown = table.Get<std::string>("animdown");
//    float speed = table.Get<float>("speed");
//    return std::make_shared<CustomHit1>(target, speed, speed, animUp, animDown);
//}
//
////std::shared_ptr<State> HitJumpFactory::Create(luabridge::LuaRef &ref) {
////    LuaTable table(ref);
////    std::string anim = table.Get<std::string>("anim");
////    int frame = table.Get<int>("frame");
////    auto shape = table.Get<std::shared_ptr<Shape>>("shape");
////    return std::make_shared<HitJump>(anim, frame, shape);
////
////
////
////}
//
//std::shared_ptr<State> NilStateFactory::Create(luabridge::LuaRef& ) {
//    return std::make_shared<NilState>();
//}
std::shared_ptr<State> FoeWalkFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string anim = table.Get<std::string>("anim");
    float speed = table.Get<float>("speed");
    float a = table.Get<float>("acceleration");
    bool fliph = table.Get<bool>("fliph");
    bool flipp = table.Get<bool>("flip_platform");

    int left = table.Get<int>("left");
    auto ptr = std::make_shared<FoeWalk>(anim, speed,a,fliph, flipp, left);
    init(table, ptr);
    return ptr;
}

void FoeWalkFactory::init(const LuaTable & table, std::shared_ptr<State> state) {
    PlatformerStateFactory::init(table, state);

}

std::shared_ptr<State> FoeDeadFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    float time = table.Get<float>("time");

    auto ptr = std::make_shared<FoeDead>(time);
    init(table, ptr);
    return ptr;
}

void FoeDeadFactory::init(const LuaTable & table, std::shared_ptr<State> state) {
    PlatformerStateFactory::init(table, state);

}

std::shared_ptr<State> KoopaShellFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    float time = table.Get<float>("time");
    float time_walk = table.Get<float>("time_walk");

    auto ptr = std::make_shared<KoopaShell>(time, time_walk);
    init(table, ptr);
    return ptr;
}

void KoopaShellFactory::init(const LuaTable & table, std::shared_ptr<State> state) {
    PlatformerStateFactory::init(table, state);

}