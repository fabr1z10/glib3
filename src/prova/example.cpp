#include <pybind11/pybind11.h>
#include <monkey/python/wrap1.h>
#include <monkey/python/pymonkey.h>
#include "rect.h"

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 exciaoample plugin"; // optional module docstring

    py::class_<Wrap1>(m, "Wrap1")
        .def(py::init<>())
        .def("x", &Wrap1::x)
        .def("setColor", &Wrap1::setColor)
        .def("setText", &Wrap1::setText);

    py::class_<PyEngine>(m, "engine")
        .def("get", &PyEngine::get, py::arg("tag"))
        .def("prova", &PyEngine::prova);

    py::class_<Rect>(m, "rect")
        .def(py::init<float, float>())
        .def("widthh", &Rect::width)
        .def("height", &Rect::height)
        .def("area", &Rect::area);

    m.def("add", &add, "A functione which adds two numbers");
    m.attr("what") = PyEngine();
}
