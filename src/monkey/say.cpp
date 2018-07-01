#include <monkey/say.h>
#include <gfx/engine.h>
#include <gfx/renderer.h>
#include <gfx/animate.h>
#include <monkey/showmessage.h>

void Say::Start() {

    auto actor = Engine::get().GetRef<Entity>(m_actorId);
    glm::vec2 currentPos(actor->GetPosition());

    Renderer* r = actor->GetComponent<Renderer>();
    std::string anim = r->GetAnimation();
    std::string animStart;
    std::string animEnd;
    size_t s = anim.find_last_of('_');
    std::string face;
    bool flipx = r->GetFlipX();
    if (s == std::string::npos) {
        face = "front";
    } else {
        std::string facing = anim.substr(s+1);
        if (facing == "left" || facing == "right" || facing == "front" || facing == "back") {
            face = facing;
        } else
            face = "front";
    }
    animStart ="talk_" + face;
    animEnd ="idle_" + face;
    int count = 0;
    Push(std::make_shared<Animate>(count++, actor, animStart, flipx));

    for (auto& s : m_lines) {

        Push(std::make_shared<ShowMessage>(count++, s, "monkey", m_actorId, 8, m_color, glm::vec4(0.0f), BOTTOM, 1.0f));
    }
    Push(std::make_shared<Animate>(count++, actor, animEnd, flipx));

}
