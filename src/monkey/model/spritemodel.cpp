#include <monkey/model/spritemodel.h>
#include <monkey/entity.h>
#include <monkey/engine.h>
#include <iostream>
#include <monkey/error.h>
#include <pybind11/pytypes.h>
#include <monkey/input/pytab.h>
#include <monkey/components/spriterenderer.h>
#include <monkey/mesh.h>

namespace py = pybind11;

std::shared_ptr<Renderer> SpriteModel::makeRenderer(std::shared_ptr<Model> model) {
    auto renderer = std::make_shared<SpriteRenderer>(model);
    renderer->setAnimation(m_defaultAnimation);
    return renderer;
}

AnimationInfo * SpriteModel::getAnimationInfo(const std::string & id) {
    return &m_animInfos.at(id);
}

SpriteModel::SpriteModel (const ITab& t) : Model() {
//    m_shareable = true;

    auto sheetId = t.get<std::string>("sheet");;
    auto ppu = t.get<float>("ppu", 1.0);

    std::string defaultAnimation;

    auto& engine = Engine::get();
    auto tex = engine.GetAssetManager().get<Tex>(sheetId);
    float tm = engine.getTickMultiplier();

    auto texWidth = static_cast<float>(tex->GetWidth());
    auto texHeight = static_cast<float>(tex->GetHeight());


    auto dt = Engine::get().getMainTable().get<float>("frame_time");
    std::vector<Vertex3D> vertices;
    std::vector<unsigned int> indices;
    int icount {0};
    int quadCount {0};
    // get the animations
    int a=0;

    auto parseQuad = [&] (pybind11::list l) {
        auto n = l.size();
        auto x = l[0].cast<int>();
        auto y = l[1].cast<int>();
        auto width_px = l[2].cast<int>();
        auto height_px = l[3].cast<int>();
        int ox, oy = 0;
        bool flipx, flipy = false;
        if (n > 4) {
            ox = l[4].cast<int>();
            oy = l[5].cast<int>();
        }
        if (n > 6) {
            PyTab extra(l[6]);
            flipx = extra.get<bool>("flipx", false);
            flipy = extra.get<bool>("flipy", false);

        }
        // compute width and height in world coordinates
        float w = width_px / ppu;
        float h = height_px / ppu;
        float tx = x / texWidth;
        float ty = y / texHeight;
        float tw = width_px / texWidth;
        float th = height_px / texHeight;

        float txl = flipx ? tx+tw : tx;
        float txr = flipx ? tx : tx + tw;
        float tyb = flipy ? ty : ty+th;
        float tyt = flipy ? ty+th : ty;

        // ccw from bottom left
        vertices.emplace_back(Vertex3D(ox, oy, 0.0f, txl, tyb));
        vertices.emplace_back(Vertex3D(ox + w, oy, 0.0f, txr, tyb));
        vertices.emplace_back(Vertex3D(ox + w, oy + h, 0.0f, txr, tyt));
        vertices.emplace_back(Vertex3D(ox, oy + h, 0.0f, txl, tyt));
        unsigned ix = quadCount * 4;
        indices.push_back(ix);
        indices.push_back(ix + 1);
        indices.push_back(ix + 2);
        indices.push_back(ix + 3);
        indices.push_back(ix);
        indices.push_back(ix + 2);
        // a quad has been added
        quadCount++;

    };

    t.foreach("animations", [&] (const std::string& animId, const ITab& u) {
        std::cout << "anim: " << animId << "\n";
        if (m_defaultAnimation.empty()) {
            m_defaultAnimation = animId;
        }
        AnimationInfo animInfo;
        animInfo.loop = u.get<bool>("loop");
        animInfo.loopFrame = u.get<int>("loop_frame", 0);
        u.foreach("frames", [&] (const ITab& v) {
            FrameInfo frameInfo;
            frameInfo.time = v.get<int>("ticks", 1) * (1.0f/60.0f);
            frameInfo.offset = icount;
            int n = 0;
            auto qs = v.get<py::object>("quads").cast<py::list>();
            try {
                auto x = qs[0].cast<int>();
                parseQuad(qs);
                n += 6;
            } catch (...) {
                for (const auto& q : qs) {
                    parseQuad(q.cast<pybind11::list>());
                    n += 6;
                }
            }
            frameInfo.count = n;
            animInfo.frames.push_back(frameInfo);
            icount += n;
        });
        m_animInfos[animId] = animInfo;
        a++;
    });

    std::cerr << "number of anism = " << a << "\n";

    auto mesh = std::make_shared<Mesh<Vertex3D>>(ShaderType::TEXTURE_SHADER_UNLIT);
    mesh->m_primitive = GL_TRIANGLES;
    mesh->Init(vertices, indices);
    this->addMesh(mesh);
    //m_mesh->SetDefaultAnimation(defaultAnimation);



}

//
//
//std::vector<std::string> SpriteModel::GetAnimations() const {
//    const auto& m = m_mesh->GetAnimInfo();
//    std::vector<std::string> animations;
//    for (auto& a : m) {
//        animations.push_back(a.first);
//    }
//    return animations;
//}
//
//std::string SpriteModel::GetDefaultAnimation() const {
//    return m_mesh->GetDefaultAnimation();
//}
//
//
//ShaderType SpriteModel::GetShaderType() const {
//    return TEXTURE_SHADER_UNLIT;
//}
//
//const AnimInfo* SpriteModel::GetAnimInfo() const {
//    return m_mesh->GetAnimInfo(m_mesh->GetDefaultAnimation());
//}
//
//const AnimInfo* SpriteModel::GetAnimInfo(const std::string& anim) const {
//    return m_mesh->GetAnimInfo(anim);
//}
//
//void SpriteModel::draw(Shader* shader, int offset, int count) {
//    m_mesh->draw(shader, offset, count);
//}
//
//
//std::vector<std::shared_ptr<IShape>> SpriteModel::getAttackShapes() const {
//    return std::vector<std::shared_ptr<IShape>>();
//}