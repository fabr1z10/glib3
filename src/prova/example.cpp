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
        .def("id", &Wrap1::id)
        .def_property_readonly("tag", &Wrap1::tag)
        .def_property_readonly("x", &Wrap1::x)
        .def_property_readonly("y", &Wrap1::y)
        .def_property_readonly("z", &Wrap1::z)
        .def_property_readonly("valid", &Wrap1::valid)
        .def_property_readonly("flipx", &Wrap1::getFlipx)
        .def_property_readonly("anim", &Wrap1::getAnim)
        .def_property("vy", &Wrap1::getVy, &Wrap1::setVy)
        .def_property("vx", &Wrap1::getVx, &Wrap1::setVx)
        .def_property("elevation", &Wrap1::getElevation, &Wrap1::setElevation)
        .def_property("scale", &Wrap1::getScale, &Wrap1::setScale)
        .def("setPosition", &Wrap1::setPosition)
        .def("getAttackPos", &Wrap1::getAttackPos)
        .def("parent", &Wrap1::getParent)
        .def("setColor", &Wrap1::setColor)
        .def("setText", &Wrap1::setText)
        .def("setModel", &Wrap1::setModel)
        .def("setActive", &Wrap1::setActive)
        .def("enableControls", &Wrap1::enableControls)
        .def("enableUpdate", &Wrap1::setEnableUpdate)
        .def("appendText", &Wrap1::appendText)
        .def("add", &Wrap1::add)
        .def("getInfo", &Wrap1::getInfo)
        .def("getState", &Wrap1::getState)
        .def("setState", &Wrap1::setState)
        .def("move", &Wrap1::move)
        .def("clearText", &Wrap1::clearText)
        .def("follow", &Wrap1::follow)
    	.def("rotatex", &Wrap1::rotx)
    	.def("getTextSize", &Wrap1::getTextSize);

    py::class_<PyEngine>(m, "engine")
        //.def("get", &PyEngine::get, py::arg("tag"))
        .def("prova", &PyEngine::prova);

//    py::class_<Rect>(m, "rect")
//        .def(py::init<float, float>())
//        .def("widthh", &Rect::width)
//        .def("height", &Rect::height)
//        .def("area", &Rect::area)
//        .def("diag", &Rect::diag);

    m.def("adder", &add, "A functione which adds two numbers");
    m.def("get", &get, "Gets a entity by tag");
    m.def("killScript", &killScript, "Kills a script");
    m.def("remove", &rmv, "Removes an entity by id");
    m.def("removeByTag", &rmvt, "Removes an entity by tag");
    m.def("campos", &campos);
    m.def("play", &play);
    m.def("restart", &restart);
    //m.def("addLine", &addLine);
    m.def("getDeviceSize", &getDeviceSize);
    m.def("init", &init);
    m.attr("dir") = "_not set_";

    m.attr("what") = PyEngine();

}
