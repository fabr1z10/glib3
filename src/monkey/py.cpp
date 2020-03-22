#include <monkey/py.h>

void PyTable::processVector (const std::string& name, std::function<void(const pybind11::handle&)> f) const
{
    if (obj.contains(name)) {
        auto l = obj.attr(name.c_str()).cast<pybind11::list>();
        for (auto &i : l) {
            f(i);
        }
    }
}
