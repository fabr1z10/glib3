#include <monkey/components/info.h>
#include <monkey/lua/luatable.h>

LuaInfo::LuaInfo(const LuaTable &t) : Component(t) {

}

LuaInfo::LuaInfo(const ITable &t) : Component(t)
{
    m_stuff = t.get<pybind11::dict>("stuff");
    //m_info = t.clone();
    //glm::vec4 pippo = t.get<glm::vec4>("text_color");

}