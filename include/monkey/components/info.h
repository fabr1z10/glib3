#pragma once

#include <monkey/component.h>
#include <monkey/py.h>

// stores custom additional information for the entity
class LuaInfo : public Component {
public:
    LuaInfo (const ITab& t);
    void Start() override {}
    void Update(double) override{}
    using ParentClass = LuaInfo;
    PyDict get2() const {
        return PyDict(m_stuff);
    }
    pybind11::dict& getStuff() {
        return m_stuff;
    }
private:
    //luabridge::LuaRef m_ref;
    pybind11::dict m_stuff;
    //std::shared_ptr<ITable> m_info;
};
