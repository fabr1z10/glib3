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

	m_n = 2;
	m_s = 0.0f;
	m_d0 = 5.0f;
	m_step = m_d0 / m_n;
	m_z0 = 0.0f;
}


void Road::Start() {
    // init mesh
    m_oldy = 0.0f;
    std::cerr << "qu]m";
	m_oldis = -10;
	m_oldy = 0.0f;
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
	m_initialSlope=0.0f;
	// road 1
	m_roadInfo[-10] = std::make_pair(0, 0);
	m_roadInfo[50] = std::make_pair(0.01, 0);
	m_roadInfo[500] = std::make_pair(-0.01, 0.01f);
	m_roadInfo[900] = std::make_pair(0, 0);
	// end road 1
	//m_step = 0.01f;

	// road 2
//	m_roadInfo[-10] = std::make_pair(0, 0);
//	m_roadInfo[50] = std::make_pair(0, 0.01f);
//	m_roadInfo[200] = std::make_pair(0, 0.0f);
//	m_roadInfo[300] = std::make_pair(0, 0.01f);
//	m_roadInfo[400] = std::make_pair(0, -0.01f);
//	m_roadInfo[500] = std::make_pair(0, 0.01f);
//	m_roadInfo[800] = std::make_pair(0, 0.01f);
//	m_roadInfo[1000] = std::make_pair(0, 0.0f);
//	m_roadInfo[10000] = std::make_pair(0, 0.0f);
	// end road 2
//	m_roadInfo[500] = std::make_pair(0, -0.01f);
//	m_roadInfo[600] = std::make_pair(0, 0.01f);
//	m_roadInfo[700] = std::make_pair(0, -0.01f);
//	m_roadInfo[800] = std::make_pair(0, 0.01f);
//	m_roadInfo[500] = std::make_pair(-0.000001, 0);
//	m_roadInfo[900] = std::make_pair(0, 0);
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


	m_s += dt*m_speed;

	float s0 = m_s - m_z0;

	long is = int(s0 / m_step);
	size_t current_color = int(is/(m_n-1)) % 2;

	// length of first poly
	float lambda0 = m_step - (s0 - is * m_step);

	std::vector<VertexColor> vertices;
	std::vector<unsigned> indices;
	int n{200};
	float roadWidth{2.0f};
	std::array<glm::vec4, 2> colors = { glm::vec4(0.64, 0.64, 0.64, 1.0f), glm::vec4(0.32,0.32f,0.32f,1.0)};

	unsigned k = 0;

	auto currentRoadInfo = m_roadInfo.upper_bound(s0);
	float next_change = currentRoadInfo->first;
	currentRoadInfo--;
	float curvature = currentRoadInfo->second.first;
	float slope = currentRoadInfo->second.second;
	currentRoadInfo++;
//	float s = s0;
//	int ic = 0;

	// road center, and deltaz
//	if (is > m_oldis) {
//		m_oldis = is;
//		m_initialSlope = slope;
//	}
	float rx = 0.0f;
	float ry = 0.0f;//slope * fabs(z0);
	float dz = 0.0f;
	float dy = 0.0f;



	vertices.emplace_back(-roadWidth, ry, m_z0, colors[current_color]);
	vertices.emplace_back(roadWidth, ry, m_z0, colors[current_color]);

	float z = m_z0;
	float s = s0;
	for (int i = 0; i < n; ++i) {
		is += 1;
		// junction point. color changing here we need to add the start
		bool jp = (is % (m_n - 1)) == 0;
		//auto j = ic*ic;
		if (s > next_change) {
			curvature = currentRoadInfo->second.first;
			slope = currentRoadInfo->second.second;
			currentRoadInfo++;
			next_change = currentRoadInfo->first;
		}
		// update delta z
		float step = (i == 0 ? lambda0 : m_step);
		s += step;
		dz += step * curvature;
		dy += slope * step;
		rx += dz;
		ry += dy;
		z -= step;
		vertices.emplace_back(rx - roadWidth, ry, z, colors[current_color]);
		vertices.emplace_back(rx + roadWidth, ry, z, colors[current_color]);
		indices.push_back(k);
		indices.push_back(k+1);
		indices.push_back(k+2);
		indices.push_back(k+3);
		indices.push_back(k+2);
		indices.push_back(k+1);
		k += 2;
		if (jp) {
			current_color = (current_color + 1) % 2;
			vertices.emplace_back(rx - roadWidth , ry, z, colors[current_color]);
			vertices.emplace_back(rx + roadWidth , ry, z, colors[current_color]);
			k += 2;
		}
		//ic++;
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

