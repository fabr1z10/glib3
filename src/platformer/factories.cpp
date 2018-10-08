#include <platformer/factories.h>
#include <platformer/states/idle2d.h>
#include <platformer/states/walk2d.h>
#include <platformer/states/enemywalk2d.h>
#include <platformer/states/jump2d.h>
#include <gfx/lua/luatable.h>

std::shared_ptr<State> Idle2DStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    std::string anim = table.Get<std::string>("anim");
    float acc = table.Get<float>("acceleration");
    return std::make_shared<Idle2D>(anim, acc);
}

std::shared_ptr<State> Walk2DStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    std::string anim = table.Get<std::string>("anim");
    float acc = table.Get<float>("acceleration");
    //float g = table.Get<float>("gravity");
    float speed = table.Get<float>("speed");
    return std::make_shared<Walk2D>(anim, acc, speed);
}

std::shared_ptr<State> Jump2DStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    std::string anim = table.Get<std::string>("anim");
    float acc = table.Get<float>("acceleration");
    //float g = table.Get<float>("gravity");
    float speed = table.Get<float>("speed");
    return std::make_shared<Jump2D>(anim, acc, speed);
}

std::shared_ptr<State> EnemyWalk2DStateFactory::Create(luabridge::LuaRef & r) {
    LuaTable table(r);
    std::string anim = table.Get<std::string>("anim");
    float speed = table.Get<float>("speed");
    int dir = table.Get<int>("dir", 1);
    bool enableFlip = table.Get<bool>("flip");
    return std::make_shared<EnemyWalk2D>(anim, speed, dir, enableFlip);
}
