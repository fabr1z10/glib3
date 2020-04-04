#include <monkey/py.h>

namespace py = pybind11;

PyTable::PyTable(const PyTable & other) : obj(other.obj) {

}

PyDict::PyDict(const PyDict & other) : obj(other.obj) {

}

std::shared_ptr<ITable> PyTable::clone() const {
    return std::make_shared<PyTable>(*this);
}

std::shared_ptr<ITable> PyDict::clone() const {
    return std::make_shared<PyDict>(*this);
}

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
