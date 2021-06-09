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
}


void Road::Start() {
    // init mesh
    std::cerr << "qu]m";

    m_mesh = std::make_shared<DynamicMesh<VertexColor>>(COLOR_SHADER);
    m_mesh->m_primitive = GL_LINES;
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
	m_step = 0.01f;
	m_mesh->UpdateGeometry(vertices, indices);
}

void Road::Update(double dt) {
	std::vector<VertexColor> vertices;
	std::vector<unsigned> indices;
	float roadWidth = 2.0f;
	int n = 200;
	m_curvature += dt*m_step;
	if (fabs(m_curvature) > 0.01f) {
		m_step = -m_step;
	}
	for (int i = 0; i < n; ++i) {
		vertices.emplace_back(-roadWidth+i*i*m_curvature, 0.0f, -i);
		vertices.emplace_back(roadWidth+i*i*m_curvature, 0.0f, -i);
	}
	for (int i = 0; i < n; ++i) {
		indices.push_back(i);
		indices.push_back(i+2);
		indices.push_back(i+1);
		indices.push_back(i+3);
	}

	m_mesh->UpdateGeometry(vertices, indices);

}

