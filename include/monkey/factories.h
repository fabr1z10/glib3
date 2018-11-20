#pragma once

#include <gfx/factories.h>


FACTORY(WalkAreaComponentFactory, Component)

FACTORY(WalkToActFactory, Activity)
FACTORY(TurnActFactory, Activity)
FACTORY(SayActFactory, Activity)
//
//
//class WalkAreaComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};
//
//class ScalingComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};