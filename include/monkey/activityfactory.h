#pragma once

#include <gfx/singleton.h>
#include <unordered_map>
#include <functional>
#include <gfx/activity.h>
#include <monkey/luatable.h>

class ActivityFactory : public Singleton<ActivityFactory>
{
public:
    // can I make it const LuaTable& ?
    std::unique_ptr<Activity> createActivity(LuaTable& t);
private:

    friend class Singleton<ActivityFactory>;
    ActivityFactory() ;
    std::unordered_map<std::string, std::function<std::unique_ptr<Activity>(LuaTable&)>> m_factories;
};