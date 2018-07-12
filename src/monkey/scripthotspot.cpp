#include <monkey/scripthotspot.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gfx/entity.h>
#include <monkey/luawrapper.h>
#include <monkey/entitywrapper.h>


void ScriptHotSpot::onLeave() {
    if (r_leave != nullptr)
        r_leave->operator()(EntityWrapper(m_entity));
}
void ScriptHotSpot::onClick(glm::vec2) {
    std::cout << "CLICK ON SCRIPTHS\n";
    if (r_click != nullptr)
        r_click->operator()(EntityWrapper(m_entity));
}
void ScriptHotSpot::onEnter() {
    if (r_enter != nullptr)
        r_enter->operator()(EntityWrapper(m_entity));
}
