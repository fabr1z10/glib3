#pragma once

#include <monkey/component.h>
#include <monkey/lua/luawrapper.h>

// stores custom additional information for the entity
class LuaInfo : public Component {
public:
    LuaInfo(luabridge::LuaRef info) {}
    LuaInfo (const LuaTable& t);
    LuaInfo (const ITable& t);
    LuaInfo (const LuaInfo& orig) : Component(orig), m_stuff(pybind11::none()) {}
    void Start() override {}
    void Update(double) override{}
    using ParentClass = LuaInfo;
    PyDict get2() const {
        return PyDict(m_stuff);
    }
    std::shared_ptr<Component> clone() const override {
        return std::make_shared<LuaInfo>(LuaInfo(*this));
    }
    pybind11::dict& getStuff() {
        return m_stuff;
    }
private:
    //luabridge::LuaRef m_ref;
    pybind11::dict m_stuff;
    //std::shared_ptr<ITable> m_info;
};
