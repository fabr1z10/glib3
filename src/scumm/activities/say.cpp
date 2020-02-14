#include "say.h"
#include <monkey/engine.h>
#include <monkey/activities/animate.h>
#include <monkey/activities/setstate.h>
#include <monkey/activities/showmessage.h>
#include <monkey/monkey.h>

Say::Say(const LuaTable& t) : Sequence() {
    m_lines = t.GetVector<std::string>("lines");
    m_color = t.Get<glm::vec4>("color");
    m_color /= 255.0f;
    m_offset = t.Get<glm::vec2>("offset");

    if (t.HasKey("id")) {
        m_actorId = t.Get<int>("id");
    } else {
        m_tag = t.Get<std::string>("tag");
    }

    bool animate = t.Get<bool>("animate", true);
    if (t.HasKey("animstart")) {
        auto animStart = t.Get<std::string>("animstart");
        SetAnimationStart(animStart);
    }
    if (t.HasKey("animend")) {
        auto animEnd = t.Get<std::string>("animend");
        SetAnimationEnd(animEnd);
    }

    SetNoAnim(!animate);

}

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
