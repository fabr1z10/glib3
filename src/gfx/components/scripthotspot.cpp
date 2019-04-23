#include <gfx/components/scripthotspot.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gfx/entity.h>
#include <gfx/entitywrapper.h>

ScriptHotSpot::ScriptHotSpot(const ScriptHotSpot& orig) :
HotSpot(orig), r_move(orig.r_move), r_click(orig.r_click), r_enter(orig.r_enter), r_leave(orig.r_leave) {

}

std::shared_ptr<Component> ScriptHotSpot::clone() const {
    return std::make_shared<ScriptHotSpot>(ScriptHotSpot(*this));
}

void ScriptHotSpot::onLeave() {
    if (r_leave != nullptr)
        r_leave->operator()(EntityWrapper(m_entity));
}
void ScriptHotSpot::onClick(glm::vec2 pos, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && r_click != nullptr) {
            r_click->execute(pos.x, pos.y, EntityWrapper(m_entity));
        } else if (button == GLFW_MOUSE_BUTTON_RIGHT && m_rmbClick != nullptr){
            m_rmbClick->execute(EntityWrapper(m_entity));
        }

    }
    //if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && r_click != nullptr)


        //r_click->operator()(EntityWrapper(m_entity));
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
