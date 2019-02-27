#include <platformer/platformerfactory.h>
#include <platformer/factories.h>
#include <gfx/entitywrapper.h>
#include <platformer/luaext.h>
#include <gfx/engine.h>
#include <gfx/entity.h>
#include <gfx/dynamicworld.h>
#include <platformer/characterstatemachine.h>

PlatformerFactory::PlatformerFactory() : SceneFactory() {

    // platformer states
//    m_stateBehaviorFactory.Add<Idle2DStateFactory>("idle2d");
//    m_stateBehaviorFactory.Add<Walk2DStateFactory>("walk2d");
//    m_stateBehaviorFactory.Add<Jump2DStateFactory>("jump2d");
//    m_stateBehaviorFactory.Add<EnemyWalk2DStateFactory>("enemywalk2d");
//    m_stateBehaviorFactory.Add<EnemyBounce2DStateFactory>("enemybounce2d");

    m_componentFactory.Add<CharacterStateCompFactory>("characterstate");

    m_activityFactory.Add<DropCharactersActFactory>("dropcharacters");

}

void Ciao(EntityWrapper* p, const std::string& key, luabridge::LuaRef value) {
    p->m_underlying->GetComponent<CharacterStateMachine>()->UpdateAddInfo(key, value);
}


void PlatformerFactory::extendLua() {

    luabridge::getGlobalNamespace(LuaWrapper::L)
            .beginNamespace("monkey")
            .addFunction("register_platform", &RegisterToPlatform)
            .addFunction("unregister_platform", &UnregisterToPlatform)
            .addFunction("set2", &Ciao);

}


std::shared_ptr<Entity> PlatformerFactory::Create() {

    // get current room
    LuaTable vars (LuaWrapper::GetGlobal("variables"));
    std::string room = vars.Get<std::string>("_room");

    std::cout << "=================================\n";
    std::cout << "Loading room: "<< room << std::endl;
    std::cout << "=================================\n";
    LuaWrapper::Load(Engine::get().GetDirectory() + "rooms/" + room + ".lua");

    // Create the local assets
    luabridge::LuaRef roomRef = luabridge::getGlobal(LuaWrapper::L, "room");
    LuaTable roomTable(roomRef);

    if (roomTable.HasKey("init")) {
        luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("init");
        r1();
    }

    if (roomTable.HasKey("engines")) {
        luabridge::LuaRef engines = roomTable.Get<luabridge::LuaRef>("engines");
        for (int i = 0; i < engines.length(); ++i) {
            luabridge::LuaRef e = engines[i+1];
            auto runner = GetShared<Runner>(e);
            Engine::get().AddRunner(runner);
        }
    }


    // load room-specific assets
//    auto roomAssets = roomTable.GetVector<std::string>("assets");
//    for (auto& a : roomAssets) {
//        // load the asset
//        LoadModel(a);
//    }

    // read the scene tree
    auto rootNode = std::make_shared<Entity>();
    rootNode->SetTag("_root");
    luabridge::LuaRef rscene = roomTable.Get<luabridge::LuaRef>("scene");
    for (int i = 0; i < rscene.length(); ++i) {
        luabridge::LuaRef rnode = rscene[i+1];
        auto node  = GetShared<Entity>(rnode);
        rootNode->AddChild(node);
    }



    // launch the start script
    if (roomTable.HasKey("start")) {
        luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("start");
        r1();
    }

    // add the dynamic world builder
    auto dynBuilder = std::make_shared<DynamicWorldBuilder>(256,256);
    Camera* cam = Engine::get().GetRef<Camera>("maincam");
    if (roomTable.HasKey("dynamic")) {
        luabridge::LuaRef rdyn = roomTable.Get<luabridge::LuaRef>("dynamic");
        for (int i = 0; i < rdyn.length(); ++i) {
            
            luabridge::LuaRef rnode = rdyn[i+1];
            std::string parent = rnode["parent"].cast<std::string>();
            Entity* p = Engine::get().GetRef<Entity>(parent);
            luabridge::LuaRef rChildren = rnode["children"];
            for (int j = 0; j < rChildren.length(); j++) {
                luabridge::LuaRef rChild = rChildren[j+1];
                auto node  = GetShared<Entity>(rChild);
                dynBuilder->AddItem(p, node);
            }
        }
    }
    dynBuilder->SetCamera(cam);
    Engine::get().AddRunner(dynBuilder);

    return rootNode;

}
