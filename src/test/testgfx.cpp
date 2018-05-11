#include <test/testgfx.h>
#include <gfx/renderingengine.h>
#include <gfx/renderer.h>
#include <gfx/meshfactory.h>


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

std::shared_ptr<Entity> Factory2::Create() {

    auto entity = std::make_shared<Entity>();

    // create one node showing a square
    auto gfxNode = std::make_shared<Entity>();
    gfxNode->SetLayer(1);
    auto r1 = std::make_shared<Renderer>();
    r1->SetMesh(MeshFactory::CreateLineMesh(glm::vec2(), glm::vec2(100, 0), glm::vec4(255,0,0,255)));
    gfxNode->AddComponent(r1);
    entity->AddChild(gfxNode);




    // create engine node
    auto engineNode = std::make_shared<Entity>();

    auto renderingEngine = std::make_shared<RenderingEngine>();
    auto cam = std::unique_ptr<OrthographicCamera> (new OrthographicCamera(800, 600, 1));
    cam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    renderingEngine->AddCamera (std::move(cam));
    renderingEngine->AddShader(COLOR_SHADER);
    engineNode->AddComponent(renderingEngine);

    entity->AddChild(engineNode);

    return entity;

}