#include <monkey/model/factory.h>
#include <monkey/mesh.h>
#include <monkey/engine.h>
#include <monkey/math/util.h>
#include <monkey/box2dworld.h>
#include <monkey/skeletalmesh.h>
#include <monkey/scenefactory.h>
#include <monkey/meshfactory.h>

//std::shared_ptr<IMesh> ModelFactory::b2Poly(b2PolygonShape &shape, glm::vec4 color) {
//    auto world = Engine::get().GetRunner<Box2DWorld>();
//    float scale = 1.0f / world->getScalingFactor();
//
//    const auto& vertices = shape.m_vertices;
//    const auto o = shape.m_centroid;
//    auto mesh = std::make_shared<Mesh<VertexColor>>(ShaderType::COLOR_SHADER);
//    std::vector<VertexColor> verts;
//    std::vector<unsigned> indices;
//
//    for (size_t i = 0; i < shape.m_count; ++i) {
//        verts.emplace_back(scale * (o.x + vertices[i].x), scale * (o.y + vertices[i].y), 0.0f, color.r, color.g, color.b, color.a);
//        indices.push_back(i);
//        indices.push_back((i+1) % shape.m_count);
//    }
//    mesh->m_primitive = GL_LINES;
//    mesh->Init(verts, indices);
//    return mesh;
//}

std::shared_ptr<Model> ModelFactory::rect(float width, float height,
                                          glm::vec2 offset, RenderType rtype,
                                          glm::vec4 color, const std::string& tex, glm::vec2 repeat, glm::vec2 scale) {
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
        if (width == 0 || height == 0) {
			auto t = Engine::get().GetAssetManager().get<Tex>(tex);
			width = scale.x * t->GetWidth();
			height = scale.y * t->GetHeight();
		}

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
    //for (int j = 0; j < size[1]; ++j) {
    //    for (int i = 0; i < size[0]; ++i) {
    int i = 0;
    int j = 0;
    int count = 0;
    int tileCount = size[0] * size[1];
    while (count < tileCount) {
    	if (data[n] == -1) {
        	n += 1;
        	count++;
			i++;
			if (i >= size[0]) {
				i = 0;
				j++;
			}
            continue;
    	}
        bool fliph = false;
        int repeat = 1;
        if (data[n] == -2) {
        	// flip horizontally next tile
           	n++;
           	fliph = true;
        }

        if (data[n] == -3) {
          	n++;
           	repeat = data[n++];
        }

        for (int k = 0; k < repeat; k++) {
			float tx0 = data[n] * tw;
			float tx1 = (data[n] + 1) * tw;
			if (fliph) std::swap(tx0, tx1);
			verts.emplace_back(i * tileWidth, j * tileHeight, 0, tx0, (data[n + 1] + 1) * th, 1, 1, 1, 1);
			verts.emplace_back((i + 1) * tileWidth, j * tileHeight, 0, tx1, (data[n + 1] + 1) * th, 1, 1, 1, 1);
			verts.emplace_back((i + 1) * tileWidth, (j + 1) * tileHeight, 0, tx1, data[n + 1] * th, 1, 1, 1, 1);
			verts.emplace_back(i * tileWidth, (j + 1) * tileHeight, 0, tx0, data[n + 1] * th, 1, 1, 1, 1);
			indices.push_back(v);
			indices.push_back(v + 1);
			indices.push_back(v + 2);
			indices.push_back(v + 2);
			indices.push_back(v + 3);
			indices.push_back(v);
			v += 4;
			// increase x
			i++;
			if (i >= size[0]) {
				i = 0;
				j++;
			}
			count++;
        }
        n += 2;

    }

    mesh->Init(verts, indices);
    return std::make_shared<Model>(mesh);

}

std::shared_ptr<Model> ModelFactory::_rampWireframe(const ITab & t) {
    std::vector<VertexColor> vertices;
    std::vector<unsigned> indices;
    float width = t.get<float>("width");
    float height = t.get<float>("height");
    float length = t.get<float>("length");

    vertices.emplace_back(0.0f, 0.0f, 0.0f, 1.0f, 1.0, 1.0f, 1.0f);
    vertices.emplace_back(width, 0.0f, 0.0f, 1.0f, 1.0, 1.0f, 1.0f);
    vertices.emplace_back(width, 0.0f, length, 1.0f, 1.0, 1.0f, 1.0f);
    vertices.emplace_back(0.0f, 0.0f, length, 1.0f, 1.0, 1.0f, 1.0f);
    vertices.emplace_back(width, height, length, 1.0f, 1.0, 1.0f, 1.0f);
    vertices.emplace_back(0.0f, height, length, 1.0f, 1.0, 1.0f, 1.0f);
    indices = {0, 1, 1, 2, 2, 3, 3, 0, 1, 4, 2, 4, 0, 5, 3, 5, 4, 5};

    auto m = std::make_shared<Mesh<VertexColor>>(ShaderType::COLOR_SHADER);
    m->m_primitive = GL_LINES;
    m->Init(vertices, indices);
    //m->addTexture(tex, TexType::DIFFUSE);

    return std::make_shared<Model>(m);
}

std::shared_ptr<Model> ModelFactory::_box3DColor(const ITab & t) {
    std::vector<VertexColorNormal> vertices;
    std::vector<unsigned> indices;

    auto size = t.get<glm::vec3>("size", glm::vec3(1.0f));
    auto color = t.get<glm::vec4>("color");
    auto frontColor = t.get<glm::vec4>("color_front", color);
    auto topColor = t.get<glm::vec4>("color_top", color);
    auto leftColor = t.get<glm::vec4>("color_left", color);
    auto rightColor = t.get<glm::vec4>("color_right", color);
    auto backColor = t.get<glm::vec4>("color_back", color);
    auto bottomColor = t.get<glm::vec4>("color_bottom", color);
    auto offset = t.get<glm::vec3>("offset", glm::vec3(0.0f));
    auto m = std::make_shared<Mesh<VertexColorNormal>>(ShaderType::COLOR_SHADER_LIGHT);

    glm::vec3 fbl = offset + glm::vec3(0.0f, 0.0f, size.z);
    glm::vec3 fbr = offset + glm::vec3(size.x, 0.0f, size.z);
    glm::vec3 ftr = offset + glm::vec3(size.x, size.y, size.z);
    glm::vec3 ftl = offset + glm::vec3(0.0f, size.y, size.z);
    glm::vec3 bbl = offset + glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 bbr = offset + glm::vec3(size.x, 0.0f, 0.0f);
    glm::vec3 btr = offset + glm::vec3(size.x, size.y, 0.0f);
    glm::vec3 btl = offset + glm::vec3(0.0f, size.y, 0.0f);
    glm::vec3 x(1.0f, 0.0f, 0.0f);
    glm::vec3 y(0.0f, 1.0f, 1.0f);
    glm::vec3 z(0.0f, 0.0f, 1.0f);

    // front face
    vertices.emplace_back(fbl, z, frontColor);
    vertices.emplace_back(fbr, z, frontColor);
    vertices.emplace_back(ftr, z, frontColor);
    vertices.emplace_back(ftl, z, frontColor);
    //indices = {0, 1, 2, 3, 0, 2};

    // top face
    vertices.emplace_back(btl, y, topColor);
    vertices.emplace_back(ftl, y, topColor);
    vertices.emplace_back(ftr, y, topColor);
    vertices.emplace_back(btr, y, topColor);

    // back
    vertices.emplace_back(bbr, -z, backColor);
    vertices.emplace_back(bbl, -z, backColor);
    vertices.emplace_back(btl, -z, backColor);
    vertices.emplace_back(btr, -z, backColor);

    // right
    vertices.emplace_back(fbr, x, rightColor);
    vertices.emplace_back(bbr, x, rightColor);
    vertices.emplace_back(btr, x, rightColor);
    vertices.emplace_back(ftr, x, rightColor);

    // left
    vertices.emplace_back(bbl, -x, leftColor);
    vertices.emplace_back(fbl, -x, leftColor);
    vertices.emplace_back(ftl, -x, leftColor);
    vertices.emplace_back(btl, -x, leftColor);

    // bottom
    vertices.emplace_back(bbl, -y, bottomColor);
    vertices.emplace_back(bbr, -y, bottomColor);
    vertices.emplace_back(fbr, -y, bottomColor);
    vertices.emplace_back(fbl, -y, bottomColor);

    indices = {
            0, 1, 2, 3, 0, 2,
            4, 5, 6, 7, 4, 6,
            8, 9, 10, 11, 8, 10,
            12, 13, 14, 15, 12, 14,
            16, 17, 18, 19, 16, 18,
            20, 21, 22, 23, 20, 22
    };


    m->m_primitive = GL_TRIANGLES;
    m->Init(vertices, indices);
    //m->addTexture(tex, TexType::DIFFUSE);

    return std::make_shared<Model>(m);
}

std::shared_ptr<Model> ModelFactory::_cube3D(const ITab & t) {
    std::vector<Vertex3DN> vertices;
    std::vector<unsigned> indices;

    auto size = glm::vec3(t.get<float>("size", 1.0f));
    auto tex = t.get<std::string>("tex");
    auto offset = t.get<glm::vec3>("offset", glm::vec3(0.0f));

    auto m = std::make_shared<Mesh<Vertex3DN>>(ShaderType::TEXTURE_SHADER_LIGHT);

    float u = 1.0f / 3.0f;
    float u1 = 2.0f / 3.0f;

    glm::vec3 fbl = offset + glm::vec3(0.0f, 0.0f, size.z);
    glm::vec3 fbr = offset + glm::vec3(size.x, 0.0f, size.z);
    glm::vec3 ftr = offset + glm::vec3(size.x, size.y, size.z);
    glm::vec3 ftl = offset + glm::vec3(0.0f, size.y, size.z);
    glm::vec3 bbl = offset + glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 bbr = offset + glm::vec3(size.x, 0.0f, 0.0f);
    glm::vec3 btr = offset + glm::vec3(size.x, size.y, 0.0f);
    glm::vec3 btl = offset + glm::vec3(0.0f, size.y, 0.0f);
    glm::vec3 x(1.0f, 0.0f, 0.0f);
    glm::vec3 y(0.0f, 1.0f, 1.0f);
    glm::vec3 z(0.0f, 0.0f, 1.0f);

    // front face
    vertices.emplace_back(fbl, glm::vec2(0.0f, 1.0f), z);
    vertices.emplace_back(fbr, glm::vec2(u, 1.0f), z);
    vertices.emplace_back(ftr, glm::vec2(u, u1), z);
    vertices.emplace_back(ftl, glm::vec2(0.0f, u1), z);
    //indices = {0, 1, 2, 3, 0, 2};

    // top face
    vertices.emplace_back(btl, glm::vec2(u, u1), y);
    vertices.emplace_back(ftl, glm::vec2(u, 1.0f), y);
    vertices.emplace_back(ftr, glm::vec2(u1, 1.0f), y);
    vertices.emplace_back(btr, glm::vec2(u1, u1), y);

    // back
    vertices.emplace_back(bbr, glm::vec2(u1, 1.0f), -z);
    vertices.emplace_back(bbl, glm::vec2(1.0f, 1.0f), -z);
    vertices.emplace_back(btl, glm::vec2(1.0f, u1), -z);
    vertices.emplace_back(btr, glm::vec2(u1, u1), -z);

    // right
    vertices.emplace_back(fbr, glm::vec2(u1, u1), x);
    vertices.emplace_back(bbr, glm::vec2(1.0f, u1), x);
    vertices.emplace_back(btr, glm::vec2(1.0f, u), x);
    vertices.emplace_back(ftr, glm::vec2(u1, u), x);

    // left
    vertices.emplace_back(bbl, glm::vec2(u, u1), -x);
    vertices.emplace_back(fbl, glm::vec2(u1, u1), -x);
    vertices.emplace_back(ftl, glm::vec2(u1, u), -x);
    vertices.emplace_back(btl, glm::vec2(u, u), -x);

    // bottom
    vertices.emplace_back(bbl, glm::vec2(0.0f, u), -y);
    vertices.emplace_back(bbr, glm::vec2(u, u), -y);
    vertices.emplace_back(fbr, glm::vec2(u, u1), -y);
    vertices.emplace_back(fbl, glm::vec2(0, u1), -y);

    indices = {
        0, 1, 2, 3, 0, 2,
        4, 5, 6, 7, 4, 6,
        8, 9, 10, 11, 8, 9,
        12, 13, 14, 15, 12, 14,
        16, 17, 18, 19, 16, 18,
        20, 21, 22, 23, 20, 22
    };


    m->m_primitive = GL_TRIANGLES;
    m->Init(vertices, indices);
    m->addTexture(tex, TexType::DIFFUSE);

    return std::make_shared<Model>(m);
}

std::shared_ptr<Model> ModelFactory::_rect(const ITab & t) {
    auto size = t.get<glm::vec2>("size", glm::vec2(0.0f));
    auto offset = t.get<glm::vec2>("offset", glm::vec2(0.0f));
    float width = size[0];
    float height = size[1];
    auto tex = t.get<std::string>("tex", "");
    auto render = t.get<std::string>("render", "fill");
    auto color = t.get<glm::vec4> ("color", glm::vec4(1.0f));
    auto rtype = (render == "fill" ? RenderType::FILL : RenderType::WIREFRAME);
    auto repeat = t.get<glm::vec2>("repeat", glm::vec2(1.0f, 1.0f));
    auto scale = t.get<glm::vec2>("scale", glm::vec2(1.0f, 1.0f));
    return rect(width, height, offset, rtype, color, tex, repeat, scale);
}

std::shared_ptr<Model> ModelFactory::_quad(const ITab & t) {
	auto w = t.get<glm::vec2>("width"); // width below and above
	auto h = t.get<glm::vec2>("height"); // height left and right
	auto offset = t.get<glm::vec2>("offset"); // height left and right
	auto color = t.get<glm::vec4> ("color", glm::vec4(1.0f));
	auto tex = t.get<std::string>("tex", "");

	auto m = std::make_shared<Mesh<Vertex3D>>(ShaderType::TEXTURE_SHADER_UNLIT);

	std::vector<Vertex3D> vertices{
		{-0.5f * w[1] + offset.x, 0.5f * h[0]+ offset.y, 0, 0, 0, color.r, color.g, color.b, color.a},
		{-0.5f * w[0]+ offset.x, -0.5f * h[0]+ offset.y, 0, 0, 1, color.r, color.g, color.b, color.a},
		{0.5f * w[0]+ offset.x, -0.5f * h[1]+ offset.y, 0, 1, 1, color.r, color.g, color.b, color.a},
		{0.5f * w[1]+ offset.x, 0.5f * h[1]+ offset.y, 0, 1, 0, color.r, color.g, color.b, color.a},
	};
	std::vector<unsigned> indices;
	indices = {0, 1, 2, 3, 0, 2};
	m->m_primitive = GL_TRIANGLES;
	m->Init(vertices, indices);
	m->addTexture(tex, TexType::DIFFUSE);

	return std::make_shared<Model>(m);

}


std::shared_ptr<Model> ModelFactory::shape(const ITab & t) {
	auto factory = Engine::get().GetSceneFactory();
	auto shapeDesc = t["shape"];
	auto color = t.get<glm::vec4>("color", glm::vec4(1.0f));
	auto shape = factory->make2<IShape>(*shapeDesc.get());
	MeshFactory m;
	auto pino = m.createWireframe(shape.get(), color);
	return pino;
}

std::shared_ptr<Model> ModelFactory::prism(const ITab & t)  {
	std::vector<Vertex3DN> vertices;
	std::vector<unsigned> indices;
	std::vector<Vertex3DN> side_vertices;
	std::vector<unsigned> side_indices;

	auto repeat_every = t.get<glm::vec3>("repeat");
	auto top = t.get<std::string>("top");
	auto side = t.get<std::string>("side");

	float h = t.get<float>("height");
    auto offset = t.get<glm::vec3>("offset", glm::vec3(0.0f));

	std::vector<std::vector<glm::vec2>> pts;
	auto poly = t.get<std::vector<float>>("poly");
	std::vector<glm::vec2> outline;
	for (size_t i = 0; i < poly.size(); i+=2) {
		outline.emplace_back(poly[i], poly[i+1]);
		vertices.emplace_back(poly[i], 0.0f, -poly[i+1], (poly[i] / repeat_every.x), (-poly[i+1] / repeat_every.z), 0.0f, 1.0f, 0.0f);
	}
	float sx = 0.0f;
	float tb = h / repeat_every.y;
	for (size_t i = 0; i < poly.size(); i+=2) {
		int j = i+2;
		if (j >= poly.size())
			j = 0;
		glm::vec3 u = glm::normalize(glm::vec3(poly[j], 0.0f, -poly[j+1]) - glm::vec3(poly[i], 0.0f, -poly[i+1]));
		glm::vec3 n = glm::cross(u, glm::vec3(0, 1, 0));
		float length = glm::length(glm::vec3(poly[j], 0.0f, -poly[j+1]) - glm::vec3(poly[i], 0.0f, -poly[i+1]));
		unsigned k = side_vertices.size();
		side_indices.push_back(k);
		side_indices.push_back(k+1);
		side_indices.push_back(k+2);
		side_indices.push_back(k+1);
		side_indices.push_back(k+3);
		side_indices.push_back(k+2);
		side_vertices.emplace_back(poly[i], 0.0f, -poly[i+1], sx, 0.0f, n.x, n.y, n.z);
		side_vertices.emplace_back(poly[i], -h, -poly[i+1], sx, tb, n.x, n.y, n.z);
		sx += length / repeat_every.x;
		side_vertices.emplace_back(poly[j], 0.0f, -poly[j+1], sx, 0.0f, n.x, n.y, n.z);
		side_vertices.emplace_back(poly[j], -h, -poly[j+1], sx, tb, n.x, n.y, n.z);

	}

	// TODO add support for holes
	pts.push_back(outline);
	indices = glib3::math::triangulate(pts);

	// create top mesh
	auto mesh = std::make_shared<Mesh<Vertex3DN>>(ShaderType::TEXTURE_SHADER_LIGHT);
	mesh->m_primitive = GL_TRIANGLES;
	//mesh->m_behind = true;
	mesh->Init(vertices, indices);
	mesh->addTexture(top, TexType::DIFFUSE);

	auto sideMesh = std::make_shared<Mesh<Vertex3DN>>(ShaderType::TEXTURE_SHADER_LIGHT);
	sideMesh->m_primitive = GL_TRIANGLES;
	sideMesh->Init(side_vertices, side_indices);
	sideMesh->addTexture(side, TexType::DIFFUSE);
	auto model = std::make_shared<Model>();
	model->addMesh(mesh);
	model->addMesh(sideMesh);
    model->setOffset(offset);
	return model;

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
    if (t.has("dimensions")) {
        t.foreach("dimensions", [&] (const std::string& id, const ITab& point) {
            mesh->addDimension(id, point.as<glm::vec2>());
        });
    }
	auto& factory = Engine::get().GetAssetManager();
	//auto jointId = t.get<int>("joint_id");
	//auto parentJointId = t.get<int>("parent_joint_id", -1);
	auto tex = factory.get<Tex>(t.get<std::string>("tex"));
	std::vector<VertexSkeletal> vertices;
	std::vector<Point> polygon;

	for (size_t i = 0; i < data.size(); i += 3) {
		size_t offset = i;
		VertexSkeletal vertex;
		float x = data[offset] - origin.x;
		float y = -(data[offset + 1] - origin.y);
		vertex.x = x;
		vertex.y = y;
		vertex.z = 0.0f;
		vertex.s = data[offset] / tex->GetWidth();
		vertex.t = data[offset + 1] / tex->GetHeight();

		vertex.weight0 = 1.0 - data[offset + 2];
		vertex.weight1 = data[offset + 2];
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