#include <gfx/scenefactory.h>
#include <gfx/factories.h>
#include <gfx/monkey.h>
#include <iostream>

SceneFactory::SceneFactory() {
    //m_runnerFactory.Add<HotSpotManagerFactory>("hotspotmanager");
    m_runnerFactory.Add<SchedulerFactory>("scheduler");
    m_runnerFactory.Add<CollisionEngineFactory>("collision");

    m_meshFactory.Add<SpriteFactory>("sprite");

    m_entityFactory.Add<EntityFactory>("default");

    m_cameraFactory.Add<OrthoCamFactory>("ortho");
    m_cameraFactory.Add<PerspectiveCamFactory>("perspective");

    m_componentFactory.Add<LuaKeyboardComponentFactory>("luakey");
    m_componentFactory.Add<GfxComponentFactory>("gfx");
    m_componentFactory.Add<ColliderComponentFactory>("collider");
    m_componentFactory.Add<MultiColliderComponentFactory>("multicollider");

    m_componentFactory.Add<Controller2DComponentFactory>("controller2d");
    m_componentFactory.Add<Dynamics2DComponentFactory>("dynamics2d");
    m_componentFactory.Add<StateMachineComponentFactory>("statemachine");
    m_componentFactory.Add<FollowComponentFactory>("follow");
    m_componentFactory.Add<InfoComponentFactory>("info");
    m_componentFactory.Add<PlatformComponentFactory>("platform");
    m_componentFactory.Add<ParallaxComponentFactory>("parallax");
    m_componentFactory.Add<TextComponentFactory>("text");
    m_componentFactory.Add<FPSComponentFactory>("fps");

    m_shapeFactory.Add<RectFactory>("rect");
    m_shapeFactory.Add<LineFactory>("line");

    m_stateInitFactory.Add<AnimInitializerFactory>("anim");
    m_stateInitFactory.Add<AnimColliderInitializerFactory>("animcollider");
    m_stateInitFactory.Add<LuaInitializerFactory>("lua");
    m_stateInitFactory.Add<LuaAnimColliderInitializerFactory>("luaanim");

    m_activityFactory.Add<NoOpActFactory>("noop");
    m_activityFactory.Add<CallFuncActFactory>("callfunc");
    m_activityFactory.Add<AnimateActFactory>("animate");
    m_activityFactory.Add<FlipActFactory>("flip");
    m_activityFactory.Add<MoveActFactory>("move");
    m_activityFactory.Add<MoveGravityActFactory>("movegravity");
    m_activityFactory.Add<ChangeStateActFactory>("changestate");
    m_activityFactory.Add<ChangeRoomActFactory>("gotoroom");
    m_activityFactory.Add<DelayActFactory>("delay");
    m_activityFactory.Add<BlinkActFactory>("blink");
    m_activityFactory.Add<CamBoundsActFactory>("setcambounds");
    m_activityFactory.Add<EnableKeyActFactory>("enablekey");
    m_activityFactory.Add<VirtualKeyActFactory>("virtualkey");
    m_activityFactory.Add<CollisionCheckActFactory>("collisioncheck");
}

template <>
std::unique_ptr<Entity> SceneFactory::Get<Entity> (luabridge::LuaRef& ref) {
    return std::move(m_entityFactory.Create(ref));
}

template <>
std::unique_ptr<Shape> SceneFactory::Get<Shape> (luabridge::LuaRef& ref) {
    return m_shapeFactory.Create(ref);
}

template <>
std::unique_ptr<Runner> SceneFactory::Get<Runner> (luabridge::LuaRef& ref) {
    return m_runnerFactory.Create(ref);
}

template <>
std::unique_ptr<Camera> SceneFactory::Get<Camera> (luabridge::LuaRef& ref) {
    return (m_cameraFactory.Create(ref));
}

template <>
std::unique_ptr<StateInitializer> SceneFactory::Get<StateInitializer> (luabridge::LuaRef& ref) {
    return m_stateInitFactory.Create(ref);
}

template <>
std::unique_ptr<StateBehaviour> SceneFactory::Get<StateBehaviour> (luabridge::LuaRef& ref) {
    return m_stateBehaviorFactory.Create(ref);
}

template <>
std::unique_ptr<Component> SceneFactory::Get<Component> (luabridge::LuaRef& ref) {
    return m_componentFactory.Create(ref);
}

template <>
std::unique_ptr<Activity> SceneFactory::Get<Activity> (luabridge::LuaRef& ref) {
    return std::move(m_activityFactory.Create(ref));
}

template <>
std::unique_ptr<IMesh> SceneFactory::Get<IMesh> (luabridge::LuaRef& ref) {
    return m_meshFactory.Create(ref);
}


std::shared_ptr<Entity> SceneFactory::Create() {

    // get current room
    Monkey& m = Monkey::get();
    std::string room = m["variables"].Get<std::string>("_room");
    std::cout << "Loading room "<< room << std::endl;
    LuaWrapper::Load(Engine::get().GetAssetManager().GetDirectory() + "rooms/" + room + "/room.lua");

    // Create the local assets
    luabridge::LuaRef roomRef = luabridge::getGlobal(LuaWrapper::L, "room");
    LuaTable roomTable(roomRef);

    if (roomTable.HasKey("init")) {
        luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("init");
        r1();
    }

    std::cout << "Loading engines ...\n";
    if (roomTable.HasKey("engines")) {
        luabridge::LuaRef engines = roomTable.Get<luabridge::LuaRef>("engines");
        for (int i = 0; i < engines.length(); ++i) {
            luabridge::LuaRef e = engines[i+1];
            auto runner = GetShared<Runner>(e);
            Engine::get().AddRunner(runner);
        }
    }



    // read assets
    if (roomTable.HasKey("assets")) {
        luabridge::LuaRef assets = roomTable.Get<luabridge::LuaRef>("assets");
        for (int i = 0; i < assets.length();++i) {
            luabridge::LuaRef a = assets[i+1];
            std::string id = a["id"].cast<std::string>();
            auto asset = GetShared<IMesh>(a);
            Engine::get().GetAssetManager().AddMesh(id, asset);
        }
    }

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

    return rootNode;

}


void SceneFactory::PostInit() {

    // Create the local assets
    luabridge::LuaRef roomRef = luabridge::getGlobal(LuaWrapper::L, "room");
    LuaTable roomTable(roomRef);
    if (roomTable.HasKey("afterstartup")) {
        luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("afterstartup");
        r1();
    }
}

void SceneFactory::CleanUp() {
    luabridge::LuaRef roomRef = luabridge::getGlobal(LuaWrapper::L, "room");
    LuaTable table (roomRef);
    luabridge::LuaRef assets = table.Get<luabridge::LuaRef>("assets");
    for (int i = 0; i < assets.length();++i) {
        luabridge::LuaRef a = assets[i+1];
        LuaTable assetTable(a);
        std::string id = assetTable.Get<std::string>("id");
        std::string type = assetTable.Get<std::string>("type");
        if (type == "sprite") {
            Engine::get().GetAssetManager().RemoveMesh(id);

        }
    }

    roomRef = luabridge::Nil();

}
