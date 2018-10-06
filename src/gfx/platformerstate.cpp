#include <gfx/platformerstate.h>
#include <gfx/controller2d.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>
#include <graph/geom.h>
#include <gfx/error.h>
#include <gfx/renderer.h>
#include <gfx/dynamics2d.h>

extern GLFWwindow* window;

PlatformerState::PlatformerState(const std::string& anim) :
        State(), m_anim(anim), m_controller(nullptr), m_renderer(nullptr)
{}

void PlatformerState::Init(Entity* e) {
    State::Init(e);
    m_controller = m_entity->GetComponent<Controller2D>();
    if (m_controller == nullptr) {
        GLIB_FAIL("Required a controller2D component!")
    }
    m_renderer = m_entity->GetComponent<Renderer>();
    if (m_renderer == nullptr) {
        GLIB_FAIL("Required a renderer component!")
    }
    m_dynamics = m_entity->GetComponent<Dynamics2D>();
    if (m_dynamics == nullptr) {
        GLIB_FAIL("Required a dynamics2d component!");
    }
}

void PlatformerState::Start() {

    // set the animation
    m_renderer->SetAnimation(m_anim);

    // colliders!
}

