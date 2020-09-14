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

DirectionalLight::DirectionalLight(const ITable & t) {
	m_direction = t.get<glm::vec3>("direction");
	m_ambient = t.get<glm::vec4>("ambient");
	m_ambient /= 255.0f;
	m_diffuse = t.get<glm::vec4>("diffuse");
	m_diffuse /= 255.0f;
}

std::shared_ptr<Component> DirectionalLight::clone() const {
    return std::make_shared<DirectionalLight>(DirectionalLight(*this));
}


void DirectionalLight::setUp(Shader* s) {
	auto locDir = s->GetUniformLocation(ShaderUniform::LIGHTDIR);
	auto locAmb = s->GetUniformLocation(ShaderUniform::AMBIENT);
	auto locDif = s->GetUniformLocation(ShaderUniform::LIGHTCOLOR);
	glUniform3fv(locDir, 1, &m_direction[0]);
	glUniform4fv(locAmb, 1, &m_ambient[0]);
	glUniform4fv(locDif, 1, &m_diffuse[0]);

}
