#pragma once

#include <gfx/entity.h>
#include <memory>
#include <gfx/lua/luawrapper.h>

class Activity;
class LuaTable;




class SceneFactory {
public:
    virtual ~SceneFactory() {}
    virtual std::shared_ptr<Entity> Create() = 0;
    virtual void CleanUp () = 0;
    virtual void PostInit() {}
    virtual std::shared_ptr<Entity> ReadItem(luabridge::LuaRef& ref) = 0;
};

class ActivityFactory {
public:
    virtual ~ActivityFactory () {}
    // can I make it const LuaTable& ?
    virtual std::unique_ptr<Activity> createActivity(LuaTable& t) = 0;
};