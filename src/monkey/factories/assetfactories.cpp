#include <monkey/factories/modelfactories.h>
#include <monkey/spritemesh.h>
#include <monkey/assetman.h>
#include <monkey/engine.h>
#include <monkey/model/spritemodel.h>
#include <monkey/model/boxedmodel.h>
#include <monkey/model/combomodel.h>
#include <monkey/math/box.h>
#include <monkey/model/skeletalmodel.h>
#include <monkey/quadmesh.h>
#include <monkey/splineanim.h>
#include <monkey/parabolicanim.h>

std::shared_ptr<SpriteMesh> SimpleModelFactory::ReadSpriteMesh(LuaTable& t) {

    std::string sheetName = t.Get<std::string>("sheet");
    std::string defaultAnimation;
    float ppu = t.Get<float>("ppu", 1.0);

    auto tex = Engine::get().GetAssetManager().GetTex(sheetName);
    float texWidth = static_cast<float>(tex->GetWidth());
    float texHeight = static_cast<float>(tex->GetHeight());

    std::vector<Vertex3D> vertices;
    std::vector<unsigned int> indices;

    auto mesh = std::make_shared<SpriteMesh>(sheetName);

    luabridge::LuaRef an = t.Get<luabridge::LuaRef>("animations");
    int quadCount {0};

    // loop through animations
    for (int i = 0; i < an.length(); ++i) {

        luabridge::LuaRef a = an[i+1];
        LuaTable at (a);
        std::string animName = at.Get<std::string>("name");
        AnimInfo animInfo;
        animInfo.loop = at.Get<bool>("loop", true);
        luabridge::LuaRef fr = at.Get<luabridge::LuaRef>("frames");
        if (i == 0) {
            defaultAnimation = animName;
        }
        // loop through frames
        for (int j = 0; j < fr.length(); ++j) {
            luabridge::LuaRef a2 = fr[j+1];
            LuaTable ft (a2);
            FrameInfo frame;
            frame.duration = ft.Get<float>("duration");
            luabridge::LuaRef qu = ft.Get<luabridge::LuaRef>("quads");
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
                luabridge::LuaRef a4 = qt.Get<luabridge::LuaRef>("id");
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
        mesh->AddAnimInfo(animName, animInfo);
    }
    mesh->Init(vertices, indices);
    mesh->SetDefaultAnimation(defaultAnimation);
    return mesh;
}

std::shared_ptr<IModel> SimpleModelFactory::Create (luabridge::LuaRef& ref) {

    LuaTable t(ref);
    auto mesh = ReadSpriteMesh(t);
    std::unique_ptr<IModel> m(new SpriteModel(mesh));
    return m;
}



std::shared_ptr<IModel> GenericModel3DFactory::Create(luabridge::LuaRef &ref) {
    // reading a 3D model

    LuaTable table(ref);

    // create a combo model
    auto model = std::make_shared<ComboModel>();

    table.ProcessVector("meshes", [&] (luabridge::LuaRef ref) {
        LuaTable meshTable(ref);
        std::string text = meshTable.Get<std::string>("texture");
        auto mesh = std::make_shared<TexturedMesh<Vertex3DN>>(TEXTURE_SHADER_LIGHT, GL_TRIANGLES, text);
        std::vector<Vertex3DN> vertices;
        std::vector<unsigned int> indices = meshTable.GetVector<unsigned int>("indices");
        meshTable.ProcessVector("vertices", [&vertices] (luabridge::LuaRef ref) {
            std::vector<float> data = ReadVector<float>(ref);
            vertices.push_back(Vertex3DN(data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]));
        });
        mesh->Init(vertices, indices);
        model->AddMesh(mesh);
    });
    return model;

}

