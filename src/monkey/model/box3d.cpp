#include "monkey/mesh3dfactory.h"

Box3D::Box3D(const ITable & t) {
	auto width = t.get<float>("width");
	auto height = t.get<float>("height");
	auto depth = t.get<float>("depth");

	float hw = width * 0.5f;
	float hh = height * 0.5f;
	float hd = depth * 0.5f;

	auto tex = t.get<std::string>("tex");

	auto tex_front = t.get<std::string>("tex_front", tex);
	glm::vec2 repeatFront = t.get<glm::vec2>("repeat_front", glm::vec2(1.0f, 1.0f));
	auto tex_right = t.get<std::string>("tex_right", tex);
	auto tex_back = t.get<std::string>("tex_back", tex);
	auto tex_left = t.get<std::string>("tex_left", tex);
	auto tex_top = t.get<std::string>("tex_top", tex);
	auto tex_bottom = t.get<std::string>("tex_bottom", tex);

	auto frontMesh = std::make_shared<TexturedMesh<Vertex3DN>>(TEXTURE_SHADER_LIGHT, GL_TRIANGLES, tex_front);
	std::vector<Vertex3DN> vertices;
	std::vector<unsigned int> indices;

	vertices.push_back( Vertex3DN (-hw, hh, -hd, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f));
	vertices.push_back( Vertex3DN (-hw, -hh, -hd, 0.0f, repeatFront.y, 0.0f, -1.0f, 0.0f));
	vertices.push_back( Vertex3DN (hw, -hh, -hd, repeatFront.x, repeatFront.y, 0.0f, -1.0f, 0.0f));
	vertices.push_back( Vertex3DN (hw, hh, -hd, repeatFront.x, 0.0f, 0.0f, -1.0f, 0.0f));
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(0);
	frontMesh->Init(vertices, indices);
	m_meshes.push_back(frontMesh);




}

void Box3D::Draw(Shader * shader) {
	for (const auto &m : m_meshes) {
		m->Draw(shader, 0, 0);
	}
}