#include "say.h"
#include <monkey/engine.h>
#include <monkey/activities/animate.h>
#include <monkey/activities/setstate.h>
#include <monkey/activities/showmessage.h>
#include <monkey/monkey.h>

void Say::Start() {

    // if the walk has a tag, then get the id
    if (!m_tag.empty()) {
        m_actorId =  Monkey::get().Get<Ref>(m_tag)->GetId();
    }

    if (!m_noAnim) {

        if (m_animStart.empty()) {
            auto action =std::make_shared<SetState>("talk");
            action->SetId(m_actorId);
            Push (action);
        } else {
            auto action =std::make_shared<Animate>(m_animStart, true);
            action->SetId(m_actorId);
            Push (action);
        }
    }

    for (auto& s : m_lines) {

        Push(std::make_shared<ShowMessage>(s, "monkey", m_actorId, 8, m_color, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), BOTTOM, 1.0f, m_offset));
    }

    if (!m_noAnim) {
        if (m_animEnd.empty()) {
            auto action =std::make_shared<SetState>("idle");
            action->SetId(m_actorId);
            Push (action);
        } else {
            auto action =std::make_shared<Animate>(m_animEnd, true);
            action->SetId(m_actorId);
            Push (action);
            //Push (std::make_shared<Animate>(m_actorId, m_animEnd, 0));
        }
    }

}