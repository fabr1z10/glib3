#include <gfx/factories/skeleton.h>
#include <gfx/components/renderer.h>
#include <gfx/engine.h>
#include <gfx/components/skeletalanimator.h>
#include <gfx/factories.h>


std::shared_ptr<SkeletalAnimation> SkeletalAnimFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    float duration = table.Get<float>("duration");
    auto anim = std::make_shared<SkeletalAnimation>(duration);

    KeyFrame firstKeyFrame;
    int i = 0;
    table.ProcessVector("frames", [&anim, &i, &firstKeyFrame] (luabridge::LuaRef keyframe) {
        LuaTable ft(keyframe);
        float t = ft.Get<float>("t");
        KeyFrame kf;
        ft.ProcessVector("bones", [&kf] (luabridge::LuaRef bone) {
            std::string boneId = bone["name"].cast<std::string>();
            float angle = bone["angle"].cast<float>();
            kf.AddAngle(boneId, angle);
        });
        anim->addKeyFrame(t, kf);
        if (i == 0) {
            firstKeyFrame = kf;
        }
        i++;
    });
    // add a last keyframe equal to the first in order to loop
    anim->addKeyFrame(duration, firstKeyFrame);

    anim->init();
    return anim;
}

std::shared_ptr<Entity> SkeletonFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    luabridge::LuaRef bonesRef = table.Get<luabridge::LuaRef>("bones");
    auto factory = Engine::get().GetSceneFactory();

    std::unordered_map<std::string, std::shared_ptr<Entity>> bones;
    std::unordered_map<std::string, std::string> parentRelation;
    std::string root;

    auto animator = Ref::Create<SkeletalAnimator>();

    table.ProcessVector("bones", [&bones, &parentRelation, &root, factory, &animator] (luabridge::LuaRef ref) {
        // each bone generates a node
        LuaTable boneRef (ref);
        std::string name = boneRef.Get<std::string>("name");
        std::string parent = boneRef.Get<std::string>("parent", "");
        float length = boneRef.Get<float>("length");

        if (!parent.empty()) {
            parentRelation.insert(std::make_pair(name, parent));
        } else {
            root = name;
        }
        // create the bone
        luabridge::LuaRef desc = boneRef.Get<luabridge::LuaRef>("desc");
        auto bone = factory->makeEntity(desc);
        animator->AddBone(name, bone.get(), length);
        bones.insert(std::make_pair(name, bone));
    });

    for (const auto& p : parentRelation) {
        bones.at(p.second)->AddChild(bones.at(p.first));
    }

    auto entity = Ref::Create<Entity>();
    entity->AddChild(bones.at(root));


    table.ProcessVector("animations", [&animator] (luabridge::LuaRef a) {
        std::string name = a[1].cast<std::string>();
        std::string animId = a[2].cast<std::string>();
        auto anim = Engine::get().GetAssetManager().GetSkeletalAnimation(animId);
        animator->AddAnimation(name, anim);
    });

    entity->AddComponent(animator);

    // add additional components
    // add components
    if (table.HasKey("components")) {
        luabridge::LuaRef c = table.Get<luabridge::LuaRef>("components");
        for (int i = 0; i < c.length(); ++i) {
            luabridge::LuaRef rcomponent = c[i+1];
            auto component = factory->makeComponent(rcomponent);
            entity->AddComponent(component);
        }
    }

    // add additional children
    if (table.HasKey("children")) {
        luabridge::LuaRef c = table.Get<luabridge::LuaRef>("children");
        for (int i = 0; i < c.length(); ++i) {
            luabridge::LuaRef child = c[i+1];
            auto childEntity = factory->makeEntity(child);
            if (childEntity != nullptr)
                entity->AddChild(childEntity);
        }
    }

    glm::vec3 pos = table.Get<glm::vec3>("pos", glm::vec3(0.0f));
    entity->SetPosition(pos);
    return entity;


}