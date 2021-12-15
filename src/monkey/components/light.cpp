#include <monkey/components/light.h>
//#include <monkey/shader/lightshader.h>
#include <monkey/engine.h>

void Light::Start() {
    Engine::get().GetRenderingEngine()->AddLight(this);

}

Light::~Light() {
    Engine::get().GetRenderingEngine()->RemoveLight(this);
}

DirectionalLight::DirectionalLight(const ITab & t) {
	m_direction = glm::normalize(t.get<glm::vec3>("direction"));
	m_ambient = t.get<glm::vec4>("ambient");
	m_diffuse = t.get<glm::vec4>("diffuse");
}



void DirectionalLight::setUp(Shader* s) {

    s->setVec3("lightDir", m_direction);
    s->setVec4("ambient", m_ambient);
    s->setVec4("diffuse", m_diffuse);



}
