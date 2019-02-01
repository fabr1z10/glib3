#include <gfx/factories.h>
#include <gfx/spritemesh.h>
#include <gfx/assetman.h>
#include <gfx/engine.h>
#include <gfx/simplemodel.h>
#include <gfx/compositemodel.h>
#include <gfx/imodel.h>

std::unique_ptr<IModel> CompositeModelFactory::Create (luabridge::LuaRef& ref) {

    LuaTable t(ref);

    std::unique_ptr<CompositeModel> model(new CompositeModel);
    luabridge::LuaRef comps = t.Get<luabridge::LuaRef>("components");
    lua_loop_array(comps, [&model] (const LuaTable& table) {
        ModelComponent component;
        std::string name = table.Get<std::string>("name");
        std::string parent = table.Get<std::string>("parent", "");
        std::string mesh = table.Get<std::string>("mesh");
        // DEPENDENCIES. IF simplemodls are not loaded, then do it now!

        SimpleModel* m = dynamic_cast<SimpleModel*>(Engine::get().GetAssetManager().GetModel(mesh).get());
        if (model == nullptr) {
            // mmmh the model is not available, try to get it now
//            auto sceneFactory = Engine::get().GetSceneFactory();
//            sceneFactory->LoadModel(mesh);
//            m = dynamic_cast<SimpleModel*>(Engine::get().GetAssetManager().GetModel(mesh).get());
        }
        model->AddComponent(name, m, parent);
    });

    luabridge::LuaRef anims = t.Get<luabridge::LuaRef>("animations");
    lua_loop_array(anims, [&model] (const LuaTable& table) {
        std::string name = table.Get<std::string>("name");
        std::vector<AnimationDefinition> def;
        luabridge::LuaRef adef = table.Get<luabridge::LuaRef>("anims");
        for (int i = 0; i< adef.length(); ++i) {
            luabridge::LuaRef aa = adef[i+1];
            LuaTable aatab(aa);
            std::string comp = aatab.Get<std::string>("name");
            std::string anim = aatab.Get<std::string>("anim");
            glm::vec3 pos = aatab.Get<glm::vec3>("pos", glm::vec3(0.0f));
            def.push_back(AnimationDefinition{comp, anim, pos});
        }
        model->AddAnimation(name, def);
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
    std::unique_ptr<IModel> m(new SimpleModel(mesh));
    return m;
}

