#include "road.h"
#include <GLFW/glfw3.h>
#include <monkey/scheduler.h>

#include <monkey/engine.h>
#include <iostream>
#include <monkey/math/algo/closest.h>
#include <monkey/math/algo/shortestpath.h>
#include <monkey/properties.h>
#include <monkey/meshfactory.h>
#include <monkey/components/basicrenderer.h>

//WalkArea::WalkArea(std::shared_ptr<IShape> shape, int priority) : ScriptHotSpot(shape, priority) {}

Road::Road(const ITab& t) : Component(t) {

	m_n = 10;
	m_s = 0.0f;
	m_d0 = 5.0f;
	m_step = m_d0 / m_n;

}


void Road::Start() {
    // init mesh
    std::cerr << "qu]m";

    m_speed = 0.0f;
	m_acceleration= 10.0f;

	m_input = m_entity->GetComponent<InputMethod>();
	if (m_input == nullptr) {
		GLIB_FAIL("Road requires an <InputMethod> component!");
	}
	m_cam = Monkey::get().Get<Camera>("maincam");

    m_mesh = std::make_shared<DynamicMesh<VertexColor>>(COLOR_SHADER);
    m_mesh->m_primitive = GL_TRIANGLES;
    //m_entity->AddComponent(std::make_shared<BasicRenderer>())
    auto model = std::make_shared<BasicModel>(m_mesh);
	auto renderer = std::make_shared<BasicRenderer>(model);
	m_entity->AddComponent(renderer);
	std::vector<VertexColor> vertices;
	std::vector<unsigned> indices;
	float roadWidth = 2.0f;
	int n = 200;
	for (int i = 0; i < n; ++i) {
		vertices.emplace_back(-roadWidth, 0.0f, -i);
		vertices.emplace_back(roadWidth, 0.0f, -i);
	}
	for (int i = 0; i < n; ++i) {
		indices.push_back(i);
		indices.push_back(i+2);
		indices.push_back(i+1);
		indices.push_back(i+3);
	}
	m_curvature=0.0f;
	//m_step = 0.01f;
	//m_mesh->UpdateGeometry(vertices, indices);
}

void Road::Update(double dt) {

	if (m_input->isKeyDown(GLFW_KEY_UP)) {
		m_speed += m_acceleration * dt;
	} else if (m_input->isKeyDown(GLFW_KEY_DOWN)) {
		m_speed -= m_acceleration * dt;
		m_speed = std::max(0.0f, m_speed);
	}
	if (m_input->isKeyDown(GLFW_KEY_LEFT)) {
		auto pos = m_cam->GetPosition();
		pos.x -= 0.2f*m_speed*dt;
		m_cam->SetPosition(pos, glm::vec3(0,0,-1), glm::vec3(0,1,0));
	} else if (m_input->isKeyDown(GLFW_KEY_RIGHT)) {
		auto pos = m_cam->GetPosition();
		pos.x += 0.2f*m_speed*dt;
		m_cam->SetPosition(pos, glm::vec3(0,0,-1), glm::vec3(0,1,0));

	}

//	bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
//	bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
//	bool up = ;
//	bool down = m_input->isKeyDown(GLFW_KEY_DOWN);
	m_s+=dt*m_speed;
	long is = int(m_s/m_step);

	size_t current_color = int(is/(m_n-1)) % 2;

	float s0 = int(m_s / m_step) * m_step;
	float z0 = m_s - s0;

	std::vector<VertexColor> vertices;
	std::vector<unsigned> indices;
	int n{200};
	float roadWidth{2.0f};
	std::array<glm::vec4, 2> colors = { glm::vec4(0.64, 0.64, 0.64, 1.0f), glm::vec4(0.32,0.32f,0.32f,1.0)};

	vertices.emplace_back(-roadWidth, 0.0f, z0, colors[current_color]);
	vertices.emplace_back(roadWidth, 0.0f, z0, colors[current_color]);
	unsigned k = 0;
	for (int i = 0; i < n; ++i) {
		is += 1;
		// junction point. color changing here we need to add the start
		bool jp = (is % (m_n - 1)) == 0;
		vertices.emplace_back(-roadWidth, 0.0f, z0-(i+1)*m_step, colors[current_color]);
		vertices.emplace_back(roadWidth, 0.0f, z0-(i+1)*m_step, colors[current_color]);
		indices.push_back(k);
		indices.push_back(k+1);
		indices.push_back(k+2);
		indices.push_back(k+3);
		indices.push_back(k+2);
		indices.push_back(k+1);
		k += 2;
		if (jp) {
			current_color = (current_color + 1) % 2;
			vertices.emplace_back(-roadWidth, 0.0f, z0-(i+1)*m_step, colors[current_color]);
			vertices.emplace_back(roadWidth, 0.0f, z0-(i+1)*m_step, colors[current_color]);
			k += 2;
		}
	}

//	std::vector<VertexColor> vertices;
//	std::vector<unsigned> indices;
//	int n = 200;
//	m_curvature += dt*m_step;
//	if (fabs(m_curvature) > 0.01f) {
//		m_step = -m_step;
//	}
//	for (int i = 0; i < n; ++i) {
//		vertices.emplace_back(-roadWidth+i*i*m_curvature, 0.0f, -i);
//		vertices.emplace_back(roadWidth+i*i*m_curvature, 0.0f, -i);
//	}
//	for (int i = 0; i < n; ++i) {
//		indices.push_back(i);
//		indices.push_back(i+2);
//		indices.push_back(i+1);
//		indices.push_back(i+3);
//	}
//
	m_mesh->UpdateGeometry(vertices, indices);

}

