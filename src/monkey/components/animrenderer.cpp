#include <monkey/components/animrenderer.h>
#include <monkey/quadmesh.h>


AnimRenderer::AnimRenderer(const ITab& t) : Renderer(t) {


	t.foreach("frames", [&] (const ITab& d) {
		Frame f;
		auto image = d.get<std::string>("image");
		f.displacement = d.get<glm::vec2>("disp");
		f.duration = d.get<float>("duration");
		auto mesh = std::make_shared<QuadMesh>(image);
		f.model = std::make_shared<BasicModel>(mesh);
		m_frames.push_back(f);
	});
	m_baseModel = m_frames.front().model.get();
}


void AnimRenderer::Start() {
	m_time = 0;
	m_frame = 0;
	//m_basePosition = m_entity->GetPosition();
	glm::vec2 pos = -m_frames.front().displacement;
	m_renderingTransform[3][0] = pos.x;
	m_renderingTransform[3][1] = pos.y;

	//m_entity->SetPosition(pos);
}

void AnimRenderer::Update(double dt) {
	m_time += dt;
	if (m_time >= m_frames[m_frame].duration) {
		// advance frame
		m_time = m_frames[m_frame].duration - m_time;
		m_frame++;
		if (m_frame >= m_frames.size()) {
			m_frame = 0;
		}
		//glm::vec2 pos = m_basePosition - m_frames[m_frame].displacement;
		//m_entity->SetPosition(pos);
		glm::vec2 pos = -m_frames[m_frame].displacement;
		m_renderingTransform[3][0] = pos.x;
		m_renderingTransform[3][1] = pos.y;

	}
}

void AnimRenderer::Draw(Shader * shader) {
	Renderer::Draw(shader);
	m_frames[m_frame].model->Draw(shader);

}

std::type_index AnimRenderer::GetType() {
	return std::type_index(typeid(Renderer));
}
