#pragma once

#include <gfx/component.h>
#include <monkey/luawrapper.h>


class LuaInfo : public Component {
public:
    LuaInfo(luabridge::LuaRef info) : m_ref(info) {}
    void Start() override {}
    void Update(double) override{}
    using ParentClass = LuaInfo;
    luabridge::LuaRef get() {
        return m_ref;
    }
private:
    luabridge::LuaRef m_ref;
};