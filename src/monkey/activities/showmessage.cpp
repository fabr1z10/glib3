#include <monkey/activities/showmessage.h>
#include <monkey/engine.h>
#include <monkey/textmesh.h>
#include <monkey/components/basicrenderer.h>
#include <glm/gtx/transform.hpp>
#include <monkey/model/textmodel.h>


ShowMessage::ShowMessage(const ITab& t) {
    m_actor = -1;
    m_message = t.get<std::string>("text");
    m_font = t.get<std::string>("font");
    m_size = t.get<float>("size", 8.0f);
    m_color = t.get<glm::vec4>("color");
    m_outlineColor = t.get<glm::vec4>("outlinecolor", glm::vec4(0.0f, 0.0f, 0.0f, 255.0f));
    m_color /= 255.0f;
    m_outlineColor /= 255.0f;
    m_align = BOTTOM; //t.Get<TextAlignment>("align", BOTTOM);
    m_offset = t.get<glm::vec2>("offset", glm::vec2(0.0f));
    m_time = t.get<float>("time", 1.0f);
    m_pos = t.get<glm::vec3>("pos");

}

void ShowMessage::Start() {
    auto& m = Monkey::get();
    m_mainCam = m.Get<OrthographicCamera>("maincam");
    auto scene = m.Get<Entity>("main");
    glm::vec2 currentPos;
    if (m_actor != -1) {
        auto actor = m.Get<Entity>(m_actor);
        currentPos = (actor->GetPosition());
    } else {
        currentPos = m_pos;
    }

    currentPos += m_offset;

    auto parent = std::make_shared<Entity>();
    Font* f = Engine::get().GetAssetManager().GetFont(m_font).get();

    auto mesh = std::make_shared<TextMesh>(f, m_message, m_size, m_align, 280.0f);
    auto offset = mesh->getOffset();
    glm::mat4 transform = glm::translate(glm::vec3(offset, 0.0f));
    Bounds ex = mesh->GetBounds();
    ex.Transform(transform);

    glm::vec2 outlineOffsets[] = {{0, 0}, {-1, 0}, {-1,1}, {0, 1}, {1,1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    for (int i =0; i < 9; ++i) {
        auto entity = std::make_shared<Entity>();

        auto model = std::make_shared<TextModel>(mesh);
        auto renderer = std::make_shared<BasicRenderer>(model);

        entity->SetPosition(glm::vec3(outlineOffsets[i] * 0.5f, i == 0 ? 0 : -1));
        renderer->setMultColor(i==0 ? m_color : m_outlineColor);
        renderer->SetTransform(transform);
        entity->AddComponent(renderer);
        parent->AddChild(entity);
    }

    // adjust position so that the message is all visible
    glm::vec2 camPos(m_mainCam->GetPosition());
    glm::vec2 camSize = 0.5f * m_mainCam->GetSize();
    float shiftX = 0.0f;
    if (currentPos.x + ex.min.x < camPos.x - camSize.x) {
        // we need th shift the message RIGHT
        shiftX = (camPos.x - camSize.x) - currentPos.x - ex.min.x;
    } else if (currentPos.x + ex.max.x > camPos.x + camSize.x) {
        shiftX = (camPos.x + camSize.x) - currentPos.x - ex.max.x;
    }

    currentPos += glm::vec2(shiftX, 0.0f);
    glm::vec3 textpos(currentPos.x, currentPos.y, 5.0);
    parent->SetPosition(textpos);
    //parent->SetLayer(1);
    scene->AddChild(parent);
    m_generatedEntity = parent;
    m_elapsedTime=0.0f;
    //SetComplete();
}

void ShowMessage::Run(float dt) {
    m_elapsedTime+=dt;
    if (m_elapsedTime >= m_time) {

        SetComplete();
        if (m_generatedEntity != nullptr) {
            Engine::get().Remove(m_generatedEntity.get());
            m_generatedEntity = nullptr;
        }
    }

}
void ShowMessage::NotifySuspend(){
    SetComplete();
    if (m_generatedEntity != nullptr) {
        Engine::get().Remove(m_generatedEntity.get());
        m_generatedEntity = nullptr;
    }
}

ShowMessage::~ShowMessage() {
    if (m_generatedEntity != nullptr) {
        Engine::get().Remove(m_generatedEntity.get());
        m_generatedEntity = nullptr;
    }
}
