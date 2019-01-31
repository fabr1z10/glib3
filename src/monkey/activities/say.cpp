#include <monkey/activities/say.h>
#include <gfx/engine.h>
#include <gfx/activities/animate.h>
#include <gfx/activities/setstate.h>
#include <gfx/activities/showmessage.h>

void Say::Start() {

    if (!m_noAnim) {
        if (m_animStart.empty()) {
            Push (std::make_shared<SetState>(m_actorId, "talk"));
        } else {
            Push (std::make_shared<Animate>(m_actorId, m_animStart, 0));
        }
    }

    for (auto& s : m_lines) {

        Push(std::make_shared<ShowMessage>(s, "monkey", m_actorId, 8, m_color, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), BOTTOM, 1.0f, m_offset));
    }

    if (!m_noAnim) {
        if (m_animEnd.empty()) {
            Push (std::make_shared<SetState>(m_actorId, "idle"));
        } else {
            Push (std::make_shared<Animate>(m_actorId, m_animEnd, 0));
        }
    }

}
