#include <gfx/scenefactory.h>
#include <gfx/factories.h>
#include <iostream>
#include <gfx/engine.h>
//
//template <>
//std::shared_ptr<Entity> SceneFactory::Get<Entity> (luabridge::LuaRef& ref) {
//    return m_entityFactory.Create(ref);
//}
//
//template <>
//std::shared_ptr<Shape> SceneFactory::Get<Shape> (luabridge::LuaRef& ref) {
//    return m_shapeFactory.Create(ref);
//}
//
//template <>
//std::shared_ptr<Runner> SceneFactory::Get<Runner> (luabridge::LuaRef& ref) {
//    return m_runnerFactory.Create(ref);
//}
//
//template <>
//std::shared_ptr<Camera> SceneFactory::Get<Camera> (luabridge::LuaRef& ref) {
//    auto p = m_cameraFactory.Create(ref);
//    std::cout << "ciao ciao bellino\n";
//    std::cout << p->GetPosition().x << "\n";
//    std::cout << p->GetTag() << "\n";
//
//    return p;
//
//}
//
////template <>
////std::shared_ptr<StateInitializer> SceneFactory::Get<StateInitializer> (luabridge::LuaRef& ref) {
////    return std::move(m_stateInitFactory.Create(ref));
////}
////
////template <>
////std::shared_ptr<StateBehaviour> SceneFactory::Get<StateBehaviour> (luabridge::LuaRef& ref) {
////    return m_stateBehaviorFactory.Create(ref);
////}
//
//template <>
//std::shared_ptr<Component> SceneFactory::Get<Component> (luabridge::LuaRef& ref) {
//    return m_componentFactory.Create(ref);
//}
//
//template <>
//std::shared_ptr<Activity> SceneFactory::Get<Activity> (luabridge::LuaRef& ref) {
//    return m_activityFactory.Create(ref);
//}
//
//template <>
//std::shared_ptr<IModel> SceneFactory::Get<IModel> (luabridge::LuaRef& ref) {
//    return m_modelFactory.Create(ref);
//}


void SceneFactory::Init(Engine* engine) {
    // initialize lua
    LuaWrapper::Init();
    luabridge::setGlobal(LuaWrapper::L, engine->GetDirectory().c_str(), "_path" );
    // load main
    LuaWrapper::Load(Engine::get().GetDirectory() + "main.lua");

    LuaTable engineDef(LuaWrapper::GetGlobal("engine"));

    glm::vec2 devSize = engineDef.Get<glm::vec2>("device_size");
    glm::ivec2 winSize = engineDef.Get<glm::ivec2>("window_size");
    int fps = engineDef.Get<int>("fps", 60);
    std::string title = engineDef.Get<std::string>("title");

    engine->SetDeviceSize(devSize);
    engine->SetWindowSize(winSize);
    engine->SetFPS(fps);
    extendLua();
}

void SceneFactory::StartUp(Engine * engine) {
    engine->EnableMouse();
    engine->EnableKeyboard();

    LuaTable engineDef(LuaWrapper::GetGlobal("engine"));
    std::vector<std::string> shaders = engineDef.GetVector<std::string>("shaders");
    auto re = engine->GetRenderingEngine();
    for (auto& shaderId : shaders) {
        std::cout << "Loading shader: " << shaderId << "\n";
        auto sh = ShaderFactory::GetShader(shaderId);
        re->AddShader(std::move(sh));
        // engine->AddShader(std::move(sh));
    }

    // load global assets
    std::cout << "Loading global assets ...\n";
    LuaTable globalAssets(LuaWrapper::GetGlobal("global_assets"));
    if (globalAssets.HasKey("fonts")) {
        std::vector<std::string> fonts = globalAssets.GetVector<std::string>("fonts");
        for (auto& fontId : fonts) {
            Engine::get().GetAssetManager().GetFont(fontId);
        }
    }
    if (globalAssets.HasKey("models")) {
        std::vector<std::string> models = globalAssets.GetVector<std::string>("models");
        for (auto& modelId : models) {
            Engine::get().GetAssetManager().GetModel(modelId);
        }
    }
    Engine::get().GetAssetManager().SetLocal(true);




}

SceneFactory::SceneFactory() {
    //m_runnerFactory.Add<HotSpotManagerFactory>("hotspotmanager");
    m_runnerFactory.Add<SchedulerFactory>("scheduler");
    m_runnerFactory.Add<CollisionEngineFactory>("collision");
    m_runnerFactory.Add<HotSpotManagerFactory>("hotspotmanager");

    m_modelFactory.Add<SimpleModelFactory>("sprite");
    m_modelFactory.Add<CompositeModelFactory>("model");

    m_entityFactory.Add<EntityFactory>("default");
    m_entityFactory.Add<TextViewFactory>("textview");
    m_entityFactory.Add<SpriteFactory>("sprite");
    //m_entityFactory.Add<HeightMapFactory>("heightmap");

    m_cameraFactory.Add<OrthoCamFactory>("ortho");
    m_cameraFactory.Add<PerspectiveCamFactory>("perspective");

    //m_componentFactory.Add<LuaKeyboardComponentFactory>("luakey");
    m_componentFactory.Add<GfxComponentFactory>("gfx");
    m_componentFactory.Add<Gfx3DComponentFactory>("gfx3d");
    m_componentFactory.Add<ColliderComponentFactory>("collider");
    m_componentFactory.Add<MultiColliderComponentFactory>("multicollider");

    m_componentFactory.Add<Controller2DComponentFactory>("controller2d");
    m_componentFactory.Add<Dynamics2DComponentFactory>("dynamics2d");
    m_componentFactory.Add<PropertiesCompFactory>("properties");
    //m_componentFactory.Add<StateMachineComponentFactory>("statemachine");
    m_componentFactory.Add<FollowComponentFactory>("follow");
    //m_componentFactory.Add<Follow3DComponentFactory>("follow3d");
    m_componentFactory.Add<InfoComponentFactory>("info");
    m_componentFactory.Add<PlatformComponentFactory>("platform");
    m_componentFactory.Add<ParallaxComponentFactory>("parallax");
    m_componentFactory.Add<TextComponentFactory>("text");
    m_componentFactory.Add<FPSComponentFactory>("fps");
    m_componentFactory.Add<HotSpotComponentFactory>("hotspot");
    m_componentFactory.Add<DepthComponentFactory>("depth");
    m_componentFactory.Add<CursorComponentFactory>("cursor");
    m_componentFactory.Add<LightComponentFactory>("light");
    m_componentFactory.Add<KeyboardInputMethodCompFactory>("keyinput");

    //m_componentFactory.Add<RaycastControllerComponentFactory>("raycastcontroller");
    //m_componentFactory.Add<BillboardComponentFactory>("billboard");

    m_shapeFactory.Add<RectFactory>("rect");
    m_shapeFactory.Add<LineFactory>("line");
    m_shapeFactory.Add<CircleFactory>("circle");
    m_shapeFactory.Add<CompoundFactory>("compound");
    m_shapeFactory.Add<PolyFactory>("poly");
    m_shapeFactory.Add<GraphFactory>("graph");

//    m_stateInitFactory.Add<AnimInitializerFactory>("anim");
//    m_stateInitFactory.Add<AnimColliderInitializerFactory>("animcollider");
//    m_stateInitFactory.Add<LuaInitializerFactory>("lua");
//    m_stateInitFactory.Add<LuaAnimColliderInitializerFactory>("luaanim");

    m_activityFactory.Add<NoOpActFactory>("noop");
    m_activityFactory.Add<CallFuncActFactory>("callfunc");
    m_activityFactory.Add<AnimateActFactory>("animate");
    m_activityFactory.Add<FlipActFactory>("flip");
    m_activityFactory.Add<MoveActFactory>("move");
    m_activityFactory.Add<RotateActFactory>("rotate");
    m_activityFactory.Add<MoveAcceleratedActFactory>("moveaccelerated");
    //m_activityFactory.Add<ChangeStateActFactory>("changestate");
    m_activityFactory.Add<ChangeRoomActFactory>("gotoroom");
    m_activityFactory.Add<DelayActFactory>("delay");
    m_activityFactory.Add<BlinkActFactory>("blink");
    m_activityFactory.Add<CamBoundsActFactory>("setcambounds");
    m_activityFactory.Add<EnableKeyActFactory>("enablekey");
    m_activityFactory.Add<VirtualKeyActFactory>("virtualkey");
    m_activityFactory.Add<CollisionCheckActFactory>("collisioncheck");
    m_activityFactory.Add<ScaleActFactory>("scale");
    m_activityFactory.Add<DelayActFactory>("delay");
    m_activityFactory.Add<DelayDynamicActFactory>("delay_dynamic");
    m_activityFactory.Add<ShowMessageActFactory>("show_message");
    m_activityFactory.Add<SuspendScriptActFactory>("suspend_script");
    m_activityFactory.Add<ResumeScriptActFactory>("resume_script");
    m_activityFactory.Add<KillScriptActFactory>("kill_script");
    m_activityFactory.Add<ScrollActFactory>("scroll");
    m_activityFactory.Add<SetStateActFactory>("setstate");
}




std::shared_ptr<Entity> SceneFactory::Create() {

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
            auto runner = makeRunner(e);
            Engine::get().AddRunner(runner);
        }
    }


    // load room-specific assets
//    auto roomAssets = roomTable.GetVector<std::string>("assets");
//    for (auto& a : roomAssets) {
//        // load the asset
//        LoadModel(a);//    }

    // read the scene tree
    auto rootNode = std::make_shared<Entity>();
    rootNode->SetTag("_root");
    luabridge::LuaRef rscene = roomTable.Get<luabridge::LuaRef>("scene");
    for (int i = 0; i < rscene.length(); ++i) {
        luabridge::LuaRef rnode = rscene[i+1];
        auto node  = makeEntity(rnode);
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


//void SceneFactory::LoadModel (const std::string& model) {
//    // check if model is already loaded:
//    auto& am = Engine::get().GetAssetManager();
//
//    if (am.HasModel(model)) {
//        return;
//    }
//    static luabridge::LuaRef modelsDef = LuaWrapper::GetGlobal("models");
//    if (modelsDef.isNil()) {
//        GLIB_FAIL("No models available!")
//    }
//    std::cout << "*** load asset " << model << " ... \n";
//    luabridge::LuaRef modelDef = modelsDef[model];
//    if (modelDef.isNil()) {
//        GLIB_FAIL("Unknown model " << model);
//    }
//
//    auto asset = GetShared<IModel>(modelDef);
//    am.AddModel(model, asset);
//
//}

void SceneFactory::CleanUp() {
    luabridge::LuaRef roomRef = LuaWrapper::GetGlobal("room");
    LuaTable table (roomRef);

    // unload room-specific assets
    Engine::get().GetAssetManager().CleanUp();

    roomRef = luabridge::Nil();

}


