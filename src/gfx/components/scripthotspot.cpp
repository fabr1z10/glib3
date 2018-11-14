#include <gfx/components/scripthotspot.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gfx/entity.h>
#include <gfx/entitywrapper.h>


void ScriptHotSpot::onLeave() {
    if (r_leave != nullptr)
        r_leave->operator()(EntityWrapper(m_entity));
}
void ScriptHotSpot::onClick(glm::vec2) {
    std::cout << "CLICK ON SCRIPTHS\n";
    if (r_click != nullptr)
        r_click->operator()(EntityWrapper(m_entity));
}
void ScriptHotSpot::onMove(glm::vec2 p) {

    if (r_move != nullptr)
        r_move->operator()(p.x, p.y);
}
void ScriptHotSpot::onEnter() {
    if (r_enter != nullptr)
        r_enter->operator()(EntityWrapper(m_entity));
}


std::type_index ScriptHotSpot::GetType() {
    return std::type_index(typeid(HotSpot));
}
