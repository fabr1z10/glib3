#include <gfx/activities/flip.h>
#include <gfx/components/renderer.h>
#include <gfx/entity.h>
#include <gfx/engine.h>

Flip::Flip(const std::string& id, int mode) : Activity(), m_actor(id), m_value(mode) {}

void Flip::Start() {
    auto entity = Engine::get().GetRef<Entity>(m_actor);
    if (m_value == 0) {
        entity->FlipX();
    } else {
        entity->SetFlipX(m_value == 2);
    }

    SetComplete();
}