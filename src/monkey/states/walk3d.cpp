#include <monkey/states/walk3d.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/animator.h>
#include <monkey/entity.h>


Walk3D::Walk3D(const Walk3D &) {
    
}

Walk3D::Walk3D(const ITable & t) : State(t) {
    m_acceleration = t.get<float> ("acceleration");
}

std::shared_ptr<State> Walk3D::clone() const {
    return std::make_shared<Walk3D>(*this);
}

void Walk3D::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();
    
    m_input = m_entity->GetComponent<InputMethod>();
    if (m_input == nullptr) {
        GLIB_FAIL("Walk state requires an <InputMethod> component!");
    }
    m_animator = m_entity->GetComponent<IAnimator>();
}

void Walk3D::Init(pybind11::dict&) {
}

void Walk3D::End() {
    
}

void Walk3D::Run (double dt) {
    
    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);
    bool down = m_input->isKeyDown(GLFW_KEY_DOWN);
    
    if (up || down) {
        float dir = up ? 1.0f : -1.0f;
        m_entity->MoveLocal(glm::vec2(0.0f, dir));
    }
    if (left || right) {
        float angle = left ? 0.01 : -0.01f;
        m_entity->Rotate(angle, glm::vec3(0, 0, 1));
    }
}



//#inc