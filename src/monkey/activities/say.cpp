#include <monkey/activities/say.h>
#include <gfx/engine.h>
#include <gfx/components/renderer.h>
#include <gfx/activities/animate.h>
#include <gfx/activities/showmessage.h>


void Say::Start() {

    auto actor = Engine::get().GetRef<Entity>(m_actorId);
    glm::vec2 currentPos(actor->GetPosition());


    //int count = 0;
    std::string animStart;
    std::string animEnd;
    //bool flipx {false};
    Renderer* r = actor->GetComponent<Renderer>();
    //bool flipx = r->GetFlipX();

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
        if (m_animStart.empty() && m_animEnd.empty()) {
            // if they are both empty run auto
            animStart = "talk_" + face;
            animEnd = "idle_" + face;
        } else {
            animStart = m_animStart;
            animEnd = m_animEnd;
        }

//        if (m_animStart.empty())
//            animStart = "talk_" + face;
//        else
//            animStart = m_animStart;
//        if (m_animEnd.empty())
//            animEnd = "idle_" + face;
//        else
//            animEnd = m_animEnd;
        if (!animStart.empty())
            Push(std::make_shared<Animate>(actor, animStart, 0));
    }

    for (auto& s : m_lines) {

        Push(std::make_shared<ShowMessage>(s, "monkey", m_actorId, 8, m_color, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), BOTTOM, 1.0f, m_offset));
    }
    if (!m_noAnim) {
        if (!animEnd.empty())
            Push(std::make_shared<Animate>(actor, animEnd, 0));
    }

}
