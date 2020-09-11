#include "monkey/polymesh.h"

Plane3D::Plane3D(const ITable & t) {

//	auto width = t.get<float>("width");
//	auto height = t.get<float>("height");
//
//	float hw = width * 0.5f;
//	float hh = height * 0.5f;
//
//	auto tex = t.get<std::string>("tex");
//	glm::vec2 repeat = t.get<glm::vec2>("repeat", glm::vec2(1.0f, 1.0f));
//
//	auto frontMesh = std::make_shared<TexturedMesh<Vertex3DN>>(TEXTURE_SHADER_LIGHT, GL_TRIANGLES, tex_front);
//	std::vector<Vertex3DN> vertices;
//	std::vector<unsigned int> indices;
//
//	vertices.push_back( Vertex3DN (-hw, hh, -hd, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f));
//	vertices.push_back( Vertex3DN (-hw, -hh, -hd, 0.0f, repeatFront.y, 0.0f, -1.0f, 0.0f));
//	vertices.push_back( Vertex3DN (hw, -hh, -hd, repeatFront.x, repeatFront.y, 0.0f, -1.0f, 0.0f));
//	vertices.push_back( Vertex3DN (hw, hh, -hd, repeatFront.x, 0.0f, 0.0f, -1.0f, 0.0f));
//	indices.push_back(0);
//	indices.push_back(1);
//	indices.push_back(2);
//	indices.push_back(2);
//	indices.push_back(3);
//	indices.push_back(0);
//	frontMesh->Init(vertices, indices);
//	m_meshes.push_back(frontMesh);
}