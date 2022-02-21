#include <monkey/components/shadowrenderer.h>
#include <monkey/entity.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/transform2.hpp>

ShadowRenderer::ShadowRenderer(const ITab& t) : Renderer(t) {

	m_angle = t.get<float>("angle", 0.0f);
	m_scaleLength = t.get<float>("scale_length", 1.0f);
	m_translate = t.get<glm::vec3>("translate", glm::vec3(0.0f));
	m_shear = t.get<float>("shear", 0.0f);
	m_multColor = glm::vec4(1.0f, 0.0f, 0.0f, 0.5f);
}

void ShadowRenderer::Draw(Shader * shader) {
	m_parentRenderer->Draw(shader);
}

void ShadowRenderer::Update(double) {
	auto pos = m_parent->GetPosition();
	bool flipx = m_parent->GetFlipX();
	float scale = m_parent->GetScale();
	SetTransform(m_parentRenderer->GetTransform());
	//m_entity->SetLocalTransform(glm::translate(glm::vec3(20.0f, 0.0f, 0.0f)));
	//m_entity->SetLocalTransform(glm::rotate(glm::radians<float>(-89.9f), glm::vec3(1.0f, 0.0f, 0.0f)));
	//auto m =glm::shearX3D(glm::mat4(1.0f), m_shear, 0.0f);
	//m_entity->SetLocalTransform(m);
	auto m = glm::mat4(1.0f);
	m[1][0] = (m_parent->GetFlipX() ? -1 : 1) * m_shear;
	m[1][1] = m_scaleLength;
	m[3][2] = -1.0f;
	m_entity->SetLocalTransform(m);//glm::translate(glm::vec3(10.0f, 0.0f, 0.0f)));
	//		m*
	//		glm::translate(m_translate));
	//*
	//		glm::scale(glm::vec3(1.0f, m_scaleLength, 1.0f)) *
	//		glm::rotate(glm::radians<float>(m_angle*(flipx ? 1.0f : -1.0f)), glm::vec3(0.0f,1.0f,0.0f)) *
	//		glm::rotate(glm::radians<float>(-89.9f), glm::vec3(1.0f,0.0f,0.0f)));


}

//ShaderType ShadowRenderer::GetShaderType() const {
//	return m_parentRenderer->GetShaderType();
//}


void ShadowRenderer::Start() {
	m_parent = m_entity->GetParent();
	m_parentRenderer = m_parent->GetComponent<Renderer>();
	//m_entity->SetPosition(glm::vec3(1/m_parent->GetScale(),0,0));
	m_multColor = glm::vec4(0.0f, 0.0f, 0.0f, 0.5f);
}

std::type_index ShadowRenderer::GetType() {
	return std::type_index(typeid(Renderer));
}
