#pragma once

#include <gfx/singleton.h>
#include <unordered_map>
#include <functional>
#include <gfx/activity.h>
#include <gfx/lua/luatable.h>
#include <gfx/factories.h>

class BasicActivityFactory : public ActivityFactory {
public:
    BasicActivityFactory ();
    // can I make it const LuaTable& ?
    std::unique_ptr<Activity> createActivity(LuaTable& t) override;
private:
    std::unordered_map<std::string, std::function<std::unique_ptr<Activity>(LuaTable&)>> m_factories;
};