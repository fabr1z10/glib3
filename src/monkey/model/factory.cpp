#include <monkey/model/factory.h>
#include <monkey/mesh.h>
#include <monkey/engine.h>
#include <monkey/math/util.h>


std::shared_ptr<Model> ModelFactory::polygon(const ITab& t) {
    // first of all, check if this is a REFERENCE



    auto format = t.get<std::string>("vertex");
    auto data = t.get<std::vector<float>>("points");

    std::vector<std::vector<glm::vec2>> points;
    std::shared_ptr<IMesh> mesh;
    if (format == "pc") {
        std::vector<VertexColor> vertices;
        std::vector<glm::vec2> outline;
        for (size_t i = 0; i < data.size(); i+=7) {
            outline.push_back(glm::vec2(data[i], data[i+1]));
            vertices.emplace_back(data[i], data[i+1], data[i+2], data[i+3], data[i+4], data[i+5], data[i+6]);
        }
        points.push_back(outline);
        if (t.has("holes")) {
            t.foreach("holes", [&] (const ITab& t) {
                auto ch = t.as<std::vector<float>>();
                std::vector<glm::vec2> h;
                for (size_t i = 0; i < ch.size(); i+=7) {
                    h.push_back(glm::vec2(ch[i], ch[i+1]));
                    vertices.emplace_back(ch[i], ch[i+1], ch[i+2], ch[i+3], ch[i+4], ch[i+5], ch[i+6]);
                }
                points.push_back(h);
            });
        }
        auto indices = glib3::math::triangulate(points);
        //indices = {0,1,2};
        auto m = std::make_shared<Mesh<VertexColor>>();
        m->m_primitive = GL_TRIANGLES;
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
