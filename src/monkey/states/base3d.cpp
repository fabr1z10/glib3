#include <monkey/states/base3d.h>
#include <monkey/entity.h>
#include <monkey/components/controller3d.h>
#include <monkey/components/dynamics2d.h>


Base3D::Base3D(const ITab& t) : State(t), m_renderer(nullptr)  {
    //auto factory = Engine::get().GetSceneFactory();
    m_maxSpeed = t.get<float>("max_speed");
    auto tmax = t.get<float>("time_acc", 0.0f);
    m_acceleration = (tmax == 0.0f) ? 0.0f : m_maxSpeed / tmax;
    m_gravity = t.get<float>("gravity");

}



void Base3D::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();
    m_controller = dynamic_cast<Controller3D*>(m_entity->GetComponent<IController>());
    if (m_controller == nullptr) {
        GLIB_FAIL("Platformer state requires a <Controller3D> component!");
    }
    m_renderer = dynamic_cast<AnimationRenderer*>(m_entity->GetComponent<Renderer>());
    m_dynamics = m_entity->GetComponent<Dynamics3D>();
    if (m_dynamics == nullptr) {
        GLIB_FAIL("Platormer state requires a <Dynamics2D> component!");
    }

}