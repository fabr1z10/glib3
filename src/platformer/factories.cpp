#include <platformer/factories.h>
#include <platformer/states/idle2d.h>
#include <platformer/states/walk2d.h>
#include <platformer/states/enemywalk2d.h>
#include <platformer/states/jump2d.h>
#include <gfx/lua/luatable.h>

std::shared_ptr<StateBehaviour> Idle2DStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    float acc = table.Get<float>("acceleration");
    return std::make_shared<Idle2D>(acc);
}

std::shared_ptr<StateBehaviour> Walk2DStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    float acc = table.Get<float>("acceleration");
    float speed = table.Get<float>("speed");
    return std::make_shared<Walk2D>(acc, speed);
}

std::shared_ptr<StateBehaviour> Jump2DStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    float acc = table.Get<float>("acceleration");
    float speed = table.Get<float>("speed");
    return std::make_shared<Jump2D>(acc, speed);
}

std::shared_ptr<StateBehaviour> EnemyWalk2DStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    float speed = table.Get<float>("speed");
    int dir = table.Get<int>("dir", 1);
    bool enableFlip = table.Get<bool>("flip");
    return std::make_shared<EnemyWalk2D>(speed, dir, enableFlip);
}
