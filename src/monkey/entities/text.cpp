#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <monkey/entities/text.h>

#include <monkey/engine.h>

#include <monkey/components/spriterenderer.h>
#include <monkey/textmesh.h>
#include <monkey/model/textmodel.h>
#include <monkey/components/basicrenderer.h>

Text::Text(const ITable & t) : Entity(t) {

    auto text = t.get<std::string>("text");
    auto font = t.get<std::string>("font");
    auto size = t.get<float>("size", 8);
    auto align = t.get<int>("align", TextAlignment::TOP_LEFT);
    auto maxWidth = t.get<float>("maxwidth", 0.0f);
    auto color = t.get<glm::vec4>("color", glm::vec4(255.0f));
    color /= 255.0f;

    Font* f = Engine::get().GetAssetManager().GetFont(font).get();

    auto mesh = std::make_shared<TextMesh>(f, text, size, static_cast<TextAlignment >(align), maxWidth);

    glm::vec2 offset = mesh->getOffset();
    auto model = std::make_shared<TextModel>(mesh);
    auto renderer = std::make_shared<BasicRenderer>(model);
    renderer->setMultColor(color);

    //MoveLocal(glm::vec3(offset, 0.0f));

    this->AddComponent(renderer);

    renderer->SetTransform(glm::translate(glm::vec3(offset, 0.0f)));
}