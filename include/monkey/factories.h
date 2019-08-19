#pragma once

#include <gfx/factories.h>


FACTORY(WalkAreaComponentFactory, Component)
FACTORY(CharacterStateFactory, Component)

FACTORY(WalkToActFactory, Activity)
FACTORY(WalkSciActFactory, Activity)
FACTORY(TurnActFactory, Activity)
FACTORY(TurnSciActFactory, Activity)
FACTORY(SayActFactory, Activity)
FACTORY(EnableBlockActFactory, Activity)



//
//
//class WalkAreaComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};
//
//class ScalingComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};
