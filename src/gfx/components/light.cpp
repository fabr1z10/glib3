#include <gfx/components/light.h>
#include <gfx/shader.h>
#include <gfx/engine.h>

void Light::Start() {
    Engine::get().GetRenderingEngine()->AddLight(this);
}

void AmbientLight::setUp(Shader* s) {

    auto loc = s->GetUniformLocation(AMBIENT);
    glUniform3fv(loc, 1, &m_color[0]);
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