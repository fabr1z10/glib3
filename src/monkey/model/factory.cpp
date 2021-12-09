#include <monkey/model/factory.h>
#include <monkey/mesh.h>
#include <monkey/engine.h>
#include <monkey/math/util.h>
#include <monkey/box2dworld.h>
#include <monkey/skeletalmesh.h>

std::shared_ptr<IMesh> ModelFactory::b2Poly(b2PolygonShape &shape, glm::vec4 color) {
    auto world = Engine::get().GetRunner<Box2DWorld>();
    float scale = 1.0f / world->getScalingFactor();

    const auto& vertices = shape.m_vertices;
    const auto o = shape.m_centroid;
    auto mesh = std::make_shared<Mesh<VertexColor>>(ShaderType::COLOR_SHADER);
    std::vector<VertexColor> verts;
    std::vector<unsigned> indices;

    for (size_t i = 0; i < shape.m_count; ++i) {
        verts.emplace_back(scale * (o.x + vertices[i].x), scale * (o.y + vertices[i].y), 0.0f, color.r, color.g, color.b, color.a);
        indices.push_back(i);
        indices.push_back((i+1) % shape.m_count);
    }
    mesh->m_primitive = GL_LINES;
    mesh->Init(verts, indices);
    return mesh;
}

std::shared_ptr<Model> ModelFactory::rect(float width, float height,
                                          glm::vec2 offset, RenderType rtype,
                                          glm::vec4 color, const std::string& tex, glm::vec2 repeat) {
    std::shared_ptr<IMesh> mesh;
    if (tex.empty()) {
        auto m = std::make_shared<Mesh<VertexColor>>(ShaderType::COLOR_SHADER);
        std::vector<VertexColor> vertices{
                {offset.x, offset.y, 0, color},
                { offset.x + width, offset.y, 0, color},
                { offset.x + width, offset.y + height, 0, color},
                { offset.x, offset.y + height, 0, color},
        };
        std::vector<unsigned> indices;
        if (rtype == RenderType::FILL) {
            indices = {0, 1, 2, 3, 0, 2};
            m->m_primitive = GL_TRIANGLES;
        } else {
            indices = {0, 1, 1, 2, 2, 3, 3, 0};
            m->m_primitive = GL_LINES;
        }
        m->Init(vertices, indices);
        mesh = m;
    } else {
        auto m = std::make_shared<Mesh<Vertex3D>>(ShaderType::TEXTURE_SHADER_UNLIT);
        std::vector<Vertex3D> vertices{
            {offset.x, offset.y, 0, 0, repeat.y, color.r, color.g, color.b, color.a},
            {offset.x + width, offset.y, 0, repeat.x, repeat.y, color.r, color.g, color.b, color.a},
            {offset.x + width, offset.y + height, 0, repeat.x, 0, color.r, color.g, color.b, color.a},
            {offset.x, offset.y + height, 0, 0, 0, color.r, color.g, color.b, color.a},
        };
        std::vector<unsigned> indices;
        indices = {0, 1, 2, 3, 0, 2};
        m->m_primitive = GL_TRIANGLES;
        m->Init(vertices, indices);
        m->addTexture(tex, TexType::DIFFUSE);
        mesh = m;

    }
    return std::make_shared<Model>(mesh);

}

std::shared_ptr<Model> ModelFactory::_tiled(const ITab & t) {
    auto mesh = std::make_shared<Mesh<Vertex3D>>(ShaderType::TEXTURE_SHADER_UNLIT);
    mesh->m_primitive = GL_TRIANGLES;
    std::vector<Vertex3D> verts;
    std::vector<unsigned> indices;
    auto texFile = t.get<std::string>("tex");
    auto tex = Engine::get().GetAssetManager().get<Tex>(texFile);
    mesh->addTexture(TextureInfo{tex->GetTexId(), TexType::DIFFUSE});
    auto size = t.get<glm::ivec2>("size");
    auto tileSize = t.get<glm::vec2>("tile_size");
    auto imgTileSize = t.get<glm::vec2>("img_tile_size");

    float tileWidth = tileSize[0];
    float tileHeight = tileSize[1];
    auto tw = imgTileSize[0] / tex->GetWidth();
    auto th = imgTileSize[1] / tex->GetHeight();

    auto data = t.get<std::vector<int>>("data");
    size_t n = 0;
    size_t v = 0;
    for (int j = 0; j < size[1]; ++j) {
        for (int i = 0; i < size[0]; ++i) {
            if (data[n] == -1) {
                n += 1;
                continue;
            }
            verts.emplace_back(i * tileWidth, j * tileHeight, 0, data[n] * tw, (data[n+1] + 1) * th, 1, 1, 1, 1);
            verts.emplace_back((i+1) * tileWidth, j * tileHeight, 0, (data[n] + 1) * tw, (data[n+1] +1) * th, 1, 1, 1, 1);
            verts.emplace_back((i+1) * tileWidth, (j + 1) * tileHeight, 0, (data[n] + 1) * tw, data[n+1] * th, 1, 1, 1, 1);
            verts.emplace_back(i * tileWidth, (j+1) * tileHeight, 0, data[n] * tw, data[n+1] * th, 1, 1, 1, 1);
            indices.push_back(v);
            indices.push_back(v+1);
            indices.push_back(v+2);
            indices.push_back(v+2);
            indices.push_back(v+3);
            indices.push_back(v);
            v += 4;
            n += 2;
        }
    }
    mesh->Init(verts, indices);
    return std::make_shared<Model>(mesh);

}

std::shared_ptr<Model> ModelFactory::_rect(const ITab & t) {
    auto size = t.get<glm::vec2>("size");
    auto offset = t.get<glm::vec2>("offset", glm::vec2(0.0f));
    float width = size[0];
    float height = size[1];
    auto tex = t.get<std::string>("tex", "");
    auto render = t.get<std::string>("render", "fill");
    auto color = t.get<glm::vec4> ("color", glm::vec4(1.0f));
    auto rtype = (render == "fill" ? RenderType::FILL : RenderType::WIREFRAME);
    auto repeat = t.get<glm::vec2>("repeat", glm::vec2(1.0f, 1.0f));
    return rect(width, height, offset, rtype, color, tex, repeat);
}

std::shared_ptr<Model> ModelFactory::polygon(const ITab& t) {

    // first of all, check if this is a REFERENCE
    auto format = t.get<std::string>("vertex");
    auto data = t.get<std::vector<float>>("points");
    auto render = t.get<std::string>("render", "fill");

    std::vector<std::vector<glm::vec2>> points;
    std::shared_ptr<IMesh> mesh;
    std::vector<unsigned> indices;

    if (format == "pc") {
        std::vector<VertexColor> vertices;

        ModelFactory::getPolyVerts<VertexColor>(t, data, vertices, points, 6, ModelFactory::get1);

        auto m = std::make_shared<Mesh<VertexColor>>(ShaderType::COLOR_SHADER);
        if (render == "fill") {
            indices = glib3::math::triangulate(points);
            m->m_primitive = GL_TRIANGLES;
        } else {
            m->m_primitive = GL_LINES;
            unsigned n = 0;
            for (const auto& path : points) {
                unsigned first = n;
                for (size_t i = 0; i < path.size()-1; ++i) {
                    indices.push_back(n++);
                    indices.push_back(n);
                }
                indices.push_back(n++);
                indices.push_back(first);
            }
        }
        m->Init(vertices, indices);
        mesh = m;
    } else if (format == "ptc") {
        std::vector<Vertex3D> vertices;

        ModelFactory::getPolyVerts<Vertex3D>(t, data, vertices, points, 8, ModelFactory::get2);
        indices = glib3::math::triangulate(points);
        auto m = std::make_shared<Mesh<Vertex3D>>(ShaderType::TEXTURE_SHADER_UNLIT);

        m->m_primitive = GL_TRIANGLES;
        auto texFile = t.get<std::string>("tex");
        m->addTexture(texFile, TexType::DIFFUSE);
        m->Init(vertices, indices);
        mesh = m;
    }
    // convert a vector of float into
    return std::make_shared<Model>(mesh);
}

std::shared_ptr<Model> ModelFactory::quad(const std::string& imagePath, float width, float height, float repx, float repy) {

    auto mesh = std::make_shared<Mesh<Vertex3D>>();
    mesh->m_primitive = GL_TRIANGLES;


    auto tex = Engine::get().GetAssetManager().get<Tex>(imagePath);
    mesh->addTexture({tex->GetTexId(), TexType::DIFFUSE});

    //m_texId = tex->GetTexId();
    float w {width};
    float h {height};

    if (width == 0.0f && height == 0.0f) {
        w = static_cast<float>(tex->GetWidth());
        h = static_cast<float>(tex->GetHeight());
    } else if (width == 0.0f && height > 0.0f) {
        float aspect_ratio = static_cast<float>(tex->GetWidth()) / tex->GetHeight();
        width = height * aspect_ratio;
    } else if (width > 0.0f && height == 0.0f) {
        float aspect_ratio = static_cast<float>(tex->GetWidth()) / tex->GetHeight();
        height = width / aspect_ratio;
    }
    std::vector<Vertex3D> vertices;
    vertices = {
            {0.0f, 0.0f, 0.0f, 0.0f, repy},
            {w, 0.0f, 0.0f, repx, repy},
            {w, h, 0.0f, repx, 0.0f},
            {0.0f, h, 0.0f, 0.0f, 0.0f}};
    std::vector<unsigned int> indices{ 0, 1, 3, 3, 2, 1 };
    mesh->Init(vertices, indices);
    return std::make_shared<Model>(mesh);


}


std::shared_ptr<IMesh> ModelFactory::_mesh(const ITab & t) {
	using Coord = float;
	using Point = std::array<Coord, 2>;
	using N = uint32_t;

	auto mesh = std::make_shared<SkeletalMesh>();
	auto data =t.get<std::vector<float>>("data");
	mesh->m_primitive = GL_TRIANGLES;// t.get<GLenum>("primitive", GL_TRIANGLES);
	auto origin = t.get<glm::vec2>("origin");
	mesh->setOrigin(origin);
	if (t.has("key_points")) {
		t.foreach("key_points", [&] (const std::string& id, const ITab& point) {
			auto p = point.as<glm::vec2>();
			mesh->addKeyPoint(id, glm::vec2(p.x - origin.x, -(p.y - origin.y)));
		});


	}

	auto& factory = Engine::get().GetAssetManager();
	auto jointId = t.get<int>("joint_id");
	auto parentJointId = t.get<int>("parent_joint_id", -1);
	auto tex = factory.get<Tex>(t.get<std::string>("tex"));
	std::vector<VertexSkeletal> vertices;
	std::vector<Point> polygon;

	for (size_t i = 0; i < data.size(); i += 4) {
		size_t offset = i;
		VertexSkeletal vertex;
		float x = data[offset] - origin.x;
		float y = -(data[offset + 1] - origin.y);
		vertex.x = x;
		vertex.y = y;
		vertex.z = data[offset + 2];
		vertex.s = data[offset] / tex->GetWidth();
		vertex.t = data[offset + 1] / tex->GetHeight();
		vertex.index0 = jointId;
		if (parentJointId == -1) {
			vertex.index1 = 0;
			vertex.weight1 = 0.0;
			vertex.weight0 = 1.0;
		} else {
			vertex.index1 = parentJointId;
			vertex.weight1 = data[offset + 3];
			vertex.weight0 = 1.0 - data[offset + 3];
		}
		vertex.index2 = 0;
		vertex.weight2 = 0.0;
		polygon.push_back({x, y});
		vertices.push_back(vertex);
	}

	std::vector<std::vector<Point>> p;
	p.push_back(polygon);
	auto tri = mapbox::earcut<N>(p);
	mesh->Init(vertices, tri);

	mesh->addTexture(TextureInfo{tex->GetTexId(), TexType::DIFFUSE});
	return mesh;
}