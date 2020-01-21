#include <platformer/platformerfactory.h>
#include <platformer/factories.h>
#include <monkey/entitywrapper.h>
#include <platformer/luaext.h>
#include <platformer/factories/building.h>
#include <monkey/engine.h>
#include <monkey/entity.h>
#include <monkey/dynamicworld.h>

PlatformerFactory::PlatformerFactory() : SceneFactory() {

    m_componentFactory.Add<EnemyInputCompFactory>("enemyinput");
    m_componentFactory.Add<BasicEnemyInputCompFactory>("basicenemyinput");
    m_componentFactory.Add<Enemy3DInputCompFactory>("enemy3dinput");

    m_activityFactory.Add<DropCharactersActFactory>("dropcharacters");
    m_activityFactory.Add<SetEnemyDirActFactory>("setenemydir");

    m_stateFactory.Add<Walk4WayStateFactory>("walk4w");
    m_stateFactory.Add<WalkSideFactory>("walkside");
    m_stateFactory.Add<Walk3DFactory>("walk3d");
    m_stateFactory.Add<EnemyWalk25StateFactory>("enemywalk25");

    m_stateFactory.Add<Jump2DFactory>("jump");
    m_stateFactory.Add<Jump3DFactory>("jump3d");

    m_stateFactory.Add<HitFactory>("hit");
    m_stateFactory.Add<DuckFactory>("duck");
    m_stateFactory.Add<HitJumpFactory>("hitj");
    m_stateFactory.Add<NilStateFactory>("nil");
    m_stateFactory.Add<CustomHit1StateFactory>("ch1");

    m_modelFactory.Add<BuildingFactory>("building");


}


void PlatformerFactory::extendLua() {

    luabridge::getGlobalNamespace(LuaWrapper::L)
            .beginNamespace("monkey")
            .addFunction("register_platform", &RegisterToPlatform)
            .addFunction("unregister_platform", &UnregisterToPlatform)
            .addFunction("set_dir", &SetEnemyDir);

}


//std::shared_ptr<Entity> PlatformerFactory::Create() {
//
//    // get current room
//    LuaTable vars (LuaWrapper::GetGlobal("variables"));
//    std::string room = vars.Get<std::string>("_room");
//
//    std::cout << "=================================\n";
//    std::cout << "Loading room: "<< room << std::endl;
//    std::cout << "=================================\n";
//    LuaWrapper::Load(Engine::get().GetDirectory() + "rooms/" + room + ".lua");
//
//    // Create the local assets
//    luabridge::LuaRef roomRef = luabridge::getGlobal(LuaWrapper::L, "room");
//    LuaTable roomTable(roomRef);
//
//    if (roomTable.HasKey("init")) {
//        luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("init");
//        r1();
//    }
//
//    if (roomTable.HasKey("engines")) {
//        luabridge::LuaRef engines = roomTable.Get<luabridge::LuaRef>("engines");
//        for (int i = 0; i < engines.length(); ++i) {
//            luabridge::LuaRef e = engines[i+1];
//            auto runner = makeRunner(e);
//            Engine::get().AddRunner(runner);
//        }
//    }
//
//
//    // load room-specific assets
////    auto roomAssets = roomTable.GetVector<std::string>("assets");
////    for (auto& a : roomAssets) {
////        // load the asset
////        LoadModel(a);
////    }
//
//    // read the scene tree
//    auto rootNode = std::make_shared<Entity>();
//    rootNode->SetTag("_root");
//    luabridge::LuaRef rscene = roomTable.Get<luabridge::LuaRef>("scene");
//    for (int i = 0; i < rscene.length(); ++i) {
//        luabridge::LuaRef rnode = rscene[i+1];
//        auto node  = makeEntity(rnode);
//        rootNode->AddChild(node);
//    }
//
//
//
//    // launch the start script
//    if (roomTable.HasKey("start")) {
//        luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("start");
//        r1();
//    }
//
//    // add the dynamic world builder
//    auto dynBuilder = std::make_shared<DynamicWorldBuilder>(256,256);
//    auto cam = Ref::Get<Camera>("maincam");
//    if (roomTable.HasKey("dynamic")) {
//        luabridge::LuaRef rdyn = roomTable.Get<luabridge::LuaRef>("dynamic");
//        for (int i = 0; i < rdyn.length(); ++i) {
//
//            luabridge::LuaRef rnode = rdyn[i+1];
//            std::string parent = rnode["parent"].cast<std::string>();
//            auto p = Ref::Get<Entity>(parent);
//            luabridge::LuaRef rChildren = rnode["children"];
//            for (int j = 0; j < rChildren.length(); j++) {
//                luabridge::LuaRef rChild = rChildren[j+1];
//                auto node  = makeEntity(rChild);
//                dynBuilder->AddItem(p, node);
//            }
//        }
//    }
//    dynBuilder->SetCamera(cam.get());
//    Engine::get().AddRunner(dynBuilder);
//
//    return rootNode;
//
//}
