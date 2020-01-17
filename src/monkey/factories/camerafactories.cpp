#include <monkey/factories.h>
#include <monkey/engine.h>

std::shared_ptr<Camera> OrthoCamFactory::Create(luabridge::LuaRef &ref) {


    LuaTable tcam(ref);
    std::string tag = tcam.Get<std::string>("tag", "");
    std::cout << "create cam " << tag << "\n";
    glm::vec3 pos = tcam.Get<glm::vec3>("pos", glm::vec3(0.0f));
    glm::vec3 direction = tcam.Get<glm::vec3>("direction", glm::vec3(0, 0, -1));
    glm::vec3 up = tcam.Get<glm::vec3>("up", glm::vec3(0, 1, 0));
    glm::vec4 viewport = tcam.Get<glm::vec4>("viewport", glm::vec4(0.0f, 0.0f, Engine::get().GetDeviceSize()));

    glm::vec2 size = tcam.Get<glm::vec2>("size");
    glm::vec4 bounds = tcam.Get<glm::vec4>("bounds", glm::vec4(0.0));
    //std::unique_ptr<Camera> camera = std::unique_ptr<OrthographicCamera>(new OrthographicCamera(size.x, size.y, viewport));
    auto camera = std::make_shared<OrthographicCamera>(size.x, size.y, viewport);

    if (bounds != glm::vec4(0.0f)) {
        camera->SetBounds(bounds[0], bounds[2], bounds[1], bounds[3]);
    }
    camera->SetPosition(pos, direction, up);
    if (!tag.empty()) {
        camera->SetTag(tag);
    }
    return camera;
}

std::shared_ptr<Camera> PerspectiveCamFactory::Create(luabridge::LuaRef &ref) {
    LuaTable tcam(ref);
    std::string tag = tcam.Get<std::string>("tag", "");
    glm::vec3 pos = tcam.Get<glm::vec3>("pos", glm::vec3(0.0f));
    glm::vec3 direction = tcam.Get<glm::vec3>("direction", glm::vec3(0, 0, -1));
    glm::vec3 up = tcam.Get<glm::vec3>("up", glm::vec3(0, 1, 0));
    glm::vec4 viewport = tcam.Get<glm::vec4>("viewport", glm::vec4(0.0f, 0.0f, Engine::get().GetDeviceSize()));

    // get field of view
    float fov = tcam.Get<float>("fov", 45.0f);
    float near = tcam.Get<float>("near", 0.05f);
    float far = tcam.Get<float>("far", 1000.0f);
    auto camera = std::make_shared<PerspectiveCamera>(viewport, fov, near, far);
    camera->SetPosition(pos, direction, up);
    if (!tag.empty())
        camera->SetTag(tag);
    return std::move(camera);
}
