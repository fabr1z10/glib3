#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <monkey/entities/text.h>

#include <monkey/lua/luatable.h>
#include <monkey/engine.h>

#include <monkey/components/spriterenderer.h>
#include <monkey/textmesh.h>
#include <monkey/model/textmodel.h>
#include <monkey/components/basicrenderer.h>

Text::Text(const LuaTable & t) : Entity(t) {

    auto text = t.Get<std::string>("text");
    auto font = t.Get<std::string>("font");
    auto size = t.Get<float>("size", 8);
    auto align = t.Get<TextAlignment>("align", TOP_LEFT);
    auto maxWidth = t.Get<float>("maxwidth", 0.0f);
    auto color = t.Get<glm::vec4>("color", glm::vec4(255.0f));
    color /= 255.0f;

    Font* f = Engine::get().GetAssetManager().GetFont(font).get();

    auto mesh = std::make_shared<TextMesh>(f, text, size, align, maxWidth);

    glm::vec2 offset = mesh->getOffset();
    auto model = std::make_shared<TextModel>(mesh);
    auto renderer = std::make_shared<BasicRenderer>(model);
    renderer->SetTint(color);

    //MoveLocal(glm::vec3(offset, 0.0f));

    this->AddComponent(renderer);

    renderer->SetTransform(glm::translate(glm::vec3(offset, 0.0f)));
}