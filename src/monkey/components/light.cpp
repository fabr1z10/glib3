#include <monkey/components/light.h>
#include <monkey/shader.h>
#include <monkey/engine.h>

void Light::Start() {
    Engine::get().GetRenderingEngine()->AddLight(this);
}

AmbientLight::AmbientLight(const AmbientLight& orig) :
Light(orig), m_color(orig.m_color) {
    
}

std::shared_ptr<Component> AmbientLight::clone() const {
    return std::make_shared<AmbientLight>(AmbientLight(*this));
}

void AmbientLight::setUp(Shader* s) {

    auto loc = s->GetUniformLocation(AMBIENT);
    glUniform3fv(loc, 1, &m_color[0]);
}

DirectionalLight::DirectionalLight (const DirectionalLight& orig) :
Light(orig), m_color(orig.m_color), m_direction(orig.m_direction) {
    
}

std::shared_ptr<Component> DirectionalLight::clone() const {
    return std::make_shared<DirectionalLight>(DirectionalLight(*this));
}


DirectionalLight::DirectionalLight (glm::vec3 direction, glm::vec3 color) : Light(), m_color(color) {
    m_direction = glm::normalize(direction);
}

void DirectionalLight::setUp(Shader* s) {

    auto locDir = s->GetUniformLocation(LIGHTDIR);
    auto locCol = s->GetUniformLocation(LIGHTCOLOR);
    glUniform3fv(locDir, 1, &m_direction[0]);
    glUniform3fv(locCol, 1, &m_color[0]);

}
