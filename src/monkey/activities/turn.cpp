#include <monkey/activities/turn.h>
#include <gfx/engine.h>
#include <gfx/components/renderer.h>

void Turn::Start() {

    auto actor = Engine::get().GetRef<Entity>(m_actorId);
    auto renderer = actor->GetComponent<Renderer>();

    renderer->SetFlipX(m_dir == "west");
    if (m_dir == "north") {
        renderer->SetAnimation("idle_back");
    } else if (m_dir == "south") {
        renderer->SetAnimation("idle_front");
    } else {
        renderer->SetAnimation("idle_right");

    }
    SetComplete();

}