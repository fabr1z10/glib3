#include <monkey/activities/split.h>
#include <monkey/engine.h>
#include <monkey/components/spriterenderer.h>
#include <monkey/math/delaunator.h>
#include <monkey/random.h>

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
    std::cout << " sheet = " << sheet;
    auto pino = model->operator[]("animations")->operator[](anim)->operator[]("frames")->operator[](frame)->operator[]("quads");
    try {
        int a = pino->operator[](0)->as<int>();
        float width = pino->operator[](2)->as<float>();
        float height = pino->operator[](3)->as<float>();

        // get a list of random points between (0, 0) and (width, height)
        std::vector<double> coords = {0, 0, width, 0, width, height, 0, height};
        for (unsigned i = 0; i < 2; ++i) {
            float x = Random::get().GetUniformReal(0, width);
            float y = Random::get().GetUniformReal(0, height);
            coords.push_back(x);
            coords.push_back(y);
        }
        delaunator::Delaunator d(coords);
        for (size_t i = 0; i < d.triangles.size(); i+=3) {
            std::cout << "tri " << i << ": " <<
        }
        std::cerr << "created triangulation with " << d.triangles.size();



    } catch (...) {

    }

    //auto anims = model->get<pybind11::object>("animations").cast<pybind11::dict>();

    //auto cane = anims.attr(anim.c_str());
    //auto pippo = anims[anim][frame];

}