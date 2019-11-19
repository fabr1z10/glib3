#include <gfx/factories/modelfactories.h>
#include <gfx/spritemesh.h>
#include <gfx/assetman.h>
#include <gfx/engine.h>
#include <gfx/model/spritemodel.h>
#include <gfx/boxedmodel.h>
#include <gfx/model/combomodel.h>
#include <gfx/math/box.h>
#include <gfx/model/skeletalmodel.h>
#include <gfx/quadmesh.h>
#include <gfx/splineanim.h>
#include <gfx/parabolicanim.h>

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

std::shared_ptr<IModel> BoxedModelFactory::Create(luabridge::LuaRef &ref) {
    LuaTable t(ref);
    auto mesh = ReadSpriteMesh(t);
    // read the additional stuff
    auto pp = std::make_shared<BoxedModel>(mesh);
    float thickness = t.Get<float>("thickness", 0.0f);
    float dz = 0.5f * thickness;
    bool model3d = (thickness > 0.0f);
    luabridge::LuaRef an = t.Get<luabridge::LuaRef>("animations");
    // loop through animations
    for (int i = 0; i < an.length(); ++i) {
        luabridge::LuaRef at = an[i+1];
        std::string anim = at["name"].cast<std::string>();
        glm::vec4 box = LuaTable::Read<glm::vec4>(at["box"], glm::vec4(0.0f));
        if (box != glm::vec4(0.0f)) {
            pp->AddAnimationData(anim, Bounds{glm::vec3(box[0], box[1], box[0]), glm::vec3(box[2], box[3], box[2])});
        }
        luabridge::LuaRef fr = at["frames"];
        for (int j = 0; j < fr.length(); ++j) {
            luabridge::LuaRef a2 = fr[j + 1];
            // get the shape associated to this frame
            LuaTable table(a2);
            if (box != glm::vec4(0.0f)) {
                if (table.HasKey("boxes")) {
                    auto boxes = table.Get<luabridge::LuaRef>("boxes");
                    if (boxes.length() == 1) {
                        glm::vec4 box = LuaTable::Read<glm::vec4>(boxes[1]);
                        std::shared_ptr<Shape> collisionShape;
                        float width = box[2] - box[0];
                        float height = box[3] - box[1];
                        if (model3d) {
                            collisionShape = std::make_shared<Box>(width, height, thickness,
                                                                   glm::vec3(box[0], box[1], -dz));
                        } else {
                            collisionShape = std::make_shared<Rect>(width, height, glm::vec3(box[0], box[1], 0.0f));
                        }
                        pp->AddCollisionData(anim, j, collisionShape);
                    }
                } else {
                    // if no boxes field is specified for this frame, use the box at animation level
                    std::shared_ptr<Shape> collisionShape;
                    float width = box[2] - box[0];
                    float height = box[3] - box[1];
                    if (model3d) {
                        collisionShape = std::make_shared<Box>(width, height, thickness,
                                                               glm::vec3(box[0], box[1], -dz));
                    } else {
                        collisionShape = std::make_shared<Rect>(width, height, glm::vec3(box[0], box[1], 0.0f));
                    }
                    pp->AddCollisionData(anim, j, collisionShape);
                }
            } else {
                pp->AddCollisionData(anim, j, nullptr);
            }

            if (table.HasKey("attack")) {
                glm::vec4 attackBox = table.Get<glm::vec4>("attack");
                float w = attackBox[2] - attackBox[0];
                float h = attackBox[3] - attackBox[1];
                std::shared_ptr<Shape> attackShape;
                if (model3d) {
                    attackShape = std::make_shared<Box>(w, h, thickness, glm::vec3(attackBox[0], attackBox[1], -dz));
                } else {
                    attackShape = std::make_shared<Rect>(w, h, glm::vec3(attackBox[0], attackBox[1], 0.0f));
                }
                pp->AddAttackData(anim, j, attackShape);
                //attackTag = table.Get<int>("attack_tag");
            }
        }

    }
    pp->generateDebugMesh();
    return pp;


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

std::shared_ptr<IModel> SkeletalModelFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string gfx = table.Get<std::string>("gfx");
    std::cerr << " gfx = " << gfx << "\n";
    auto model = std::make_shared<SkeletalModel>();

    // load the bones
    int boneCount = 0;
    table.ProcessVector("bones", [&, &boneCount] (luabridge::LuaRef ref) {
        LuaTable bt(ref);
        std::string id = bt.Get<std::string>("id");
        glm::vec4 quad = bt.Get<glm::vec4>("quad");
        std::string parent = bt.Get<std::string>("parent", "");
        glm::vec2 origin = bt.Get<glm::vec2>("origin", glm::vec2(0.0f));
        glm::vec2 pos = bt.Get<glm::vec2>("pos", glm::vec2(0.0f));
        glm::vec2 center = bt.Get<glm::vec2>("center", glm::vec2(0.0f));
        float z = bt.Get<float>("z");
        float w = quad[2];      // TODO scale?
        float h = quad[3];
        auto mesh = std::make_shared<QuadMesh>(gfx, w, h, center, quad[0], quad[1], quad[2], quad[3]);
        auto bone = std::make_unique<Bone>();
        bone->id = boneCount++;
        bone->center = origin;
        bone->mesh = mesh;
        bone->pos = pos;
        bone->z = z;
        bone->transform[3][0] = -origin.x+pos.x;
        bone->transform[3][1] = -origin.y+pos.y;
        bone->transform[3][2] = z;
        std::cerr << "bone: " << id << ", quad = (" << quad[0] << ", " << quad[1] << ", " << quad[2] << ", " << quad[3] << ")\n";
        model->addBone(id, std::move(bone), parent);
    });

    // load the animations
    table.ProcessVector("animations", [&] (luabridge::LuaRef ref) {
        LuaTable atable(ref);
        std::string id = atable.Get<std::string>("id");
        bool loop = atable.Get<bool>("loop");

        std::string type = atable.Get<std::string>("animtype");

        std::shared_ptr<SkeletalAnimation> anim;
        if (type == "periodic_spline") {
            int boundltype {-1};
            int boundrtype {-1};
            double boundl {0.0};
            double boundr {0.0};
            anim = std::make_shared<SplineAnimation>(loop, boundltype, boundl, boundrtype, boundr);
        } else if (type == "monotone_spline") {
            auto pa = std::make_shared<ParabolicAnimation>(loop);
            anim = pa;
        }

        // load the keyframes
        //std::vector<std::string> boneIds = table.GetVector<std::string>("bones", true);
        //anim->setBoneIds(boneIds);
        //int boneCount = boneIds.size();
        atable.ProcessVector("frames", [&anim] (luabridge::LuaRef keyframe) {
            LuaTable ft(keyframe);
            float t = ft.Get<float>("t");
            std::vector<float> angles = ft.GetVector<float>("a", true);
            //if (angles.size() != boneCount) GLIB_FAIL("The number of angles in each keyframe must match the number of bones!");
            KeyFrame kf(t, angles);
            anim->addKeyFrame(kf);
        });

        // add a last keyframe equal to the first in order to loop
        //  anim->addKeyFrame(duration, firstKeyFrame);
        if (atable.HasKey("box")) {
            glm::vec4 box = atable.Get<glm::vec4>("box");
            anim->setBounds(box[2], box[3], glm::vec2(box[0], box[1]));
        }
        anim->init();
        model->addAnimation(id, anim);
        return anim;


    });

    return model;

}