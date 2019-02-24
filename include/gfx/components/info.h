#pragma once

#include <gfx/component.h>
#include <gfx/lua/luawrapper.h>


class LuaInfo : public Component {
public:
    LuaInfo(luabridge::LuaRef info) : m_ref(info) {}
    LuaInfo (const LuaInfo& orig) : Component(orig), m_ref(orig.m_ref) {}
    void Start() override {}
    void Update(double) override{}
    using ParentClass = LuaInfo;
    luabridge::LuaRef get() {
        return m_ref;
    }
    std::shared_ptr<Component> clone() const override {
        return std::make_shared<LuaInfo>(LuaInfo(*this));
    }
private:
    luabridge::LuaRef m_ref;
};
