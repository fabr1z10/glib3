#include <platformer/states/platformerstate.h>
#include <gfx/components/controller2d.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>
#include <gfx/math/geom.h>
#include <gfx/error.h>
#include <gfx/components/renderer.h>
#include <gfx/components/dynamics2d.h>
#include <gfx/engine.h>

extern GLFWwindow* window;

PlatformerState::PlatformerState() :
        StateBehaviour(), m_controller(nullptr), m_renderer(nullptr), m_keyboard(Engine::get().GetKeyboard())
{}

void PlatformerState::Init(Entity* e) {
    //StateBehaviour::Init(e);
    m_entity = e;

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
