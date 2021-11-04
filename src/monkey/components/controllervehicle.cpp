#include <monkey/components/controllervehicle.h>
#include <monkey/entity.h>
#include <monkey/components/inputmethod.h>

ControllerVehicle::ControllerVehicle(const ITab&) {

}

void ControllerVehicle::Start() {
    m_input = m_entity->GetComponent<InputMethod>();
}

void ControllerVehicle::Update(double) {
    //bool forward = m_input->isKeyDown(GLFW_KEY_LEFT);
  //  bool back = m_input->isKeyDown(GLFW_KEY_RIGHT);


    // update velocity
//    m_currentSpeed +=
}