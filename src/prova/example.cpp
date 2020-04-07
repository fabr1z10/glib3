#include "example.h"
#include <pybind11/pybind11.h>
#include <monkey/python/wrap1.h>
#include <monkey/python/pymonkey.h>
#include "rect.h"

namespace py = pybind11;

Monkey * m_monkey;
Engine * m_engine;

int add(int i, int j) {
    return i + j;
}

void init(PyEngine& p) {
    m_monkey = p.getMo();
    m_engine = p.getEn();
    //std::cerr <<"loo"<< id;
}


PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 exciaoample plugin"; // optional module docstring

    py::class_<Wrap1>(m, "Wrap1")
        .def(py::init<>())
        .def("x", &Wrap1::x)
        .def("setColor", &Wrap1::setColor)
        .def("setText", &Wrap1::setText)
        .def("appendText", &Wrap1::appendText);

    py::class_<PyEngine>(m, "engine")
        //.def("get", &PyEngine::get, py::arg("tag"))
        .def("prova", &PyEngine::prova);

//    py::class_<Rect>(m, "rect")
//        .def(py::init<float, float>())
//        .def("widthh", &Rect::width)
//        .def("height", &Rect::height)
//        .def("area", &Rect::area)
//        .def("diag", &Rect::diag);

    m.def("add", &add, "A functione which adds two numbers");
    m.def("get", &get, "Gets a entity by tag");
    m.def("play", &play);
    m.def("getDeviceSize", &getDeviceSize);
    m.def("init", &init);

    m.attr("what") = PyEngine();

}
