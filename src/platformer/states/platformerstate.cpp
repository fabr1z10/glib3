#include <platformer/states/platformerstate.h>
//#include <gfx/components/controller2d.h>

#include <gfx/entity.h>
#include <gfx/components/icontroller.h>
#include <gfx/components/inputmethod.h>
#include <gfx/components/dynamics2d.h>
#include <gfx/components/animator.h>
//#include <GLFW/glfw3.h>
//#include <gfx/math/geom.h>
//#include <gfx/error.h>
//#include <gfx/components/renderer.h>
//#include <gfx/components/dynamics2d.h>
//#include <gfx/engine.h>
//
//extern GLFWwindow* window;
//
PlatformerState::PlatformerState() : State() {}

PlatformerState::PlatformerState(const PlatformerState &) {


}


void PlatformerState::AttachStateMachine(StateMachine * sm) {
    m_sm = sm;
    m_entity = sm->GetObject();
    m_controller = m_entity->GetComponent<IController>();
    if (m_controller == nullptr) {
        GLIB_FAIL("Platformer state requires a <Controller2D> component!");
    }
    m_dynamics = dynamic_cast<Dynamics2D*>(m_entity->GetComponent<Properties>());
    if (m_dynamics == nullptr) {
        GLIB_FAIL("Walk4Way state requires a <Dynamics2D> component!");
    }
    //m_animator = m_entity->GetComponent<Animator>();
    m_input = m_entity->GetComponent<InputMethod>();
    if (m_input == nullptr) {
        GLIB_FAIL("Walk state requires an <InputMethod> component!");
    }
    m_animator = m_entity->GetComponent<IAnimator>();


}

void PlatformerState::AddKey(int key, std::shared_ptr<StateAction> action) {
    m_actions.insert(std::make_pair(key, action));

}

bool PlatformerState::KeyListener(int key) {
    auto f = m_actions.find(key);
    if (f == m_actions.end())
        return false;
    f->second->Run(m_sm);
    return true;
}


void PlatformerState::SetOverrideAnimation(const std::string &anim) {
    m_overrideAnimation = anim;
    m_animator->SetAnimation(anim);
}


void PlatformerState::UpdateAnimation() {
    if (!m_overrideAnimation.empty()) {
        if (m_animator->IsComplete()) {
            // in this case we reset the animation based on vy
            ResetAnimation();
        }
        return;
    }
    ModifyAnimation();
}
//
//void PlatformerState::Init(Entity* e) {
//    //StateBehaviour::Init(e);
//    m_entity = e;
//
//    m_controller = m_entity->GetComponent<Controller2D>();
//    if (m_controller == nullptr) {
//        GLIB_FAIL("Required a controller2D component!")
//    }
//    m_renderer = m_entity->GetComponent<Renderer>();
//    if (m_renderer == nullptr) {
//        GLIB_FAIL("Required a renderer component!")
//    }
//    m_dynamics = m_entity->GetComponent<Dynamics2D>();
//    if (m_dynamics == nullptr) {
//        GLIB_FAIL("Required a dynamics2d component!");
//    }
//}
