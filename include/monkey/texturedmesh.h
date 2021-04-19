#pragma once

#include <monkey/mesh.h>
#include <monkey/engine.h>
#include <monkey/math/earcut.h>

template <typename T>
class TexturedMesh : public Mesh<T> {
public:
	TexturedMesh() = default;

	TexturedMesh(const ITab& main) : Mesh<T>(main) {
        auto texName = main.get<std::string>("tex");
        auto tex = Engine::get().GetAssetManager().GetTex(texName);
        m_texId = tex->GetTexId();
	}

    TexturedMesh(ShaderType type, GLenum prim, const std::string& filename) : Mesh<T>(type) {
        this->m_primitive = prim;
        auto tex = Engine::get().GetAssetManager().GetTex(filename);
        m_texId = tex->GetTexId();
    }

//    TexturedMesh(const ITable& t) : Mesh<T>(t) {
//		using Coord = float;
//		using N = uint32_t;
//		using Point = std::array<Coord, 2>;
//		std::vector<std::vector<Point>> polygon;
//		std::vector<T> vertices;
//		std::vector<N> indices;
//		auto texId = t.get<std::string>("tex");
//		auto tex = Engine::get().GetAssetManager().GetTex(texId);
//		m_texId = tex->GetTexId();
//
//
//		auto points = t.get<std::vector<Coord>>("data");
//		polygon.push_back(std::vector<Point>());
//		assert(points.size() % T::point_size == 0);
//		for (unsigned int i = 0 ; i < points.size(); i += T::point_size) {
//			T vertex(&points[i]);
//			polygon[0].push_back({vertex.x, vertex.y});
//			vertices.push_back(vertex);
//		}
//		// calculate indices by doing triangulation
//		auto tri = mapbox::earcut<N>(polygon);
//		for (int i = 0; i < tri.size(); i += 3) {
//			indices.push_back(tri[i]);
//			indices.push_back(tri[i+1]);
//			indices.push_back(tri[i+2]);
//		}
//		this->Init(vertices, indices);
//    }

    void Setup(Shader* shader) override {
        auto texLoc = shader->GetUniformLocation(TEXTURE);
        glUniform1i(texLoc, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texId);
    }
private:
    GLuint m_texId;
};

