#pragma once

#include <monkey/factories.h>

class SceneFactory;

class Extension {
public:
    void extend(SceneFactory*);

};
//FACTORY(Idle2DStateFactory, StateBehaviour)
//FACTORY(Walk2DStateFactory, StateBehaviour)
//FACTORY(Jump2DStateFactory, StateBehaviour)
//FACTORY(EnemyWalk2DStateFactory, StateBehaviour)
//FACTORY(EnemyBounce2DStateFactory, StateBehaviour)

//FACTORY(CharacterStateCompFactory, Component)
//FACTORY(EnemyInputCompFactory, Component)
//FACTORY(BasicEnemyInputCompFactory, Component)
//
//FACTORY(Enemy3DInputCompFactory, Component)
//
//
//FACTORY(DropCharactersActFactory, Activity)
//FACTORY(SetEnemyDirActFactory, Activity)
//// State factories
FACTORY_I(PlatformerStateFactory, State)
//FACTORY(Walk4WayStateFactory, State)
FACTORY_S(WalkSideFactory, PlatformerStateFactory, State)
//FACTORY_S(Walk3DFactory, PlatformerStateFactory, State)
FACTORY_S(Jump2DFactory, PlatformerStateFactory, State)
FACTORY_S(FoeWalkFactory, PlatformerStateFactory, State)
FACTORY_S(FoeDeadFactory, PlatformerStateFactory, State)
FACTORY_S(KoopaShellFactory, PlatformerStateFactory, State)

//FACTORY_S(Jump3DFactory, PlatformerStateFactory, State)
//FACTORY(EnemyWalk25StateFactory, State)
//
//FACTORY(HitFactory, State)
//FACTORY_S(DuckFactory, PlatformerStateFactory, State)
//FACTORY(HitJumpFactory, State)
//FACTORY(NilStateFactory, State)
//FACTORY(CustomHit1StateFactory, State)

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
