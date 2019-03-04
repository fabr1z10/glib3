#include <platformer/factories.h>
#include <platformer/states/idle2d.h>
#include <platformer/states/walk2d.h>
#include <platformer/states/enemywalk2d.h>
#include <platformer/states/enemybounce2d.h>
#include <platformer/states/jump2d.h>
#include <platformer/activities/dropcharacters.h>
#include <gfx/lua/luatable.h>
#include <platformer/characterstatemachine.h>
#include <gfx/engine.h>
//
//std::unique_ptr<StateBehaviour> Idle2DStateFactory::Create(luabridge::LuaRef & r) {
//    LuaTable table(r);
//    float acc = table.Get<float>("acceleration");
//    return std::unique_ptr<Idle2D>(new Idle2D(acc));
//}
//
//std::unique_ptr<StateBehaviour> Walk2DStateFactory::Create(luabridge::LuaRef & r) {
//    LuaTable table(r);
//    float acc = table.Get<float>("acceleration");
//    float speed = table.Get<float>("speed");
//    return std::unique_ptr<Walk2D>(new Walk2D(acc, speed));
//}
//
//std::unique_ptr<StateBehaviour> Jump2DStateFactory::Create(luabridge::LuaRef & r) {
//    LuaTable table(r);
//    float acc = table.Get<float>("acceleration");
//    float speed = table.Get<float>("speed");
//    std::string animDown = table.Get<std::string>("animdown", "");
//    return std::unique_ptr<Jump2D>(new Jump2D(acc, speed, !animDown.empty(), animDown));
//}
//
//std::unique_ptr<StateBehaviour> EnemyWalk2DStateFactory::Create(luabridge::LuaRef & r) {
//    LuaTable table(r);
//    float speed = table.Get<float>("speed");
//    int dir = table.Get<int>("dir", 1);
//    bool enableFlip = table.Get<bool>("flip");
//    bool flipWhenPlatformEnds = table.Get<bool>("flip_when_platform_ends", false);
//    return std::unique_ptr<EnemyWalk2D>(new EnemyWalk2D(speed, dir, enableFlip, flipWhenPlatformEnds));
//}
//
//std::unique_ptr<StateBehaviour> EnemyBounce2DStateFactory::Create(luabridge::LuaRef & r) {
//    LuaTable table(r);
//    float speed = table.Get<float>("speed");
//    float vy = table.Get<float>("vy");
//    bool enableFlip = table.Get<bool>("flip");
//    return std::unique_ptr<EnemyBounce2D>(new EnemyBounce2D(speed, vy, enableFlip));
//}

std::unique_ptr<Component> CharacterStateCompFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    float speed = table.Get<float>("speed");
    float accGnd = table.Get<float>("acceleration_ground");
    float accAir = table.Get<float>("acceleration_air");
    float jumpHeight = table.Get<float>("jump_velocity");
    bool canDuck = table.Get<bool>("can_duck");
    luabridge::LuaRef animTable = table.Get<luabridge::LuaRef>("anims");
    LuaTable at (animTable);

    std::string anim_idle = at.Get<std::string>("idle","");
    std::string anim_walk = at.Get<std::string>("walk","");
    std::string anim_turn = at.Get<std::string>("turn","");
    std::string anim_duck = at.Get<std::string>("duck", "");
    std::string anim_jump_up = at.Get<std::string>("jump_up","");
    std::string anim_jump_down = at.Get<std::string>("jump_down","");



    auto ptr = std::unique_ptr<CharacterStateMachine>(
            new CharacterStateMachine(speed, accGnd, accAir, jumpHeight, canDuck,
            anim_idle, anim_walk, anim_turn, anim_duck, anim_jump_up, anim_jump_down));

    if (table.HasKey("f")) {
        ptr->SetRefreshFunc(table.Get<luabridge::LuaRef>("f"));
    }

    luabridge::LuaRef rColliders = table.Get<luabridge::LuaRef>("colliders");
    auto factory = Engine::get().GetSceneFactory();
    for (int i = 0; i < rColliders.length(); ++i) {
        luabridge::LuaRef rColl = rColliders[i+1];
        std::string key = rColl["key"].cast<std::string>();
        luabridge::LuaRef rShape = rColl["value"];
        std::shared_ptr<Shape> shape (factory->Get<Shape>(rShape));
        ptr->AddShape(key, shape);
    }
    return ptr;
}

std::unique_ptr<Activity> DropCharactersActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string actor = table.Get<std::string>("actor");
    glm::vec2 targetPos = table.Get<glm::vec2>("pos");
    return std::unique_ptr<DropCharacters>(new DropCharacters(actor, targetPos));
};
