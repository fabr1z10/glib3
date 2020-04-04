#pragma once

#include <monkey/component.h>
#include <monkey/lua/luawrapper.h>

// stores custom additional information for the entity
class LuaInfo : public Component {
public:
    LuaInfo(luabridge::LuaRef info) {}
    LuaInfo (const LuaTable& t);
    LuaInfo (const ITable& t);
    LuaInfo (const LuaInfo& orig) : Component(orig), m_info(orig.m_info) {}
    void Start() override {}
    void Update(double) override{}
    using ParentClass = LuaInfo;
    const ITable* get2() const {
        return m_info.get();
    }
    std::shared_ptr<Component> clone() const override {
        return std::make_shared<LuaInfo>(LuaInfo(*this));
    }
private:
    //luabridge::LuaRef m_ref;
    std::shared_ptr<ITable> m_info;
};
