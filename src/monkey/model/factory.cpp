#include <monkey/model/factory.h>
#include <monkey/mesh.h>
#include <monkey/engine.h>
#include <monkey/math/util.h>
#include <monkey/box2dworld.h>

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

std::shared_ptr<Model> ModelFactory::rect(const ITab & t) {
    auto size = t.get<glm::vec2>("size");
    auto offset = t.get<glm::vec2>("offset", glm::vec2(0.0f));
    float width = size[0];
    float height = size[1];
    auto tex = t.get<std::string>("tex", "");
    auto render = t.get<std::string>("render", "fill");

    auto color = t.get<glm::vec4> ("color");
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
        if (render == "fill") {
            indices = {0, 1, 2, 3, 0, 2};
            m->m_primitive = GL_TRIANGLES;
        } else {
            indices = {0, 1, 1, 2, 2, 3, 3, 0};
            m->m_primitive = GL_LINES;
        }
        m->Init(vertices, indices);
        mesh = m;

    }
    return std::make_shared<Model>(mesh);
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
