#include <monkey/model/spritemodel.h>
#include <monkey/entity.h>
#include <iostream>
#include <monkey/error.h>

SpriteModel::SpriteModel (const LuaTable& t) : IModel() {

    std::string sheetId = t.Get<std::string>("sheet");
    float ppu = t.Get<float>("ppu", 1.0);

    std::string defaultAnimation;

    auto tex = Engine::get().GetAssetManager().GetTex(sheetId);

    float texWidth = static_cast<float>(tex->GetWidth());
    float texHeight = static_cast<float>(tex->GetHeight());

    std::vector<Vertex3D> vertices;
    std::vector<unsigned int> indices;

    m_mesh = std::make_shared<SpriteMesh>(sheetId);

    auto an = t.Get<luabridge::LuaRef>("animations");

    int quadCount {0};

    // loop through animations
    for (int i = 0; i < an.length(); ++i) {

        luabridge::LuaRef a = an[i+1];
        LuaTable at (a);
        auto animName = at.Get<std::string>("name");
        AnimInfo animInfo;
        animInfo.loop = at.Get<bool>("loop", true);
        auto fr = at.Get<luabridge::LuaRef>("frames");
        if (i == 0) {
            defaultAnimation = animName;
        }
        // loop through frames
        for (int j = 0; j < fr.length(); ++j) {
            luabridge::LuaRef a2 = fr[j+1];
            LuaTable ft (a2);
            FrameInfo frame;
            frame.duration = ft.Get<float>("duration");
            auto qu = ft.Get<luabridge::LuaRef>("quads");
            // loop through quads
            int n = qu.length();
            frame.offset = 6*quadCount;
            frame.count = 6*n;

            if (ft.HasKey("angle") || ft.HasKey("delta")) {
                frame.move = true;
                frame.flipx = ft.Get<bool>("flip", false);
                frame.angle=ft.Get<float>("angle", 0.0f);
                frame.origin =  ft.Get<glm::vec2>("origin", glm::vec2(0.0f));;
                frame.translation =  ft.Get<glm::vec2>("delta", glm::vec2(0.0f));;
            }


            for (int k = 0; k < n; ++k) {
                luabridge::LuaRef a3 = qu[k+1];
                LuaTable qt (a3);
                auto a4 = qt.Get<luabridge::LuaRef>("id");
                LuaTable quadTable (a4);

                float x = quadTable.Get<float>("x");
                float y = quadTable.Get<float>("y");
                float z = quadTable.Get<float>("z", 0.0f);
                // width and height in pixels, the quad size must be rescaled by ppu
                float width = quadTable.Get<float>("width");
                float height = quadTable.Get<float>("height");
                float tx = x / texWidth;
                float ty = y / texHeight;
                float tw = width / texWidth;
                float th = height / texHeight;
                glm::vec2 anchor = quadTable.Get<glm::vec2>("anchor", glm::vec2(0.0f));
                glm::vec2 bottomLeft { -anchor.x / ppu, -anchor.y / ppu };

                bool flipX = qt.Get<bool>("flipx", false);
                bool flipY = qt.Get<bool>("flipy", false);
                glm::vec2 pos = qt.Get<glm::vec2>("pos", glm::vec2(0.0f));
                float zPos = qt.Get<float>("z", 0.0f);
                z += zPos;
                float tx0 = flipX ? tx+tw : tx;
                float tx1 = flipX ? tx : tx + tw;
                float ty0 = flipY ? ty : ty+th;
                float ty1 = flipY ? ty+th : ty;
                bottomLeft += pos;
                // for each quad, add 4 vertices and 6 quads
                vertices.emplace_back(Vertex3D(bottomLeft.x, bottomLeft.y, z, tx0, ty0));
                vertices.emplace_back(Vertex3D(bottomLeft.x + width, bottomLeft.y, z, tx1, ty0));
                vertices.emplace_back(Vertex3D(bottomLeft.x + width, bottomLeft.y + height, z, tx1, ty1));
                vertices.emplace_back(Vertex3D(bottomLeft.x, bottomLeft.y + height, z, tx0, ty1));
                int ix = quadCount * 4;
                indices.push_back(ix);
                indices.push_back(ix + 1);
                indices.push_back(ix + 3);
                indices.push_back(ix + 3);
                indices.push_back(ix + 2);
                indices.push_back(ix + 1);

                quadCount++;
            }
            animInfo.frameInfo.push_back(frame);
        }
        animInfo.frameCount = animInfo.frameInfo.size();
        m_mesh->AddAnimInfo(animName, animInfo);
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
    return TEXTURE_SHADER;
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
