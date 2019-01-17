#include <gfx/factories.h>
#include <gfx/spritemesh.h>
#include <gfx/assetman.h>

std::unique_ptr<IMesh> SpriteFactory::Create (luabridge::LuaRef& ref) {

    LuaTable t(ref);
    float ppu = t.Get<float>("ppu", 1.0);
    std::string sheetName = t.Get<std::string>("sheet");
    luabridge::LuaRef an = t.Get<luabridge::LuaRef>("animations");
    std::vector<Animation> anims;
    for (int i = 0; i < an.length(); ++i) {
        Animation animation;
        luabridge::LuaRef a = an[i+1];
        LuaTable at (a);
        animation.name = at.Get<std::string>("name");
        animation.loop = at.Get<bool>("loop", true);
        luabridge::LuaRef fr = at.Get<luabridge::LuaRef>("frames");
        for (int j = 0; j < fr.length(); ++j) {
            luabridge::LuaRef a2 = fr[j+1];
            LuaTable ft (a2);
            Frame frame;
            frame.time = ft.Get<float>("duration");
            luabridge::LuaRef qu = ft.Get<luabridge::LuaRef>("quads");
            for (int k = 0; k < qu.length(); ++k) {
                luabridge::LuaRef a3 = qu[k+1];
                LuaTable qt (a3);
                Quad q;
                q.x = qt.Get<float>("x");
                q.y = qt.Get<float>("y");
                q.z = qt.Get<float>("z", 0.0f);
                q.width = qt.Get<float>("width");
                q.height = qt.Get<float>("height");
                glm::vec2 anchor = qt.Get<glm::vec2>("anchor", glm::vec2(0.0f));
                q.anchorx = anchor.x;
                q.anchory = anchor.y;
                frame.quads.push_back(q);
            }
            animation.frames.push_back(frame);
        }
        anims.push_back(animation);
    }
    auto mesh = std::unique_ptr<SpriteMesh>(new SpriteMesh(ppu, sheetName, anims));

    return std::move(mesh);
}

