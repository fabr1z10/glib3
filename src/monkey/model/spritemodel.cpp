#include <monkey/model/spritemodel.h>
#include <monkey/entity.h>
#include <iostream>
#include <monkey/error.h>

namespace py = pybind11;

SpriteModel::SpriteModel (const YamlWrapper& t) : IModel() {
    m_shareable = true;

    auto sheetId = t.get<std::string>("sheet");
    auto ppu = t.get<float>("ppu", 1.0);

    std::string defaultAnimation;

    auto tex = Engine::get().GetAssetManager().GetTex(sheetId);

    float texWidth = static_cast<float>(tex->GetWidth());
    float texHeight = static_cast<float>(tex->GetHeight());


    float dt = Engine::get().getMainTable().get<float>("frame_time");
    std::vector<Vertex3D> vertices;
    std::vector<unsigned int> indices;
    unsigned quadCount {0};

    auto addQuad = [&] (const std::vector<int>& q) {
        int x = q[0];                // top left x coord in sheet
        int y = q[1];                // top left y coord in sheet
        int width = q[2];            // width in pixels
        int height = q[3];           // height in pixels
        float z = 0.0f;
        // width and height in pixel

        float w = width / ppu;
        float h = height / ppu;
        float tx = x / texWidth;
        float ty = y / texHeight;
        float tw = width / texWidth;
        float th = height / texHeight;

        // check if quad has anchor
        glm::vec2 anchor(0.0f);
        auto qs = q.size();
        if (qs > 4) {
            anchor.x = q[4];
            anchor.y = q[5];
        }
        bool flipX = qs > 6 ? (q[6] == 1) : false;
        bool flipY = qs > 7 ? (q[7] == 1) : false;
        float tx0 = flipX ? tx+tw : tx;
        float tx1 = flipX ? tx : tx + tw;
        float ty0 = flipY ? ty : ty+th;
        float ty1 = flipY ? ty+th : ty;

        glm::vec2 bottomLeft{-anchor.x / ppu, -anchor.y / ppu};
//        float tx0 = tx;
//        float tx1 = tx + tw;
//        float ty0 = ty + th;
//        float ty1 = ty;
        vertices.emplace_back(Vertex3D(bottomLeft.x, bottomLeft.y, z, tx0, ty0));
        vertices.emplace_back(Vertex3D(bottomLeft.x + w, bottomLeft.y, z, tx1, ty0));
        vertices.emplace_back(Vertex3D(bottomLeft.x + w, bottomLeft.y + h, z, tx1, ty1));
        vertices.emplace_back(Vertex3D(bottomLeft.x, bottomLeft.y + h, z, tx0, ty1));
        unsigned ix = quadCount * 4;
        indices.push_back(ix);
        indices.push_back(ix + 1);
        indices.push_back(ix + 3);
        indices.push_back(ix + 3);
        indices.push_back(ix + 2);
        indices.push_back(ix + 1);

    };

    // this is the routine which is used if you specify the frames using the frames desc
    auto rf = [&] (YAML::Node& d, AnimInfo& ai) {

        // EACH FRAME has
        // quads (mandatory)
        // shape (a collision shape -> if not, the anim shape is assigned, if any)
        // cast shape
        auto frames = d.get<py::list>("elements");
        for (auto frame : frames) {
            PyDict a(frame.cast<py::dict>());
            FrameInfo frameInfo;
            frameInfo.duration = a.get<float>("ticks") * (1.0f/60.0f);
            frameInfo.flipx = a.get<bool>("flipx", false);
            frameInfo.angle = a.get<float>("angle", 0.0f);
            frameInfo.offset = 6 * quadCount;
            frameInfo.move = true;
            frameInfo.origin = glm::vec2(0.0f);
            frameInfo.translation = a.get<glm::vec2>("pos", glm::vec2(0.0f));
            if (a.hasKey("alpha")) {
            	frameInfo.applyAlpha = true;
            	frameInfo.alpha = a.get<float>("alpha") / 256.0f;
            }
            int fq=0;
            a.foreach<py::list>("quads", [&] (const py::list& l) {
                auto p = l.cast<std::vector<int>>();
                //p[0] *= texWidth;
                //p[1] *= texHeight;
                // p[2] *= texWidth;
                //p[3] *= texHeight;
                addQuad(p);
                quadCount++;
                fq++;
            });
            frameInfo.count = 6 * fq;
            ai.frameInfo.push_back(frameInfo);

        }
    };


    m_mesh = std::make_shared<SpriteMesh>(sheetId);
    auto anims = t.get<YAML::Node>("animations");

    for (auto anim : anims) {
        AnimInfo animInfo;
        auto animId = anim.first.as<std::string>();
        if (defaultAnimation.empty()) {
            defaultAnimation = animId;
        }
        auto animData = anim.second;
        animInfo.loop = animData["loop"].as<bool>( true);
        animInfo.loopFrame = animData["loop_frame"].as<int>(0);
        if (animData["elements"]) {
            rf (animData, animInfo);
        } else {
            auto frames = animData.get<py::list>("frames");
            for (auto frame : frames) {
                FrameInfo frameInfo;
                frameInfo.duration = dt;
                frameInfo.offset = 6 * quadCount;

                // check if this frame is defined as a vec of ints
                int frameQuads = 0;
                try {
                    auto fi = frame.cast<std::vector<int>>();
                    addQuad(fi);
                    quadCount++;
                    frameQuads = 1;
                    frameInfo.count = 6;
                    animInfo.frameInfo.push_back(frameInfo);
                    continue;
                } catch (...) {}

                // check if this frame is defined as a list of quads
                try {
                    auto quads = frame.cast<py::list>();
                    for (auto quad : quads) {
                        std::vector<int> quadInfo = quad.cast<std::vector<int>>();
                        addQuad(quadInfo);
                        quadCount++;
                        frameQuads++;
                    }
                    frameInfo.count = 6 * frameQuads;
                    animInfo.frameInfo.push_back(frameInfo);
                } catch (...) {
                    GLIB_FAIL("Cannot read frame")
                }

            }
        }
        animInfo.frameCount = animInfo.frameInfo.size();
        m_mesh->AddAnimInfo(animId, animInfo);
    }
    m_mesh->Init(vertices, indices);
    m_mesh->SetDefaultAnimation(defaultAnimation);



}



std::vector<std::string> SpriteModel::GetAnimations() const {
    const auto& m = m_mesh->GetAnimInfo();
    std::vector<std::string> animations;
    for (auto& a : m) {
        animations.push_back(a.first);
    }
    return animations;
}

std::string SpriteModel::GetDefaultAnimation() const {
    return m_mesh->GetDefaultAnimation();
}


ShaderType SpriteModel::GetShaderType() const {
    return TEXTURE_SHADER_UNLIT;
}

const AnimInfo* SpriteModel::GetAnimInfo() const {
    return m_mesh->GetAnimInfo(m_mesh->GetDefaultAnimation());
}

const AnimInfo* SpriteModel::GetAnimInfo(const std::string& anim) const {
    return m_mesh->GetAnimInfo(anim);
}

void SpriteModel::Draw(Shader* shader, int offset, int count) {
    m_mesh->Draw(shader, offset, count);
}


std::vector<std::shared_ptr<IShape>> SpriteModel::getAttackShapes() const {
    return std::vector<std::shared_ptr<IShape>>();
}