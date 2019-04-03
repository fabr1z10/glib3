#include <gfx/factories.h>
#include <gfx/engine.h>

std::unique_ptr<Camera> OrthoCamFactory::Create(luabridge::LuaRef &ref) {


//    LuaTable tcam(ref);
//    std::string tag = tcam.Get<std::string>("tag", "");
//    glm::vec3 pos = tcam.Get<glm::vec3>("pos", glm::vec3(0.0f));
//    glm::vec3 direction = tcam.Get<glm::vec3>("direction", glm::vec3(0, 0, -1));
//    glm::vec3 up = tcam.Get<glm::vec3>("up", glm::vec3(0, 1, 0));
//    glm::vec4 viewport = tcam.Get<glm::vec4>("viewport", glm::vec4(0.0f, 0.0f, Engine::get().GetDeviceSize()));
//
//    glm::vec2 size = tcam.Get<glm::vec2>("size");
//    glm::vec4 bounds = tcam.Get<glm::vec4>("bounds", glm::vec4(0.0));
    //std::unique_ptr<Camera> camera = std::unique_ptr<OrthographicCamera>(new OrthographicCamera(size.x, size.y, viewport));
    std::unique_ptr<Camera> camera = std::unique_ptr<Camera>(new OrthographicCamera(10,10));

//    if (bounds != glm::vec4(0.0f)) {
//        static_cast<OrthographicCamera*>(camera.get())->SetBounds(bounds[0], bounds[2], bounds[1], bounds[3]);
//    }
//    camera->SetPosition(pos, direction, up);
//    if (!tag.empty())
//        camera->SetTag(tag);
//    //std::unique_ptr<Camera> ciccio = std::move(camera);
    //std::cout << "making2 ..." << tag << camera->GetPosition().x << "\n";
    std::cout << "ciaociaoqui\n";
    return camera;
}

std::unique_ptr<Camera> PerspectiveCamFactory::Create(luabridge::LuaRef &ref) {
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
    auto camera = std::unique_ptr<PerspectiveCamera>(new PerspectiveCamera(viewport, fov, near, far));
    camera->SetPosition(pos, direction, up);
    if (!tag.empty())
        camera->SetTag(tag);
    return std::move(camera);
}
