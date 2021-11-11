#include <monkey/states/walk3d.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/animrenderer.h>
#include <monkey/entity.h>
#include <monkey/components/controller3d.h>
#include <GLFW/glfw3.h>

Walk3D::Walk3D(const ITab& t) : State(t) {
    m_acceleration = t.get<float> ("acceleration");
}

void Walk3D::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();
    
    m_input = m_entity->GetComponent<InputMethod>();
    if (m_input == nullptr) {
        GLIB_FAIL("Walk state requires an <InputMethod> component!");
    }
    m_animator = dynamic_cast<AnimationRenderer*>(m_entity->GetComponent<Renderer>());
}

void Walk3D::Init(const ITab&) {
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
