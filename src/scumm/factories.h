#pragma once

#include <monkey/factories.h>

class SceneFactory;

class Extension {
public:
	void extend(SceneFactory*);

};

// components
FACTORY(WalkAreaComponentFactory, Component)
//FACTORY(WalkStopComponentFactory, Component)
FACTORY(CharacterComponentFactory, Component)
//

// activities
FACTORY(WalkToActFactory, Activity)
FACTORY(TurnActFactory, Activity)
FACTORY(SayActFactory, Activity)
FACTORY(EnableBlockActFactory, Activity)

//FACTORY(TurnSciActFactory, Activity)



//
//
//class WalkAreaComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};
//
//class ScalingComponentFactory : public ComponentFactory {
//    void operator()(luabridge::LuaRef&, Entity*) override;
//};
