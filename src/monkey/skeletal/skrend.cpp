#include <monkey/skeletal/skrend.h>
#include <glm/gtc/type_ptr.hpp>
#include <monkey/components/ianimator.h>

SkRend::SkRend(SkModel* model, std::shared_ptr<Mesh<VertexSkeletalColor>> mesh) {
	m_model = model;
	m_mesh = mesh;
}

void SkRend::SetModel(std::shared_ptr<IModel> model) {
	m_model = dynamic_cast<SkModel*>(model.get());
	m_baseModel = model.get();
}


void SkRend::Start() {
	m_forceZ=true;
	m_forcedZ = -0.5;

}

void SkRend::Draw(Shader * shader) {
	Renderer::Draw(shader);
	// we need to send the bone transforms to the shader
	auto boneId = shader->GetUniformLocation(BONES);

	auto jointTransforms = m_model->getJointTransforms();

	glUniformMatrix4fv(boneId, jointTransforms.size(), GL_FALSE, glm::value_ptr(jointTransforms[0]));

	m_mesh->Draw(shader,0,0);

}


ShaderType SkRend::GetShaderType() const {
	return SKELETAL_SHADER_COLOR;
}


std::type_index SkRend::GetType() {
	return std::type_index(typeid(Renderer));
}
