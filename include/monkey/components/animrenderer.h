#pragma once

#include <monkey/components/renderer.h>
#include <monkey/model/basicmodel.h>

class AnimRenderer : public Renderer {
public:
	AnimRenderer (const ITable&);
	void Draw(Shader*) override;
	void Start() override;
	void Update(double) override;

	std::type_index GetType() override;
	void SetModel(std::shared_ptr<IModel> mesh) override {}

private:
	glm::vec2 m_basePosition;
	struct Frame {
		std::shared_ptr<BasicModel> model;
		float duration;
		glm::vec2 displacement;
	};
	std::vector<Frame> m_frames;
	float m_time;
	int m_frame;

};