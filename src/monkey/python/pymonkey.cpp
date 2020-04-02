#include "monkey/python/pymonkey.h"
#include <monkey/entity.h>

namespace py= pybind11;

//Wrap1 PyEngine::get(const std::string & tag) const {
//    auto e = m_monkey->Get<Entity>(tag);
//    Wrap1 w;
//    w.setEntity(e);
////    py::object pye = py::module::import("example").attr("Wrap1");
////    pybind11::object w = pye();
////    auto wo = w.cast<Wrap1*>();
////    wo->setEntity(e);
//    return w;
//}

//void PyEngine::jj(pybind11::object o) {
//   // PyTable pollo(obj);
//   // std::string cio = pollo.get<std::string>("ciao");
//    //std::cerr << cio << "\n";
//}

void PyEngine::prova() {
    std::cout << "ciccciciciici\n";
}