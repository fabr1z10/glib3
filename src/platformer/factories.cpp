#include <platformer/factories.h>
#include <platformer/states/idle2d.h>
#include <platformer/states/walk2d.h>
#include <platformer/states/enemywalk2d.h>
#include <platformer/states/enemybounce2d.h>
#include <platformer/states/jump2d.h>
#include <gfx/lua/luatable.h>

std::unique_ptr<StateBehaviour> Idle2DStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    float acc = table.Get<float>("acceleration");
    return std::unique_ptr<Idle2D>(new Idle2D(acc));
}

std::unique_ptr<StateBehaviour> Walk2DStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    float acc = table.Get<float>("acceleration");
    float speed = table.Get<float>("speed");
    return std::unique_ptr<Walk2D>(new Walk2D(acc, speed));
}

std::unique_ptr<StateBehaviour> Jump2DStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    float acc = table.Get<float>("acceleration");
    float speed = table.Get<float>("speed");
    return std::unique_ptr<Jump2D>(new Jump2D(acc, speed));
}

std::unique_ptr<StateBehaviour> EnemyWalk2DStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    float speed = table.Get<float>("speed");
    int dir = table.Get<int>("dir", 1);
    bool enableFlip = table.Get<bool>("flip");
    bool flipWhenPlatformEnds = table.Get<bool>("flip_when_platform_ends", false);
    return std::unique_ptr<EnemyWalk2D>(new EnemyWalk2D(speed, dir, enableFlip, flipWhenPlatformEnds));
}

std::unique_ptr<StateBehaviour> EnemyBounce2DStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    float speed = table.Get<float>("speed");
    float vy = table.Get<float>("vy");
    bool enableFlip = table.Get<bool>("flip");
    return std::unique_ptr<EnemyBounce2D>(new EnemyBounce2D(speed, vy, enableFlip));
}
