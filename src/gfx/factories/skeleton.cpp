#include <gfx/factories/skeleton.h>
#include <gfx/engine.h>

std::shared_ptr<Entity> SkeletonFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    luabridge::LuaRef bonesRef = table.Get<luabridge::LuaRef>("bones");
    auto factory = Engine::get().GetSceneFactory();

    std::unordered_map<std::string, std::shared_ptr<Entity>> bones;

    table.ProcessVector("bones", [&bones, factory] (luabridge::LuaRef ref) {
        // each bone generates a node
        LuaTable boneRef (ref);
        std::string name = boneRef.Get<std::string>("name");

        // create the bone
        luabridge::LuaRef desc = boneRef.Get<luabridge::LuaRef>("desc");
        auto bone = factory->makeEntity(desc);
        bones.insert(std::make_pair(name, bone));


    });

}