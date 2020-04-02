#include <monkey/py.h>

namespace py = pybind11;

py::object PyTable::getHandle (const std::string& key) const {
    auto a = obj.attr(key.c_str());
    return a;
}

py::object PyDict::getHandle(const std::string &key) const {
    auto a = obj[key.c_str()];
    return a;
}

//void PyTable::processVector (const std::string& name, std::function<void(const pybind11::handle&)> f) const
//{
//    if (obj.contains(name)) {
//        auto l = obj.attr(name.c_str()).cast<pybind11::list>();
//        for (auto &i : l) {
//            f(i);
//        }
//    }
//}
