#include "say.h"
#include "../components/character.h"
#include <monkey/engine.h>
#include <monkey/activities/animate.h>
#include <monkey/activities/setstate.h>
#include <monkey/activities/showmessage.h>
#include <monkey/monkey.h>
#include <monkey/components/info.h>


Say::Say(const ITab& t) : Sequence() {
    m_lines = t.get<std::vector<std::string>>("lines");
    //m_color = t.Get<glm::vec4>("color");
    // m_color /= 255.0f;
    //m_offset = t.Get<glm::vec2>("offset");
    m_fontId = t.get<std::string>("font");

    if (t.has("id")) {
        m_actorId = t.get<int>("id");
    } else {
        m_tag = t.get<std::string>("tag");
    }

    bool animate = t.get<bool>("animate", true);
//    if (t.hasKey("animstart")) {
//        auto animStart = t.get<std::string>("animstart");
//        SetAnimationStart(animStart);
//    }
//    if (t.hasKey("animend")) {
//        auto animEnd = t.get<std::string>("animend");
//        SetAnimationEnd(animEnd);
//    }

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
    auto infoc = item->GetComponent<CharacterController>();

    auto offset = infoc->getTextOffset();
    auto color = infoc->getTextColor();
    //color /= 255.0f;

    //if (infoc == nullptr) GLIB_FAIL("<Say> action requires an info component!");
    //auto addInfo = infoc->get2();



    if (!m_noAnim) {
        // automatically assign animation
        char dir = infoc->getDirection();
        auto action =std::make_shared<Animate>("talk_" + std::string(1, dir), true);
        action->SetTag(m_tag);
        Push(action);
    }

    for (auto& s : m_lines) {

        Push(std::make_shared<ShowMessage>(s, m_fontId, m_actorId, 8,
                                           color, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
                                           BOTTOM, 1.0f, offset));
    }

    if (!m_noAnim) {
        // automatically assign animation
        auto action =std::make_shared<Animate>("idle_" + std::string(1, infoc->getDirection()), true);
        action->SetTag(m_tag);
        Push(action);
    }

}
