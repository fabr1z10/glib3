#include <test/testgfx.h>
#include <gfx/renderingengine.h>

std::shared_ptr<Entity> Factory1::Create() {

    auto entity = std::make_shared<Entity>();

    // create engine node
    auto engineNode = std::make_shared<Entity>();

    auto renderingEngine = std::make_shared<RenderingEngine>();
    renderingEngine->AddCamera (std::unique_ptr<OrthographicCamera> (new OrthographicCamera(320, 200, 1)));
    renderingEngine->AddShader(TEXTURE_SHADER);
    engineNode->AddComponent(renderingEngine);

    entity->AddChild(engineNode);

    return entity;

}