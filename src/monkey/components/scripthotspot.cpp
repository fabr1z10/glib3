#include <monkey/components/scripthotspot.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <monkey/entity.h>
#include <monkey/python/wrap1.h>

namespace py = pybind11;

ScriptHotSpot::ScriptHotSpot(const ITable &t) : HotSpot(t), r_enter(py::none()), r_leave(py::none()), r_move(py::none()), r_click(py::none()) {

    if (t.hasKey("onenter")) {
        auto r = t.get<py::function>("onenter");
        SetOnEnter(r);
    }

    if (t.hasKey("onleave")) {
        auto r = t.get<py::function>("onleave");
        SetOnLeave(r);
    }

    if (t.hasKey("onclick")) {
        auto r = t.get<py::function>("onclick");
        SetOnClick(r);
    }

    if (t.hasKey("onrmbclick")) {
        auto r = t.get<py::function>("onrmbclick");
        SetOnRightMouseButtonClick(r);
    }

    if (t.hasKey("onmove")) {
        auto r = t.get<py::function>("onmove");
        SetOnMove(r);
    }
}





void ScriptHotSpot::onClick(glm::vec2 pos, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && !r_click.is_none()) {
            pybind11::object example = py::module::import("example").attr("Wrap1");
            pybind11::object w = example();
            Wrap1* wo = w.cast<Wrap1*>();
            wo->setEntity(m_entity);
            r_click(pos.x, pos.y, w);
            //r_click->execute(pos.x, pos.y, EntityWrapper(m_entity));
        } else if (button == GLFW_MOUSE_BUTTON_RIGHT && !m_rmbClick.is_none()){
            //m_rmbClick->execute(EntityWrapper(m_entity));
        }

    }
    //if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && r_click != nullptr)


        //r_click->operator()(EntityWrapper(m_entity));
}
void ScriptHotSpot::onMove(glm::vec2 p) {

    if (!r_move.is_none()) {
        //r_move->operator()(p.x, p.y);
    }
}
void ScriptHotSpot::onEnter() {
    if (!r_enter.is_none()) {
        //#pybind11::object o;
        pybind11::object example = py::module::import("example").attr("Wrap1");

        pybind11::object w = example();
        Wrap1* wo = w.cast<Wrap1*>();
        wo->setEntity(m_entity);
        r_enter(w);
    }
}

void ScriptHotSpot::onLeave() {
    if (!r_leave.is_none()) {
        pybind11::object example = py::module::import("example").attr("Wrap1");
        pybind11::object w = example();
        Wrap1* wo = w.cast<Wrap1*>();
        wo->setEntity(m_entity);
        r_leave(w);
    }
    //r_leave->operator()(EntityWrapper(m_entity));
}

std::type_index ScriptHotSpot::GetType() {
    return std::type_index(typeid(HotSpot));
}
