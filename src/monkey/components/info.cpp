#include <monkey/components/info.h>


LuaInfo::LuaInfo(const ITable &t) : Component(t)
{
    m_stuff = t.get<pybind11::dict>("stuff");
}