#include <gfx/factories.h>
#include <gfx/engine.h>
#include <gfx/quadmesh.h>
#include <gfx/components/renderer.h>
#include <gfx/components/parallax.h>
#include <gfx/model/basicmodel.h>

std::shared_ptr<Entity> ParallaxBackgroundFactory::Create(luabridge::LuaRef &ref) {

    LuaTable table(ref);

    glm::vec2 range = table.Get<glm::vec2>("range");
    float factor = table.Get<float>("factor");
    glm::vec2 deviceSize = Engine::get().GetDeviceSize();

    int left = table.Get<int>("left", 0);
    if (left == 1) {
        range.x = 0.5f*deviceSize.x - deviceSize.x / factor;
    }
    float height = table.Get<float>("height");
    float z = table.Get<float>("z");
    std::string img = table.Get<std::string>("image");
    auto tex = Engine::get().GetAssetManager().GetTex(img);
    int texWidth = tex->GetWidth();
    int texHeight = tex->GetHeight();
    float imgAspectRatio = static_cast<float>(texWidth)/texHeight;

    // as a first step, we create a renderer
    auto renderer = Ref::Create<Renderer>();
    float quadWidth = (range[1] - range[0]) * (1.0f - factor);
    float panelAspectRatio = quadWidth / height;

    std::shared_ptr<IMesh> mesh = std::make_shared<QuadMesh>(img, quadWidth, height, panelAspectRatio/imgAspectRatio, 1.0f);

    renderer->SetModel(std::make_shared<BasicModel>(mesh));

    auto entity = Ref::Create<Entity>();


    auto parallax = Ref::Create<Parallax>("maincam", factor, range[0], range[1]);
    entity->AddComponent(renderer);
    entity->AddComponent(parallax);
    entity->SetPosition(glm::vec3(range.x + 0.5f*deviceSize.x, deviceSize.y - height, z));
    return entity;
}