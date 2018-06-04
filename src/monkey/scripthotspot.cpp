#include <monkey/scripthotspot.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gfx/entity.h>

#include <monkey/luawrapper.h>
#include <monkey/entitywrapper.h>

//void ScriptHotSpot::CursorPosCallback(GLFWwindow* window, double x, double y) {
//    HotSpot::CursorPosCallback(window, x, y);
//    glm::vec2 worldCoords = m_cam->GetWorldCoordinates(glm::vec2(x, y));
//    glm::vec3 pos = m_entity->GetPosition();
//    glm::vec2 lpos = worldCoords - glm::vec2(pos);
//    if (m_shape->isPointInside(lpos)) {
//        if (!m_inShape) {
//            std::cout << "Entering\n";
//            if (!m_onEnter.empty())
//            {
//                // pass
//                LuaWrapper::Call(m_onEnter, EntityWrapper(m_entity));
//            }
//        }
//        m_inShape = true;
//    } else {
//        if (m_inShape) {
//            std::cout << "Exiting\n";
//            if (!m_onLeave.empty())
//            {
//                LuaWrapper::Call(m_onLeave, EntityWrapper(m_entity));
//            }
//        }
//        m_inShape = false;
//    }
//
//}

void ScriptHotSpot::onLeave() {
    if (r_leave != nullptr)
        r_leave->operator()(EntityWrapper(m_entity));
}
void ScriptHotSpot::onClick(glm::vec2) {
    if (r_click != nullptr)
        r_click->operator()(EntityWrapper(m_entity));
}
void ScriptHotSpot::onEnter() {
    if (r_enter != nullptr)
        r_enter->operator()(EntityWrapper(m_entity));
    //if (!m_onEnter.empty()) {
    //    LuaWrapper::Call(m_onEnter, EntityWrapper(m_entity));
    //}
}