#include <gfx/factories.h>
#include <gfx/spritemesh.h>
#include <gfx/assetman.h>
#include <gfx/engine.h>
#include <gfx/simplemodel.h>
#include <gfx/compositemodel.h>
#include <gfx/imodel.h>

std::unique_ptr<IModel> CompositeModelFactory::Create (luabridge::LuaRef& ref) {

    LuaTable t(ref);
    std::string id = t.Get<std::string>("id");
    std::unique_ptr<CompositeModel> model(new CompositeModel);
    luabridge::LuaRef comps = t.Get<luabridge::LuaRef>("components");
    lua_loop_array(comps, [&model] (const LuaTable& table) {
        ModelComponent component;
        std::string name = table.Get<std::string>("name");
        std::string parent = table.Get<std::string>("parent", "");
        std::string mesh = table.Get<std::string>("mesh");
        SimpleModel* m = dynamic_cast<SimpleModel*>(Engine::get().GetAssetManager().GetModel(mesh).get());
        if (model == nullptr) {
            GLIB_FAIL("Composite models requires simple model components. " << mesh << " is not a simpòe model.");
        }
        model->AddComponent(name, m, parent);
    });
    return model;
}

std::unique_ptr<IModel> SimpleModelFactory::Create (luabridge::LuaRef& ref) {

    LuaTable t(ref);
    float ppu = t.Get<float>("ppu", 1.0);
    std::string sheetName = t.Get<std::string>("sheet");
    luabridge::LuaRef an = t.Get<luabridge::LuaRef>("animations");

    std::string defaultAnimation;
    auto tex = Engine::get().GetAssetManager().GetTexture(sheetName);
    float texWidth = static_cast<float>(tex->GetWidth());
    float texHeight = static_cast<float>(tex->GetHeight());
    int quadCount {0};
    std::vector<Vertex3D> vertices;
    std::vector<unsigned int> indices;

    auto mesh = std::make_shared<SpriteMesh>(sheetName);

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
            for (int k = 0; k < n; ++k) {
                luabridge::LuaRef a3 = qu[k+1];
                LuaTable qt (a3);
                float x = qt.Get<float>("x");
                float y = qt.Get<float>("y");
                float z = qt.Get<float>("z", 0.0f);
                float width = qt.Get<float>("width");
                float height = qt.Get<float>("height");
                float tx = x / texWidth;
                float ty = y / texHeight;
                float tw = width / texWidth;
                float th = height / texHeight;
                glm::vec2 anchor = qt.Get<glm::vec2>("anchor", glm::vec2(0.0f));
                glm::vec2 bottomLeft { -anchor.x / ppu, -anchor.y / ppu };

                // for each quad, add 4 vertices and 6 quads
                vertices.emplace_back(Vertex3D(bottomLeft.x, bottomLeft.y, z, tx, ty + th));
                vertices.emplace_back(Vertex3D(bottomLeft.x + width, bottomLeft.y, z, tx + tw, ty + th));
                vertices.emplace_back(Vertex3D(bottomLeft.x + width, bottomLeft.y + height, z, tx + tw, ty));
                vertices.emplace_back(Vertex3D(bottomLeft.x, bottomLeft.y + height, z, tx, ty));
                int ix = quadCount * 4;
                indices.push_back(ix);
                indices.push_back(ix + 1);
                indices.push_back(ix + 3);
                indices.push_back(ix + 3);
                indices.push_back(ix + 2);
                indices.push_back(ix + 1);

                quadCount++;
            }
            animInfo.frameCount = animInfo.frameInfo.size();
            animInfo.frameInfo.push_back(frame);
        }
        mesh->AddAnimInfo(animName, animInfo);
    }
    mesh->Init(vertices, indices);
    mesh->SetDefaultAnimation(defaultAnimation);
    std::unique_ptr<IModel> m(new SimpleModel(mesh));
    return m;
}

