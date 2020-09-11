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


std::shared_ptr<Component> DirectionalLight::clone() const {
    return std::make_shared<DirectionalLight>(DirectionalLight(*this));
}


void DirectionalLight::setUp(Shader* s) {
	glUniform3fv(s->GetUniformLocation(ShaderUniform::LIGHTDIR), 1, &m_direction[0]);
	glUniform4fv(s->GetUniformLocation(ShaderUniform::AMBIENT), 1, &m_ambient[0]);
	glUniform4fv(s->GetUniformLocation(ShaderUniform::LIGHTCOLOR), 1, &m_diffuse[0]);

}
