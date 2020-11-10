#pragma once

#include <monkey/components/renderer.h>
#include <monkey/skeletal/skmodel.hpp>


class SkRend : public Renderer {
public:
	// requires a skmodel
	SkRend (SkModel*, std::shared_ptr<Mesh<VertexSkeletalColor>> mesh);
	void SetModel(std::shared_ptr<IModel> mesh) override;

	void Draw(Shader*) override;
	void Start() override;

	std::type_index GetType() override;
	ShaderType GetShaderType() const override;
private:
	SkModel* m_model;
	std::shared_ptr<Mesh<VertexSkeletalColor> > m_mesh;

};