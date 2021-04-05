#include <monkey/components/info.h>


LuaInfo::LuaInfo(const ITab &t) : Component(t)
{
    m_stuff = t.get<pybind11::dict>("stuff");
}