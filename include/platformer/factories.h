#pragma once

#include <gfx/factories.h>

FACTORY(Idle2DStateFactory, StateBehaviour)
FACTORY(Walk2DStateFactory, StateBehaviour)
FACTORY(Jump2DStateFactory, StateBehaviour)
FACTORY(EnemyWalk2DStateFactory, StateBehaviour)
FACTORY(EnemyBounce2DStateFactory, StateBehaviour)

FACTORY(DropCharactersActFactory, Activity)


//class Idle2DStateFactory : public FactoryMethod<StateBehaviour> {
//    std::unique_ptr<StateBehaviour> Create(luabridge::LuaRef&) override;
//};
//class Walk2DStateFactory : public FactoryMethod<StateBehaviour> {
//    std::unique_ptr<StateBehaviour> Create(luabridge::LuaRef&) override;
//};
//class Jump2DStateFactory : public FactoryMethod<StateBehaviour> {
//    std::unique_ptr<StateBehaviour> Create(luabridge::LuaRef&) override;
//};
//class EnemyWalk2DStateFactory : public FactoryMethod<StateBehaviour> {
//    std::unique_ptr<StateBehaviour> Create(luabridge::LuaRef&) override;
//};