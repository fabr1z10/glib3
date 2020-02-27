#include <monkey/components/light.h>
#include <monkey/shader/lightshader.h>
#include <monkey/engine.h>

void Light::Start() {
    Engine::get().GetRenderingEngine()->AddLight(this);
}

Light::~Light() {
    Engine::get().GetRenderingEngine()->RemoveLight(this);
}

DirectionalLight::DirectionalLight(const DirectionalLight & orig) : Light(orig) {
    m_direction = orig.m_direction;
    m_ambient = orig.m_ambient;
    m_diffuse = orig.m_diffuse;
}

DirectionalLight::DirectionalLight(const LuaTable & t) : Light(t) {
    m_ambient = t.Get<glm::vec3>("ambient");
    m_ambient /= 255.0f;
    m_diffuse = t.Get<glm::vec3>("diffuse");
    m_diffuse /= 255.0f;
    m_direction = t.Get<glm::vec3>("direction");
}


std::shared_ptr<Component> DirectionalLight::clone() const {
    return std::make_shared<DirectionalLight>(DirectionalLight(*this));
}


void DirectionalLight::setUp(LightShader* s) {
    s->setDirectionalLight(m_direction, m_ambient, m_diffuse);

}
