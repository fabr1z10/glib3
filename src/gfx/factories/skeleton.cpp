#include <gfx/factories/skeleton.h>
#include <gfx/components/renderer.h>
#include <gfx/engine.h>
#include <gfx/components/skeletalanimator.h>
#include <gfx/components/skeletalrenderer.h>
#include <gfx/factories.h>
#include <gfx/splineanim.h>
#include <gfx/parabolicanim.h>


std::shared_ptr<SkeletalAnimation> SkeletalAnimFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    bool loop = table.Get<bool>("loop");

    std::string type = table.Get<std::string>("animtype");



    std::shared_ptr<SkeletalAnimation> anim;
    if (type == "spline") {
        luabridge::LuaRef boundary = table.Get<luabridge::LuaRef>("boundary");
        LuaTable btable(boundary);
        int boundltype{0};
        int boundrtype{0};
        double boundl{0.0};
        double boundr{0.0};
        if (btable.HasKey("periodic")) {
            boundltype = -1;
            boundrtype = -1;
        } else {
            luabridge::LuaRef left = btable.Get<luabridge::LuaRef>("left");
            luabridge::LuaRef right = btable.Get<luabridge::LuaRef>("right");
            std::string ltype = left[1].cast<std::string>();
            if (ltype == "first") {
                boundl = left[2].cast<double>();
                boundltype = 1;
            }
            std::string rtype = right[1].cast<std::string>();
            if (rtype == "first") {
                boundrtype = 1;
                boundr = right[2].cast<double>();
            }
        }
        anim = std::make_shared<SplineAnimation>(loop, boundltype, boundl, boundrtype, boundr);
    } else if (type == "parabolic") {
        auto pa = std::make_shared<ParabolicAnimation>(loop);
        anim = pa;

    }

    // load the keyframes
    std::vector<std::string> boneIds = table.GetVector<std::string>("bones", true);
    anim->setBoneIds(boneIds);
    int boneCount = boneIds.size();
    table.ProcessVector("frames", [&anim, boneCount] (luabridge::LuaRef keyframe) {
        LuaTable ft(keyframe);
        float t = ft.Get<float>("t");
        std::vector<float> angles = ft.GetVector<float>("a", true);
        if (angles.size() != boneCount) GLIB_FAIL("The number of angles in each keyframe must match the number of bones!");
        KeyFrame kf(t, angles);
        anim->addKeyFrame(kf);
    });

    // add a last keyframe equal to the first in order to loop
    //  anim->addKeyFrame(duration, firstKeyFrame);

    anim->init();
    return anim;
}

std::shared_ptr<Entity> SkeletonFactory::Create(luabridge::LuaRef &ref) {

    //GLIB_FAIL ("Don't know how to create skeletons!");
    LuaTable table(ref);
    std::string tag = table.Get<std::string>("tag", "");
    std::string modelId = table.Get<std::string>("model");
    auto model = Engine::get().GetAssetManager().GetModel(modelId);
    glm::vec3 pos = table.Get<glm::vec3>("pos", glm::vec3(0.0f));

    // create the entity
    auto entity = Ref::Create<Entity>();

    auto renderer = Ref::Create<SkeletalRenderer>(model);
    entity->AddComponent(renderer);
    if (!tag.empty()) {
        entity->SetTag(tag);
    }

    auto animator = std::make_shared<SkeletalAnimator>(model);
    entity->AddComponent(animator);

    auto factory = Engine::get().GetSceneFactory();

    // additional components
    if (table.HasKey("components")) {
        luabridge::LuaRef c = table.Get<luabridge::LuaRef>("components");
        for (int i = 0; i < c.length(); ++i) {
            luabridge::LuaRef rcomponent = c[i+1];
            auto component = factory->makeComponent(rcomponent);
            entity->AddComponent(component);
        }
    }

    entity->SetPosition(pos);
    if (table.HasKey("scale")) {
        float scale = table.Get<float>("scale");
        entity->SetScale(scale);
    }
    return entity;
//    auto animator = std::make_shared<Animator>(model);
//    entity->AddComponent(animator);
//    return entity;
//
//    GLIB_FAIL("mmm, have to create skeleton with model " << modelId << " but do not know why");
//    luabridge::LuaRef bonesRef = table.Get<luabridge::LuaRef>("bones");
//    auto factory = Engine::get().GetSceneFactory();
//
//    std::unordered_map<std::string, std::shared_ptr<Entity>> bones;
//    std::unordered_map<std::string, std::string> parentRelation;
//    std::string root;
//
//    auto animator = Ref::Create<SkeletalAnimator>();
//    table.ProcessVector("bones", [&bones, &parentRelation, &root, factory, &animator] (luabridge::LuaRef ref) {
//        // each bone generates a node
//        LuaTable boneRef (ref);
//        std::string name = boneRef.Get<std::string>("name");
//        std::string parent = boneRef.Get<std::string>("parent", "");
//        float length = boneRef.Get<float>("length");
//
//        if (!parent.empty()) {
//            parentRelation.insert(std::make_pair(name, parent));
//        } else {
//            root = name;
//        }
//        // create the bone
//        luabridge::LuaRef desc = boneRef.Get<luabridge::LuaRef>("desc");
//        auto bone = factory->makeEntity(desc);
//        animator->AddBone(name, bone.get(), length);
//        bones.insert(std::make_pair(name, bone));
//    });
//
//    for (const auto& p : parentRelation) {
//        bones.at(p.second)->AddChild(bones.at(p.first));
//    }
//
//    auto entity = Ref::Create<Entity>();
//    std::string tag = table.Get<std::string>("tag", "");
//    if (!tag.empty()) entity->SetTag(tag);
//
//    entity->AddChild(bones.at(root));
//
//
//    table.ProcessVector("animations", [&animator] (luabridge::LuaRef a) {
//        std::string name = a[1].cast<std::string>();
//        std::string animId = a[2].cast<std::string>();
//        auto anim = Engine::get().GetAssetManager().GetSkeletalAnimation(animId);
//        animator->AddAnimation(name, anim);
//    });
//
//    float loffset = table.Get<float>("l_offset_y", 0.0f);
//    float roffset = table.Get<float>("r_offset_y", 0.0f);
//    animator->setOffsetY(loffset, roffset);
//
//    entity->AddComponent(animator);
//    auto fakeRenderer = std::make_shared<Renderer>();
//    entity->AddComponent(fakeRenderer);
//    // add additional components
//    // add components
//    if (table.HasKey("components")) {
//        luabridge::LuaRef c = table.Get<luabridge::LuaRef>("components");
//        for (int i = 0; i < c.length(); ++i) {
//            luabridge::LuaRef rcomponent = c[i+1];
//            auto component = factory->makeComponent(rcomponent);
//            entity->AddComponent(component);
//        }
//    }
//
//    // add additional children
//    if (table.HasKey("children")) {
//        luabridge::LuaRef c = table.Get<luabridge::LuaRef>("children");
//        for (int i = 0; i < c.length(); ++i) {
//            luabridge::LuaRef child = c[i+1];
//            auto childEntity = factory->makeEntity(child);
//            if (childEntity != nullptr)
//                entity->AddChild(childEntity);
//        }
//    }
//
//    glm::vec3 pos = table.Get<glm::vec3>("pos", glm::vec3(0.0f));
//    entity->SetPosition(pos);
//    return entity;
//

}