#include <monkey/walk.h>
#include <gfx/engine.h>
#include <gfx/renderer.h>
#include <gfx/animate.h>
#include <gfx/move.h>

void Walk::Start() {

    auto actor = Engine::get().GetRef<Entity>(m_actorId);
    glm::vec2 currentPos(actor->GetPosition());
    glm::vec2 delta = m_p - currentPos;
    if (delta != glm::vec2(0.0f)) {
        std::string anim;
        std::string anim2;
        if (std::fabs(delta.x) > std::fabs(delta.y)) {
            anim = "walk_right";
            anim2 = "idle_right";
        } else {
            if (delta.y > 0) {
                anim = "walk_back";
                anim2 = "idle_back";
            } else {
                anim = "walk_front";
                anim2 = "idle_front";
            }
        }
        bool flipX = (anim == "walk_right" && delta.x < 0);
        actor->GetComponent<Renderer>()->SetFlipX(flipX);
        Push(std::make_shared<Animate>(0, actor, anim));
        Push(std::make_shared<MoveTo>(1, actor, m_p, 50.0f));
        Push(std::make_shared<Animate>(2, actor, anim2));
        //script->AddActivity(p);
    }
}