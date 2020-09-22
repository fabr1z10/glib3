#include <monkey/texturedmesh.h>
#include "monkey/texmeshfactory.h"
#include "monkey/enums.h"
#include <monkey/math/shapes/polytri.h>
#include <monkey/math/earcut.h>

TexMeshFactory::TexMeshFactory() {

}

std::vector<std::shared_ptr<IMesh>> TexMeshFactory::CreateMesh (Shape& s) {
	s.accept(*this);
	return m_meshes;
}

void TexMeshFactory::visit(Polygon& poly) {
    const auto& texInfo = m_textureInfo.at("default");

    using Coord = float;
    using N = uint32_t;

    using Point = std::array<Coord, 2>;
    std::vector<std::vector<Point>> polygon;
    std::vector<Point> op;
    //m_bounds.min = glm::vec3(outline[0], outline[1], 0.0f);
    //m_bounds.max = glm::vec3(outline[0], outline[1], 0.0f);
    std::vector<Vertex3DN> vertices;
    std::vector<unsigned> indices;
    for (const glm::vec2& P : poly.getPoints()) {
        op.push_back({P.x, P.y});
        vertices.emplace_back(Vertex3DN(P.x, P.y, 0.0f, P.x / texInfo.repeat.x, P.y / texInfo.repeat.y, 0, 0, 1));
    }
    polygon.push_back(op);
    auto mesh = std::make_shared<TexturedMesh<Vertex3DN>>(ShaderType::TEXTURE_SHADER_LIGHT, GL_TRIANGLES, texInfo.tex);


    // add all vertices in op
    auto tri = mapbox::earcut<N>(polygon);
    // calculate edges
    for (int i = 0; i < tri.size(); i += 3) {
        indices.push_back(tri[i]);
        indices.push_back(tri[i+1]);
        indices.push_back(tri[i+2]);
    }
    // Run tessellation
    // Returns array of indices that refer to the vertices of the input polygon.
    // e.g: the index 6 would r
    mesh->Init(vertices, indices);
    m_meshes.push_back(mesh);
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

void TexMeshFactory::visit(ISurf2D & s) {
    // make grid of pts
    const auto& texInfo = m_textureInfo.at("default");

    int nx = s.getNx();
    int ny = s.getNy();
    int n = nx * ny;
    glm::vec2 p0 = s.getMin();
    glm::vec2 gridSize = s.getGridSize();
    std::vector<std::vector<float>> heights;
    std::vector<Vertex3DN> vertices;
    std::vector<unsigned> indices;
    float ymax = p0.y + (ny-1) * gridSize.y;
    for (int j = 0; j < ny; ++j) {
        std::vector<float> row(nx);
        float y = p0.y + j * gridSize.y;
        for (int i = 0; i < nx; ++i) {
            float x = p0.x + i * gridSize.x;
            row[i] = s(x, y);
        }
        heights.push_back(row);
    }

    for (int j = 0; j < ny; ++j) {
        float y = p0.y + j * gridSize.y;
        for (int i = 0; i < nx; ++i) {
            float x = p0.x + i * gridSize.x;
            // compute normals
            float h = heights[i][j];
            float hR = i < nx-1 ? heights[i+1][j] : h;
            float hL = i > 0 ? heights[i-1][j] : h;
            float dx = (i > 0 && i < nx-1) ? gridSize.x : 2.0f * gridSize.x;
            float nx = (hL-hR) / dx;
            float hU = j < ny-1 ? heights[i][j+1] : h;
            float hD = j > 0 ? heights[i][j-1] : h;
            float dy = (j > 0 && j < ny-1) ? gridSize.y : 2.0f * gridSize.y;
            float ny = (hD-hU) / dy;
            glm::vec3 normal = glm::normalize(glm::vec3(nx, 2.0f, -ny));
            vertices.emplace_back( Vertex3DN (x, h, -y, (x-p0.x)/texInfo.repeat.x, (ymax-y)/texInfo.repeat.y, normal.x, normal.y, normal.z ) );
        }
    }

    // compute indices
    for (int i = 0; i < n - nx; ++i) {
        if ( (i+1) % nx != 0) {
            indices.push_back(i);
            indices.push_back(i + 1);
            indices.push_back(i + 1 + nx);

            indices.push_back(i);
            indices.push_back(i + 1 + nx);
            indices.push_back(i + 1 + nx - 1);
        }
    }

    auto mesh = std::make_shared<TexturedMesh<Vertex3DN>>(ShaderType::TEXTURE_SHADER_LIGHT, GL_TRIANGLES, texInfo.tex);
    mesh->Init(vertices, indices);
    m_meshes.push_back(mesh);
}