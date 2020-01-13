#pragma once

#include <functional>
#include <monkey/component.h>
#include <monkey/lua/luawrapper.h>

// hooks C++ function to LUA
class LuaHook : public Component {
public:
    LuaHook();
    LuaHook(const LuaHook&);
    std::shared_ptr<Component> clone() const override;
    void addHook (const std::string&, std::function<void(luabridge::LuaRef)> );
    void call(const std::string&, luabridge::LuaRef args);
    void Start() {}
    void Update(double dt) {}
    using ParentClass = LuaHook;

private:
    std::unordered_map<std::string, std::function<void(luabridge::LuaRef)> > m_callbacks;
};