#include <monkey/states/platformerstate.h>
#include <monkey/components/controller2d.h>

#include <monkey/entity.h>
#include <monkey/components/icontroller.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>
//#include <GLFW/glfw3.h>
//#include <monkey/math/geom.h>
//#include <monkey/error.h>
#include <monkey/components/animrenderer.h>
//#include <monkey/components/dynamics2d.h>
//#include <monkey/engine.h>
//
//extern GLFWwindow* window;
//
PlatformerState::PlatformerState() : State() {}

PlatformerState::PlatformerState(const PlatformerState &) {


}

PlatformerState::PlatformerState(const ITab& t) : State(t) {}


void PlatformerState::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();
    m_controller = (m_entity->GetComponent<IController>());
    if (m_controller == nullptr) {
        GLIB_FAIL("Platformer state requires a <Controller2D> component!");
    }
    m_dynamics = m_entity->GetComponent<Dynamics2D>();
    if (m_dynamics == nullptr) {
        GLIB_FAIL("Platormer state requires a <Dynamics2D> component!");
    }
    //m_animator = m_entity->GetComponent<Animator>();
    m_input = m_entity->GetComponent<InputMethod>();
    //if (m_input == nullptr) {
    //    GLIB_FAIL("Walk state requires an <InputMethod> component!");
    //}
    m_animator = dynamic_cast<AnimationRenderer*>(m_entity->GetComponent<Renderer>());


}



//bool PlatformerState::KeyListener(int key) {
//    auto f = m_actions.find(key);
//    if (f == m_actions.end())
//        return false;
//    f->second->Run(m_sm);
//    return true;
//}


void PlatformerState::SetOverrideAnimation(const std::string &anim) {
    m_overrideAnimation = anim;
    m_animator->setAnimation(anim);
}


void PlatformerState::UpdateAnimation() {
    if (!m_overrideAnimation.empty()) {
        if (m_animator->isComplete()) {
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
