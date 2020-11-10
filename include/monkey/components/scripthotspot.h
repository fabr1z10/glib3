#pragma once

#include <monkey/components/hotspot.h>

class ScriptHotSpot : public HotSpot {
public:
    ScriptHotSpot (int priority) : HotSpot(priority) {}
    ScriptHotSpot (const ITable& t);

    ScriptHotSpot (
            std::shared_ptr<Shape> shape,
            int priority) : HotSpot(shape, priority) {}
    
    void onLeave() override;
    void onClick(glm::vec2, int, int, int) override;
    void onEnter() override;
    void onMove(glm::vec2) override;
    void SetOnEnter(pybind11::function ref) {
        r_enter = ref;
    }
    void SetOnLeave(pybind11::function ref) {
        r_leave= ref;
    }
    void SetOnClick(pybind11::function ref) {
        r_click = ref;
    }
    void SetOnRightMouseButtonClick(pybind11::function ref) {
        m_rmbClick = ref;
    }
    void SetOnMove(pybind11::function ref) {
        r_move= ref;
    }
    using ParentClass = HotSpot;
    std::type_index GetType() override;

private:
    //bool m_inShape;
    pybind11::function r_enter;
    pybind11::function r_leave;
    pybind11::function r_click;
    pybind11::function m_rmbClick;
    pybind11::function r_move;

};
