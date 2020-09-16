#include <monkey/model/basicmodel.h>
#include <monkey/components/basicrenderer.h>
#include <monkey/skeletal/skrenderer.hpp>
#include <monkey/skeletal/skrend.h>
#include <monkey/model/boxedmodel.h>
#include <monkey/skeletal/skanimator.hpp>
#include "monkey/skeletal/skcoll.h"
#include "monkey/skeletal/skmodel.hpp"
#include "monkey/math/geom.h"
#include "monkey/components/renderer.h"

SkColl::SkColl(const SkColl & other) : ICollider(other) {

}


void SkColl::Start() {
	// a sk collider requires a model
	m_renderer = m_entity->GetComponent<Renderer>();
	auto anim = dynamic_cast<SkAnimator*>(m_entity->GetComponent<IAnimator>());
	m_model = dynamic_cast<SkModel*>(anim->getModel());
	std::vector<glm::vec2> points = computePoints(m_P0, m_P1);
	m_polygon = std::make_shared<Polygon>(points);
	ICollider::Start();
	auto c = std::make_shared<Entity>();
	auto mesh = std::make_shared<Mesh<VertexSkeletalColor>>(SKELETAL_SHADER_COLOR);
	mesh->m_primitive = GL_LINE_LOOP;

	std::vector<VertexSkeletalColor> vertices;
	std::vector<unsigned> indices;
	auto pts = m_polygon->getPoints();
	size_t nw1 = weights1.size();
	size_t nw0 = weights0.size();
	vertices.emplace_back( VertexSkeletalColor {pts[0].x, pts[0].y, 2.0f, 1.0f, 1.0f, 1.0f,
		jointIds1[0], nw1>1? jointIds1[1] : 0, nw1>2 ? jointIds1[2] : 0,
		weights1[0], nw1>1? weights1[1] : 0, nw1>2 ? weights1[2] : 0});
	vertices.emplace_back( VertexSkeletalColor {pts[1].x, pts[1].y, 2.0f, 1.0f, 1.0f, 1.0f,
		jointIds0[0], nw0>1? jointIds0[1] : 0, nw0>2 ? jointIds0[2] : 0,
		weights0[0], nw0>1? weights0[1] : 0, nw0>2 ? weights0[2] : 0});
	vertices.emplace_back( VertexSkeletalColor {pts[2].x, pts[2].y, 2.0f, 1.0f, 1.0f, 1.0f,
		jointIds0[0], nw0>1? jointIds0[1] : 0, nw0>2 ? jointIds0[2] : 0,
		weights0[0], nw0>1? weights0[1] : 0, nw0>2 ? weights0[2] : 0});
	vertices.emplace_back( VertexSkeletalColor {pts[3].x, pts[3].y, 2.0f, 1.0f, 1.0f, 1.0f,
		jointIds1[0], nw1>1? jointIds1[1] : 0, nw1>2 ? jointIds1[2] : 0,
		weights1[0], nw1>1? weights1[1] : 0, nw1>2 ? weights1[2] : 0});
	indices.emplace_back(0);
	indices.emplace_back(1);
	indices.emplace_back(2);
	indices.emplace_back(3);
	mesh->Init(vertices, indices);
	//auto model = std::make_shared<BasicModel>(mesh);
	auto renderer = std::make_shared<SkRend>(m_model, mesh);
	m_debugRend = renderer.get();
	c->AddComponent(renderer);
	m_entity->AddChild(c);

}


std::vector<glm::vec2> SkColl::computePoints(glm::vec2 p0, glm::vec2 p1) {
	glm::vec2 dir = glm::normalize(Perp(p1 - p0));
	std::vector<glm::vec2> points;
	points.emplace_back( p0 + dir * m_width);
	points.emplace_back( p1 + dir * m_width);
	points.emplace_back( p1 - dir * m_width);
	points.emplace_back( p0 - dir * m_width);
	return points;
}

SkColl::SkColl(const ITable & table) : ICollider() {
	m_tag = table.get<int>("tag");
	m_flag = table.get<int>("flag");
	m_mask = table.get<int>("mask");
	m_width = table.get<float>("width");

	m_P0 = table.get<glm::vec2>("P0");
	jointIds0 = table.get<std::vector<int>>("j0");
	weights0 = table.get<std::vector<float>>("w0");

	m_P1 = table.get<glm::vec2>("P1");
	jointIds1 = table.get<std::vector<int>>("j1");
	weights1 = table.get<std::vector<float>>("w1");
}

std::shared_ptr<Component> SkColl::clone() const {
	return std::make_shared<SkColl>(*this);
}


void SkColl::Update(double dt) {
	// get the current trnasnforms
	glm::mat4 rt = m_renderer->GetTransform();
	glm::vec2 offset (rt[3][0], rt[3][1]);
	m_offset = glm::vec3(offset, 0.0f);
	auto jointTransforms = m_model->getJointTransforms();
	glm::vec4 a0;
	glm::vec4 a1;
	for (size_t i = 0; i < jointIds0.size(); ++i) {
		a0 += weights0[i] * jointTransforms[jointIds0[i]] * glm::vec4(m_P0+offset, 0.0f, 1.0f);
	}
	for (size_t i = 0; i < jointIds1.size(); ++i) {
		a1 += weights1[i] * jointTransforms[jointIds1[i]] * glm::vec4(m_P1+offset, 0.0f, 1.0f);
	}

	m_debugRend->SetTransform(rt);
	glm::vec2 p0(a0);
	glm::vec2 p1(a1);
	std::vector<glm::vec2> points = computePoints(p0, p1);
	m_polygon->setPoints(points);
	// notify engine
	m_engine->Move(this);
}

Shape * SkColl::GetShape() {

	return m_polygon.get();
}

std::type_index SkColl::GetType() {
	return std::type_index(typeid(ICollider));
}


Bounds SkColl::GetStaticBoundsI() const {
	Bounds b =  m_polygon->getBounds();
	b.min += m_offset;
	b.max += m_offset;
	return b;
}

Bounds SkColl::GetDynamicBoundsI() const {
	Bounds b =m_polygon->getBounds();
	b.min += m_offset;
	b.max += m_offset;
	return b;
}