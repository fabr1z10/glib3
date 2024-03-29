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

bool isPressed(int key) {
    return (glfwGetKey(m_engine->getWindow(), key) == GLFW_PRESS);
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
        .def_property_readonly("id", &Wrap1::id)
        .def_property_readonly("tag", &Wrap1::tag)
        .def_property_readonly("x", &Wrap1::x)
        .def_property_readonly("y", &Wrap1::y)
        .def_property_readonly("z", &Wrap1::z)
        .def_property_readonly("valid", &Wrap1::valid)
        .def_property_readonly("flipx", &Wrap1::getFlipx)
        .def_property_readonly("anim", &Wrap1::getAnim)
        .def_property_readonly("grounded", &Wrap1::grounded)
        .def_property("vy", &Wrap1::getVy, &Wrap1::setVy)
        .def_property("vx", &Wrap1::getVx, &Wrap1::setVx)
        .def_property("elevation", &Wrap1::getElevation, &Wrap1::setElevation)
        .def_property("scale", &Wrap1::getScale, &Wrap1::setScale)
        .def_property("collisionFlag", &Wrap1::getCollisionFlag, &Wrap1::setCollisionFlag)
        .def_property("collisionMask", &Wrap1::getCollisionMask, &Wrap1::setCollisionMask)
        .def("play", &Wrap1::play)
        .def("killScripts", &Wrap1::killScripts)
        .def("setPosition", &Wrap1::setPosition)
        .def("setTransform", &Wrap1::setTransform)
        .def("getAttackPos", &Wrap1::getAttackPos)
        .def("parent", &Wrap1::getParent)
        .def("setColor", &Wrap1::setColor)
        .def("setText", &Wrap1::setText)
        .def("setModel", &Wrap1::setModel)
        .def("setMesh", &Wrap1::setMesh)
        .def("setAnim", &Wrap1::setAnim)
        .def("setActive", &Wrap1::setActive)
		.def("setVisible", &Wrap1::setVisible)
        .def("enableControls", &Wrap1::enableControls)
        .def("enableUpdate", &Wrap1::setEnableUpdate)
        .def("appendText", &Wrap1::appendText)
        .def("add", &Wrap1::add)
        .def("getInfo", &Wrap1::getInfo)
        .def("getState", &Wrap1::getState)
        .def("setState", &Wrap1::setState)
        .def("move", &Wrap1::move)
        .def("clear", &Wrap1::clear)
        .def("clearText", &Wrap1::clearText)
        .def("follow", &Wrap1::follow)
    	.def("rotatex", &Wrap1::rotx)
    	.def("getTextSize", &Wrap1::getTextSize)
    	.def("getKeyFrame", &Wrap1::getKeyFrame)
    	.def("getCollisionBounds",&Wrap1::getCollisionBounds)
		.def("getAttackCollisionBounds",&Wrap1::getAttackCollisionBounds)
		//.def("getKeyPoint", &Wrap1::getKeyPoint)
		.def("setColliderBounds", &Wrap1::setControllerBounds)

		.def("children", &Wrap1::getChildren)
		.def("getBoxSize", &Wrap1::getBoxSize);


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
    m.def("is_pressed", &isPressed, "Check if a key is pressed");
    m.def("get", &get, "Gets a entity by tag");
    m.def("getById", &getById, "Gets an entity by id");
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
