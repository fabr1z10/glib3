#include <gfx/factories/skeleton.h>
#include <gfx/components/renderer.h>
#include <gfx/engine.h>

std::shared_ptr<Entity> SkeletonFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    luabridge::LuaRef bonesRef = table.Get<luabridge::LuaRef>("bones");
    auto factory = Engine::get().GetSceneFactory();

    std::unordered_map<std::string, std::shared_ptr<Entity>> bones;
    std::unordered_map<std::string, std::string> parentRelation;
    std::string root;
    table.ProcessVector("bones", [&bones, &parentRelation, &root, factory] (luabridge::LuaRef ref) {
        // each bone generates a node
        LuaTable boneRef (ref);
        std::string name = boneRef.Get<std::string>("name");
        std::string parent = boneRef.Get<std::string>("parent", "");

        if (!parent.empty()) {
            parentRelation.insert(std::make_pair(name, parent));
        } else {
            root = name;
        }
        // create the bone
        luabridge::LuaRef desc = boneRef.Get<luabridge::LuaRef>("desc");
        auto bone = factory->makeEntity(desc);
        bones.insert(std::make_pair(name, bone));
    });

    for (const auto& p : parentRelation) {
        bones.at(p.second)->AddChild(bones.at(p.first));
    }

    auto entity = Ref::Create<Entity>();
    entity->AddChild(bones.at(root));
    return entity;


}