#include <monkey/components/shadowrenderer.h>
#include <monkey/entity.h>
#include <glm/gtx/transform.hpp>

ShadowRenderer::ShadowRenderer(const ITable& t) : Renderer(t) {

	m_angle = t.get<float>("angle", 0.0f);
	m_scaleLength = t.get<float>("scale_length", 1.0f);
}

void ShadowRenderer::Draw(Shader * shader) {

	m_parentRenderer->Draw(shader);
}

void ShadowRenderer::Update(double) {
	auto pos = m_parent->GetPosition();
	bool flipx = m_parent->GetFlipX();
	float scale = m_parent->GetScale();
	SetTransform(m_parentRenderer->GetTransform());
	m_entity->SetLocalTransform(
			glm::translate(glm::vec3(0.0f, -pos.y/scale, -pos.y/scale)) *
			glm::scale(glm::vec3(1.0f, m_scaleLength, 1.0f)) *
			glm::rotate(glm::radians<float>(m_angle*(flipx ? 1.0f : -1.0f)), glm::vec3(0.0f,1.0f,0.0f)) *
			glm::rotate(glm::radians<float>(-89.9f), glm::vec3(1.0f,0.0f,0.0f)));


}

ShaderType ShadowRenderer::GetShaderType() const {
	return m_parentRenderer->GetShaderType();
}


void ShadowRenderer::Start() {
	m_parent = m_entity->GetParent();
	m_parentRenderer = m_parent->GetComponent<Renderer>();
	//m_entity->SetPosition(glm::vec3(1/m_parent->GetScale(),0,0));
	m_multColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.5f);
}

std::type_index ShadowRenderer::GetType() {
	return std::type_index(typeid(Renderer));
}
