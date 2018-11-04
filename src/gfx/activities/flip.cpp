#include <gfx/activities/flip.h>
#include <gfx/components/renderer.h>
#include <gfx/entity.h>
#include <gfx/engine.h>

Flip::Flip(const std::string& id, bool horizontal) : Activity(), m_actor(id), m_value(horizontal) {}

void Flip::Start() {
    auto entity = Engine::get().GetRef<Entity>(m_actor);
    //entity->GetComponent<Renderer>()->SetFlipX(m_value);
    entity->FlipX();
    SetComplete();
}