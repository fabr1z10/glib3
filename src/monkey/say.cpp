#include <monkey/say.h>
#include <gfx/engine.h>
#include <gfx/renderer.h>
#include <gfx/animate.h>
#include <monkey/showmessage.h>

void Say::Start() {

    auto actor = Engine::get().GetRef<Entity>(m_actorId);
    glm::vec2 currentPos(actor->GetPosition());


    int count = 0;
    std::string animStart;
    std::string animEnd;
    //bool flipx {false};
    Renderer* r = actor->GetComponent<Renderer>();
    bool flipx = r->GetFlipX();

    if (!m_noAnim) {
        std::string anim = r->GetAnimation();
        size_t s = anim.find_last_of('_');
        std::string face;

        if (s == std::string::npos) {
            face = "front";
        } else {
            std::string facing = anim.substr(s + 1);
            if (facing == "left" || facing == "right" || facing == "front" || facing == "back") {
                face = facing;
            } else
                face = "front";
        }
        if (m_animStart.empty())
            animStart = "talk_" + face;
        else
            animStart = m_animStart;
        if (m_animEnd.empty())
            animEnd = "idle_" + face;
        else
            animEnd = m_animEnd;
        Push(std::make_shared<Animate>(actor, animStart, flipx));
    }

    for (auto& s : m_lines) {

        Push(std::make_shared<ShowMessage>(s, "monkey", m_actorId, 8, m_color, glm::vec4(0.0f), BOTTOM, 1.0f, m_offset));
    }
    if (!m_noAnim) {
        Push(std::make_shared<Animate>(actor, animEnd, flipx));
    }

}
