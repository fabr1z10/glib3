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
    m_pieces = t.get<int>("pieces");
    m_angularSpeed = t.get<float>("angular_speed");
    m_gravity = t.get<float>("gravity");
    m_xSpeedFactor = t.get<float>("xvel");
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
        for (unsigned i = 0; i < m_pieces; ++i) {
            float rx = Random::get().GetUniformReal(0, width);
            float ry = Random::get().GetUniformReal(0, height);
            coords.push_back(rx);
            coords.push_back(ry);
        }
        delaunator::Delaunator d(coords);
        auto mainEntity = std::make_shared<Entity>();
        auto scale = m_entity->getScaleVec();
        auto l = [&] (std::vector<Vertex3D>& vertices, unsigned index) {
            float xA = coords[2 * d.triangles[index]];
            float yA = coords[2 * d.triangles[index] + 1];
            float xB = coords[2 * d.triangles[index+1]];
            float yB = coords[2 * d.triangles[index+1] + 1];
            float xC = coords[2 * d.triangles[index+2]];
            float yC = coords[2 * d.triangles[index+2] + 1];

            glm::vec2 centroid((xA + xB + xC) / 3.0f, (yA + yB + yC) / 3.0f);

            vertices.emplace_back(xA - centroid.x, yA - centroid.y, 0.0f, (xA + x) / texWidth, (y + height - yA) / texHeight, 1.0f, 1.0f, 1.0f, 1.0f);
            vertices.emplace_back(xB - centroid.x, yB - centroid.y, 0.0f, (xB + x) / texWidth, (y + height - yB) / texHeight, 1.0f, 1.0f, 1.0f, 1.0f);
            vertices.emplace_back(xC - centroid.x, yC - centroid.y, 0.0f, (xC + x) / texWidth, (y + height - yC) / texHeight, 1.0f, 1.0f, 1.0f, 1.0f);

            auto c1 = centroid + glm::vec2(ox, oy);
            c1.x *= scale.x;
            c1.y *= scale.y;
            return c1;
        };

        for (size_t i = 0; i < d.triangles.size(); i+=3) {
            std::vector<Vertex3D> vertices;
            std::vector<unsigned int> indices{0, 1, 2};
            auto mesh = std::make_shared<Mesh<Vertex3D>>(ShaderType::TEXTURE_SHADER_UNLIT);
            mesh->m_primitive = GL_TRIANGLES;
            auto centroid = l(vertices, i);
            mesh->Init(vertices, indices);
            glm::vec2 vel (centroid.x * m_xSpeedFactor, centroid.y * 0.2f);
            mesh->addTexture(sheet, TexType::DIFFUSE);
            auto m = std::make_shared<Model>();
            m->addMesh(mesh);
            auto subEntity = std::make_shared<Entity>();
            auto renderer = m->makeRenderer(m);
            renderer->setMultColor(glm::vec4(1.0f, 0.5f, 0.5f, 1.0f));
            subEntity->AddComponent(renderer);
            subEntity->AddComponent(std::make_shared<Controller3D>(glm::vec3(1.0f), glm::vec3(0.0f), 2, 2));
            subEntity->AddComponent(std::make_shared<Dynamics>());
            auto sm = std::make_shared<StateMachine>("fly");
            sm->AddState("fly", std::make_shared<Fly>(m_gravity, vel, m_angularSpeed));
            subEntity->AddComponent(sm);

            subEntity->SetPosition(glm::vec3(centroid, 0.0f));
            subEntity->setScale(m_entity->getScaleVec());

            mainEntity->AddChild(subEntity);


            //mesh->addTexture(TextureInfo{tex->GetTexId(), TexType::DIFFUSE});
        }
        m_entity->GetParent()->AddChild(mainEntity);
        mainEntity->SetPosition(m_entity->GetPosition());
        //mainEntity->SetScale(m_entity->GetScale());
        std::cerr << "created triangulation with " << d.triangles.size();
        Engine::get().Remove(m_entity.get());


    } catch (...) {

    }

    //auto anims = model->get<pybind11::object>("animations").cast<pybind11::dict>();

    //auto cane = anims.attr(anim.c_str());
    //auto pippo = anims[anim][frame];

}