#include <monkey/components/scriptwalktrigger.h>
#include <monkey/entitywrapper.h>


ScriptWalkTrigger::ScriptWalkTrigger(std::shared_ptr<Shape> shape, const std::string &target) : WalkTrigger(shape, target) {


}
void ScriptWalkTrigger::onLeave() {
    if (r_leave != nullptr)
        r_leave->operator()(EntityWrapper(m_entity));
}
void ScriptWalkTrigger::onStay() {
    if (r_stay!= nullptr)
        r_stay->operator()(EntityWrapper(m_entity));
}
void ScriptWalkTrigger::onEnter() {
    if (r_enter != nullptr)
        r_enter->operator()(EntityWrapper(m_entity));
}