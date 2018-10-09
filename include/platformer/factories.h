#pragma once

#include <gfx/factories.h>

class Idle2DStateFactory : public FactoryMethod<StateBehaviour> {
    std::shared_ptr<StateBehaviour> Create(luabridge::LuaRef&) override;
};
class Walk2DStateFactory : public FactoryMethod<StateBehaviour> {
    std::shared_ptr<StateBehaviour> Create(luabridge::LuaRef&) override;
};
class Jump2DStateFactory : public FactoryMethod<StateBehaviour> {
    std::shared_ptr<StateBehaviour> Create(luabridge::LuaRef&) override;
};
class EnemyWalk2DStateFactory : public FactoryMethod<StateBehaviour> {
    std::shared_ptr<StateBehaviour> Create(luabridge::LuaRef&) override;
};