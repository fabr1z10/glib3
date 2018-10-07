#pragma once

#include <gfx/entity.h>
#include <memory>

class Activity;
class LuaTable;

class SceneFactory {
public:
    virtual ~SceneFactory() {}
    virtual std::shared_ptr<Entity> Create() = 0;
    virtual void CleanUp () = 0;
    virtual void PostInit() {}
};

class ActivityFactory {
public:
    virtual ~ActivityFactory () {}
    // can I make it const LuaTable& ?
    virtual std::unique_ptr<Activity> createActivity(LuaTable& t) = 0;
};