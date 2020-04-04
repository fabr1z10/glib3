#include "say.h"
#include <monkey/engine.h>
#include <monkey/activities/animate.h>
#include <monkey/activities/setstate.h>
#include <monkey/activities/showmessage.h>
#include <monkey/monkey.h>
#include <monkey/components/info.h>

Say::Say(const LuaTable& t) : Sequence() {
    m_lines = t.GetVector<std::string>("lines");
    m_fontId = t.Get<std::string>("font");

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

Say::Say(const ITable& t) : Sequence() {
    m_lines = t.get<std::vector<std::string>>("lines");
    //m_color = t.Get<glm::vec4>("color");
    // m_color /= 255.0f;
    //m_offset = t.Get<glm::vec2>("offset");
    m_fontId = t.get<std::string>("font");

    if (t.hasKey("id")) {
        m_actorId = t.get<int>("id");
    } else {
        m_tag = t.get<std::string>("tag");
    }

    bool animate = t.get<bool>("animate", true);
    if (t.hasKey("animstart")) {
        auto animStart = t.get<std::string>("animstart");
        SetAnimationStart(animStart);
    }
    if (t.hasKey("animend")) {
        auto animEnd = t.get<std::string>("animend");
        SetAnimationEnd(animEnd);
    }

    SetNoAnim(!animate);

}



void Say::Start() {

    // if the walk has a tag, then get the id
    Entity* item = nullptr;
    if (!m_tag.empty()) {
        item = Monkey::get().Get<Entity>(m_tag);
        m_actorId = item->GetId();
        //m_actorId =  Monkey::get().Get<Ref>(m_tag)->GetId();
    } else {
        item = Monkey::get().Get<Entity>(m_actorId);
    }

    // need to check the character information. offset and text color
    auto infoc = item->GetComponent<LuaInfo>();
    if (infoc == nullptr) GLIB_FAIL("<Say> action requires an info component!");
    const auto* addInfo = infoc->get2();

    m_color = addInfo->get<glm::vec4>("text_color");
    m_color /= 255.0f;
    m_offset = addInfo->get<glm::vec2>("text_offset");

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

        Push(std::make_shared<ShowMessage>(s, m_fontId, m_actorId, 8, m_color, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), BOTTOM, 1.0f, m_offset));
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
