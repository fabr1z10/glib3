#include <platformer/factories.h>
#include <platformer/states/idle2d.h>
#include <platformer/states/walk2d.h>
#include <platformer/states/enemywalk2d.h>
#include <platformer/states/enemybounce2d.h>
#include <platformer/states/jump2d.h>
#include <platformer/activities/dropcharacters.h>
#include <gfx/lua/luatable.h>
#include <platformer/characterstatemachine.h>
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
    float jumpHeight = table.Get<float>("jump_height");
    float timeApex = table.Get<float>("time_jump_apex");


    auto ptr = std::unique_ptr<CharacterStateMachine>(
            new CharacterStateMachine(speed, accGnd, accAir, jumpHeight, timeApex));

    if (table.HasKey("addinfo")) {
        ptr->SetAdditionalState(table.Get<luabridge::LuaRef>("addinfo"));
    }
    if (table.HasKey("f")) {
        ptr->SetAnimFunc(table.Get<luabridge::LuaRef>("f"));
    }
    return ptr;
}

std::unique_ptr<Activity> DropCharactersActFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string actor = table.Get<std::string>("actor");
    glm::vec2 targetPos = table.Get<glm::vec2>("pos");
    return std::unique_ptr<DropCharacters>(new DropCharacters(actor, targetPos));
};
