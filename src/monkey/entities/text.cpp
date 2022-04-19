#include <glm/gtx/transform.hpp>
#include <monkey/entities/text.h>

#include <monkey/engine.h>

//#include <monkey/components/spriterenderer.h>
#include <monkey/textmesh.h>
#include <monkey/model/textmodel.h>
#include <monkey/components/renderer.h>
#include <monkey/model/shadowtext.h>

Text::Text(const std::string & text, const std::string &font, float size, TextAlignment align, glm::vec4 color, glm::vec2 pos) {
    SetPosition(pos);
    Font* f = Engine::get().GetAssetManager().get<Font>(font).get();
    auto model = std::make_shared<TextModel>(f, size, static_cast<TextAlignment >(align), color, 0.0f);
    model->setText(text);
    glm::vec2 offset = model->getOffset();
    //auto model = std::make_shared<TextModel>(mesh);
    auto renderer = std::make_shared<Renderer>(model);
    renderer->setMultColor(color);

    //MoveLocal(glm::vec3(offset, 0.0f));

    this->AddComponent(renderer);

    renderer->SetTransform(glm::translate(glm::vec3(offset, 0.0f)));
}


Text::Text(const ITab& t) : Entity(t) {

    auto text = t.get<std::string>("text");
    auto font = t.get<std::string>("font");
    auto size = t.get<float>("size", 8);
    auto align = t.get<int>("align", TextAlignment::TOP_LEFT);
    auto maxWidth = t.get<float>("maxwidth", 0.0f);
    auto color = t.get<glm::vec4>("color", glm::vec4(1.0));

    auto textMode = t.get<int>("mode", 0);

    //color /= 255.0f;

    Font* f = Engine::get().GetAssetManager().get<Font>(font).get();

    std::shared_ptr<TextModel> model;
    switch (textMode) {
        case 0:
            model = std::make_shared<TextModel>(f,  size, static_cast<TextAlignment >(align), color, maxWidth);
            break;
        case 1:
            auto shadeColor = t.get<glm::vec4>("shade_color");
            auto offset = t.get<glm::vec2>("shade_offset", glm::vec2(1.0f, -1.0f));
            model = std::make_shared<ShadowText>(f,  size, static_cast<TextAlignment >(align), color, shadeColor, offset, maxWidth);
            break;


    }


    model->setText(text);
    glm::vec2 offset = model->getOffset();
    //  auto model = std::make_shared<TextModel>(mesh);

    //auto renderer = std::make_shared<Renderer>(model);
    //renderer->setMultColor(color);

    //MoveLocal(glm::vec3(offset, 0.0f));
    auto renderer = model->makeRenderer(model);
    //renderer->setMultColor(color);
    this->AddComponent(renderer);

    renderer->SetTransform(glm::translate(glm::vec3(offset, 0.0f)));
}