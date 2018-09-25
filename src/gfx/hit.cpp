#include <gfx/hit.h>
#include <gfx/entity.h>
#include <gfx/engine.h>
#include <gfx/renderer.h>

Hit::Hit (const std::string& anim) : State(), m_anim(anim)
{}

void Hit::Init(Entity* e) {
    State::Init(e);
    m_renderer = m_entity->GetComponent<Renderer>();
    m_engine = Engine::get().GetRunner<CollisionEngine>();
}

void Hit::Start() {
    m_renderer->SetAnimation(m_anim);

}