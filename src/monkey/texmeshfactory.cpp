#include <monkey/texturedmesh.h>
#include "monkey/texmeshfactory.h"
#include "monkey/enums.h"

TexMeshFactory::TexMeshFactory() {

}

std::vector<std::shared_ptr<IMesh>> TexMeshFactory::CreateMesh (Shape& s) {
	s.accept(*this);
	return m_meshes;
}

void TexMeshFactory::visit(PolyChain3D & shape) {
    const auto& texInfo = m_textureInfo.at("default");
    auto mesh = std::make_shared<TexturedMesh<Vertex3DN>>(ShaderType::TEXTURE_SHADER_LIGHT, GL_TRIANGLES, texInfo.tex);
    float width = shape.width();
    float hw = 0.5f * width;
    std::vector<Vertex3DN> vertices;
    std::vector<unsigned> indices;
    unsigned j = 0;

    float tx = 0;
    float ty = width / texInfo.repeat.y;
    for (size_t i = 0; i < shape.getPointCount() - 1; ++i) {
        glm::vec2 P = shape.getPoint(i);
        glm::vec2 Pnext = shape.getPoint(i+1);
        // for each point we have a quad
        float length = glm::length(Pnext-P);
        glm::vec2 t = glm::normalize (Pnext - P);
        glm::vec2 n = glm::cross(glm::vec3(0, 0, 1), glm::vec3(t, 0.0f));
        float incTex = length / texInfo.repeat.x;
        vertices.emplace_back(Vertex3DN{P.x, P.y, hw, tx, ty, n.x, n.y, 0.0f});
        vertices.emplace_back(Vertex3DN{Pnext.x, Pnext.y, hw, tx+incTex, ty, n.x, n.y, 0.0f});
        vertices.emplace_back(Vertex3DN{Pnext.x, Pnext.y, -hw, tx+incTex, 0.0f, n.x, n.y, 0.0f});
        vertices.emplace_back(Vertex3DN{P.x, P.y, -hw, tx, 0.0f, n.x, n.y, 0.0f});
        tx += incTex;
        indices.emplace_back( j);
        indices.emplace_back( j+1);
        indices.emplace_back( j+2);
        indices.emplace_back( j+2);
        indices.emplace_back( j+3);
        indices.emplace_back( j);
        j += 4;
    }
    mesh->Init(vertices, indices);
    m_meshes.push_back(mesh);
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