#pragma once

#include <monkey/components/renderer.h>

class ShadowRenderer : public Renderer {
public:
	//ShadowRenderer () {}
	ShadowRenderer(const ITab&);
	void Draw(Shader*) override;
	std::type_index GetType() override;
	void Start() override;
	//void setModel(std::shared_ptr<IModel> mesh) override {}
	void Update(double) override;
//	ShaderType GetShaderType() const override;

private:
	Renderer* m_parentRenderer;
	Entity* m_parent;
	glm::vec3 m_translate;
	float m_angle;
	float m_shear;
	float m_scaleLength;
};