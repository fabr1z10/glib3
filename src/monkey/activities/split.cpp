#include <monkey/activities/split.h>
#include <monkey/engine.h>
#include <monkey/components/spriterenderer.h>
#include <monkey/math/delaunator.h>
#include <monkey/random.h>
#include <monkey/mesh.h>
#include <monkey/components/statemachine.h>
#include <monkey/states/fly.h>
#include <monkey/components/controller3d.h>

SplitQuad::SplitQuad(const ITab& t) : TargetActivity(t) {

}



void SplitQuad::Start() {
    TargetActivity::Start();
    auto renderer = dynamic_cast<SpriteRenderer*>(m_entity->GetComponent<Renderer>());
    auto anim = renderer->getAnimation();
    auto frame = renderer->getFrame();
    auto spriteModel = dynamic_cast<SpriteModel*>(renderer->GetModel());
    std::cout << " model is = " << spriteModel->getId();
    auto& f = spriteModel->getAnimationInfo(anim)->frames[frame];
    auto model = Engine::get().GetAssetManager().getAsset(spriteModel->getId());
    auto sheet = model->get<std::string>("sheet");
    auto tex = Engine::get().GetAssetManager().get<Tex>(sheet);

    auto texWidth = static_cast<float>(tex->GetWidth());
    auto texHeight = static_cast<float>(tex->GetHeight());
    std::cout << " sheet = " << sheet;
    auto pino = model->operator[]("animations")->operator[](anim)->operator[]("frames")->operator[](frame)->operator[]("quads");
    try {
        auto p22 = pino->as<std::vector<float>>();
        float x = p22[0]; // ->operator[](0)->as<float>();
        float y = p22[1]; //pino->operator[](0)->as<float>();
        float width = p22[2]; //pino->operator[](2)->as<float>();
        float height = p22[3]; pino->operator[](3)->as<float>();
        float ox = p22.size() > 4 ? p22[4] : 0.0f;
        float oy = p22.size() > 5 ? p22[5] : 0.0f;

        float tx = x / texWidth;    // tex coords of top left
        float ty = y / texHeight;
        // get a list of random points between (0, 0) and (width, height)
        std::vector<double> coords = {0, 0, width, 0, width, height, 0, height};
        for (unsigned i = 0; i < 2; ++i) {
            float rx = Random::get().GetUniformReal(0, width);
            float ry = Random::get().GetUniformReal(0, height);
            coords.push_back(rx);
            coords.push_back(ry);
        }
        delaunator::Delaunator d(coords);
        auto mainEntity = std::make_shared<Entity>();
        auto l = [&] (std::vector<Vertex3D>& vertices, unsigned index) {
            float xt = coords[2 * d.triangles[index]];
            float yt = coords[2 * d.triangles[index] + 1];
            vertices.emplace_back(xt + ox, yt + oy, 0.0f, (xt + x) / texWidth, (y + height - yt) / texHeight, 1.0f, 1.0f, 1.0f, 1.0f);
            return glm::vec3(xt+ox, yt+oy, 0.0f);
        };

        for (size_t i = 0; i < d.triangles.size(); i+=3) {
            std::vector<Vertex3D> vertices;
            std::vector<unsigned int> indices{0, 1, 2};
            auto mesh = std::make_shared<Mesh<Vertex3D>>(ShaderType::TEXTURE_SHADER_UNLIT);
            mesh->m_primitive = GL_TRIANGLES;
            auto A = l(vertices, i);
            auto B = l(vertices, i+1);
            auto C = l(vertices, i+2);
            glm::vec3 centroid = (A + B + C) / 3.0f;
            mesh->Init(vertices, indices);
            glm::vec2 vel (centroid.x, centroid.y);
            mesh->addTexture(sheet, TexType::DIFFUSE);
            auto m = std::make_shared<Model>();
            m->addMesh(mesh);
            auto subEntity = std::make_shared<Entity>();
            subEntity->AddComponent(m->makeRenderer(m));
            subEntity->AddComponent(std::make_shared<Controller3D>(glm::vec3(1.0f), glm::vec3(0.0f), 2, 2));
            subEntity->AddComponent(std::make_shared<Dynamics>());
            auto sm = std::make_shared<StateMachine>("fly");
            sm->AddState("fly", std::make_shared<Fly>(0.0f, vel, 0.0f));
            subEntity->AddComponent(sm);
            mainEntity->AddChild(subEntity);

            //mesh->addTexture(TextureInfo{tex->GetTexId(), TexType::DIFFUSE});
        }
        m_entity->GetParent()->AddChild(mainEntity);
        mainEntity->SetPosition(m_entity->GetPosition());
        mainEntity->SetScale(m_entity->GetScale());
        std::cerr << "created triangulation with " << d.triangles.size();
        Engine::get().Remove(m_entity.get());


    } catch (...) {

    }

    //auto anims = model->get<pybind11::object>("animations").cast<pybind11::dict>();

    //auto cane = anims.attr(anim.c_str());
    //auto pippo = anims[anim][frame];

}