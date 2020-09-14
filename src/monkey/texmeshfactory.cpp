#include <monkey/texturedmesh.h>
#include "monkey/texmeshfactory.h"
#include "monkey/enums.h"

TexMeshFactory::TexMeshFactory() {

}

std::vector<std::shared_ptr<IMesh>> TexMeshFactory::CreateMesh (Shape& s) {
	s.accept(*this);
	return m_meshes;
}

void TexMeshFactory::visit(Plane3D & plane) {
	const auto& texInfo = m_textureInfo.at("default");
	auto mesh = std::make_shared<TexturedMesh<Vertex3DN>>(ShaderType::TEXTURE_SHADER_LIGHT, GL_TRIANGLES, texInfo.tex);

	float hw = plane.width() * 0.5f;
	float hh = plane.height() * 0.5f;
	auto orientation = plane.plane();
	std::vector<Vertex3DN> vertices;
	std::vector<unsigned> indices;

	if (orientation == 2) {  // XZ
		vertices.emplace_back(Vertex3DN{-hw, 0.0f, hh, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f});
		vertices.emplace_back(Vertex3DN{-hw, 0.0f, -hh, 0.0f, texInfo.repeat.y, 0.0f, 1.0f, 0.0f});
		vertices.emplace_back(Vertex3DN{hw, 0.0f, -hh, texInfo.repeat.x, texInfo.repeat.y, 0.0f, 1.0f, 0.0f});
		vertices.emplace_back(Vertex3DN{hw, 0.0f, hh, texInfo.repeat.x, 0.0f, 0.0f, 1.0f, 0.0f});
	} else if (orientation == 1) {  // YZ
		vertices.emplace_back(Vertex3DN{0.0f, hh, hw, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f});
		vertices.emplace_back(Vertex3DN{0.0f, -hh, hw, 0.0f, texInfo.repeat.y, 1.0f, 0.0f, 0.0f});
		vertices.emplace_back(Vertex3DN{0.0f, -hh, -hw, texInfo.repeat.x, texInfo.repeat.y, 1.0f, 0.0f, 0.0f});
		vertices.emplace_back(Vertex3DN{0.0f, hh, -hw, texInfo.repeat.x, 0.0f, 1.0f, 0.0f, 0.0f});
	} else if (orientation == 0) { // XY
		vertices.emplace_back(Vertex3DN{-hw, hh, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f});
		vertices.emplace_back(Vertex3DN{-hw, -hh, 0.0f, 0.0f, texInfo.repeat.y, 0.0f, 0.0f, 1.0f});
		vertices.emplace_back(Vertex3DN{hw, -hh, 0.0f, texInfo.repeat.x, texInfo.repeat.y, 0.0f, 0.0f, 1.0f});
		vertices.emplace_back(Vertex3DN{hw, hh, 0.0f, texInfo.repeat.x, 0.0f, 0.0f, 0.0f, 1.0f});
	}

	indices.emplace_back( 0);
	indices.emplace_back( 1);
	indices.emplace_back( 2);
	indices.emplace_back( 2);
	indices.emplace_back( 3);
	indices.emplace_back( 0);
	mesh->Init(vertices, indices);
	m_meshes.push_back(mesh);
}