#include <gfx/activities/showmessage.h>
#include <gfx/engine.h>
#include <gfx/entity.h>
#include <gfx/enums.h>
#include <gfx/textmesh.h>
#include <gfx/components/renderer.h>
#include <glm/gtx/transform.hpp>

void ShowMessage::Start() {
    m_mainCam = Engine::get().GetRef<OrthographicCamera>("maincam");
    auto scene = Engine::get().GetRef<Entity>("main");
    glm::vec2 currentPos;
    if (!m_actor.empty()) {
        auto actor = Engine::get().GetRef<Entity>(m_actor);
        currentPos = (actor->GetPosition());
    } else {
        currentPos = m_pos;
    }

    // make this a param
    currentPos += m_offset; //glm::vec2(0, 60.0);

    auto parent = std::make_shared<Entity>();
    Font* f = Engine::get().GetAssetManager().GetFont(m_font);
    auto mesh = std::make_shared<TextMesh>(f, m_message, m_size, m_align, 280.0f);
    glm::vec2 outlineOffsets[] = {{0, 0}, {-1, 0}, {-1,1}, {0, 1}, {1,1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    for (int i =0; i < 9; ++i) {
        auto entity = std::make_shared<Entity>();
        auto renderer = std::make_shared<Renderer>();
        renderer->SetMesh(mesh);
        entity->SetPosition(glm::vec3(outlineOffsets[i] * 0.5f, i == 0 ? 0 : -1));
        renderer->SetTint(i==0 ? m_color : m_outlineColor);
        //renderer->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
        entity->AddComponent(renderer);
        parent->AddChild(entity);
    }

    // adjust position

    Bounds textBounds = mesh->getBounds();
    glm::vec2 extents = textBounds.GetExtents();
    glm::vec2 displ(0.0f);
    glm::vec2 camPos(m_mainCam->GetPosition());
    glm::vec2 camSize = 0.5f * m_mainCam->GetSize();

    if (currentPos.x - extents[0] < camPos.x - camSize.x)
        displ.x = (camPos.x - camSize.x) - (currentPos.x - extents[0]);
    else if (currentPos.x + extents[0] > camPos.x + camSize.x)
        displ.x = -((currentPos.x + extents[0]) - (camPos.x + camSize.x));
    parent->SetPosition(glm::vec3(currentPos + displ, 5.0f));
    parent->SetLayer(1);
    scene->AddChild(parent);
    m_generatedEntity = parent.get();
    m_elapsedTime=0.0f;
    //SetComplete();
}

void ShowMessage::Run(float dt) {
    m_elapsedTime+=dt;
    if (m_elapsedTime >= m_time) {

        SetComplete();
        if (m_generatedEntity != nullptr) {
            Engine::get().Remove(m_generatedEntity);
            m_generatedEntity = nullptr;
        }
    }

}
void ShowMessage::NotifySuspend(){
    SetComplete();
    if (m_generatedEntity != nullptr) {
        Engine::get().Remove(m_generatedEntity);
        m_generatedEntity = nullptr;
    }
}

ShowMessage::~ShowMessage() {
    if (m_generatedEntity != nullptr) {
        Engine::get().Remove(m_generatedEntity);
        m_generatedEntity = nullptr;
    }
}
