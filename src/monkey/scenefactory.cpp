#include <monkey/scenefactory.h>
#include <monkey/factories.h>
#include <monkey/factories/modelfactories.h>
#include <monkey/components/smartcollider.h>
#include <monkey/components/controller2d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/extstatemachine.h>
#include <monkey/dyloader.h>
#include <monkey/states/simple.h>

#include <monkey/components/hotspot.h>
#include <monkey/components/follow.h>
#include <monkey/components/scripthotspot.h>
#include <monkey/components/basicrenderer.h>
#include <monkey/components/luakeylistener.h>
#include <monkey/dynamicworld.h>
#include <monkey/scheduler.h>
#include <monkey/math/funcs.h>

#include <monkey/entities/sprite.h>
#include <monkey/entities/text.h>

#include <monkey/model/spritemodel.h>
#include <monkey/model/boxedmodel.h>

#include <monkey/activities/delay.h>
#include <monkey/activities/animate.h>
#include <monkey/components/info.h>
#include <monkey/activities/changeroom.h>
#include <monkey/activities/callfunc.h>
#include <monkey/entities/textview.h>
#include <monkey/mesh3dfactory.h>
#include <monkey/components/inputmethod.h>
#include <monkey/activities/scriptactions.h>
#include <monkey/activities/showmessage.h>
#include <monkey/activities/setstate.h>
#include <monkey/components/cursor.h>
#include <monkey/activities/setactive.h>
#include <monkey/py.h>
#include <monkey/activities/runscript.h>
#include <monkey/activities/move.h>
#include <monkey/activities/cambounds.h>
#include <monkey/states/walk25.h>
#include <monkey/components/controller25.h>
#include <monkey/math/ellipse.h>

namespace py = pybind11;


void SceneFactory::Init(Engine* engine) {
    // initialize lua
//    LuaWrapper::Init();
//    luabridge::LuaRef package = luabridge::getGlobal(LuaWrapper::L, "package");
//    std::cout << "package.path = " << package["path"].cast<std::string>() << "\n";
//    luabridge::setGlobal(LuaWrapper::L, engine->GetGameDirectory().c_str(), "_path" );
//    // load main
//    LuaWrapper::Load(Engine::get().GetGameDirectory() + "main.lua");
//
//    LuaTable engineDef(LuaWrapper::GetGlobal("engine"));
//
//    glm::vec2 devSize = engineDef.Get<glm::vec2>("device_size");
//    glm::ivec2 winSize = engineDef.Get<glm::ivec2>("window_size");
//    int fps = engineDef.Get<int>("fps", 60);
//    std::string title = engineDef.Get<std::string>("title");
//
//    engine->SetDeviceSize(devSize);
//    engine->SetWindowSize(winSize);
//    engine->SetFPS(fps);
//    engine->SetTitle(title);
//
//    extendLua();
}



void SceneFactory::StartUp(Engine * engine) {
    engine->EnableMouse();
    engine->EnableKeyboard();

    const auto& mt = engine->getMainTable();
    auto shaders = mt.get<std::vector<std::string>>("shaders");

    ShaderFactory sf;
    auto re = engine->GetRenderingEngine();
    for (const auto& s : shaders) {
        std::cout << "loading shader " << s << std::endl;
        auto sh = sf.getShader(s);
        re->AddShader(std::move(sh));
    }
//    LuaTable engineDef(LuaWrapper::GetGlobal("engine"));
//    std::vector<std::string> shaders = engineDef.GetVector<std::string>("shaders");
//    auto re = engine->GetRenderingEngine();
//    ShaderFactory sf;
//    for (auto& shaderId : shaders) {
//        std::cout << "Loading shader: " << shaderId << "\n";
//        auto sh = sf.getShader(shaderId);
//        re->AddShader(std::move(sh));
//        // engine->AddShader(std::move(sh));
//    }
//
//    // load global assets (fonts + models)
//    std::cout << "Loading global assets ...\n";
//    if (engineDef.HasKey("global_assets")) {
//
//        luabridge::LuaRef gaRef = engineDef.Get<luabridge::LuaRef>("global_assets");
//        LuaTable gaTable(gaRef);b
//        auto fonts = gaTable.GetVector<std::string>("fonts");
//        for (auto& fontId : fonts) {
//            Engine::get().GetAssetManager().GetFont(fontId);
//        }
//        auto models = gaTable.GetVector<std::string>("models");
//        for (auto& model : models) {
//            Engine::get().GetAssetManager().GetModel(model);
//        }
//
//    }
//
//    Engine::get().GetAssetManager().SetLocal(true);




}

SceneFactory::SceneFactory() {

    add<Ref> ("ref");

    // entities
    add<Entity> ("default");
    add2<Entity> ("entity");

    add<Sprite> ("sprite");
    add2<Sprite> ("sprite");
    add<Text> ("text");
    add2<Text> ("text");
    add<TextView> ("textview");
    add2<TextView> ("textview");
    // components
    add<Follow> ("follow");
    add2<Follow> ("components.follow");
    add<SimpleCollider> ("collider");
    add2<SimpleCollider> ("components.collider");
    add2<SmartCollider> ("components.smartcollider");
    add<ScriptHotSpot> ("hotspot");
    add2<ScriptHotSpot> ("components.hotspot");
    add<BasicRenderer> ("gfx");
    add2<BasicRenderer> ("components.gfx");
    add<LuaKeyListener> ("keylistener");
    add2<LuaKeyListener> ("runner.keylistener");
    add<LuaInfo> ("info");
    add2<LuaInfo> ("components.info");
    add<DirectionalLight> ("directional.light");
    add<KeyboardInputMethod> ("keyinput");
    add2<KeyboardInputMethod> ("components.keyinput");
    add<Cursor> ("cursor");
    add2<Controller2D> ("components.controller2D");
    add2<Controller25> ("components.controller25");
    add2<Dynamics2D> ("components.dynamics2D");
    add2<ExtendedStateMachine> ("components.statemachine");

    // states
    add2<NullState> ("state.null");
    add2<SimpleState> ("state.simple");
    add2<Walk25> ("state.walk25");

    // actions
    add<DelayTime> ("delay");
    add2<DelayTime> ("action.delay");
    add<DelayTimeDynamic> ("delay_dynamic");
    add<Animate> ("animate");
    add2<Animate> ("action.animate");
    add<ChangeRoom> ("gotoroom");
    add2<ChangeRoom> ("action.changeroom");
    add<CallFunc> ("callfunc");
    add2<CallFunc> ("action.callfunc");
    add<SuspendScript> ("suspend_script");
    add<ResumeScript> ("resume_script");
    add<KillScript> ("kill_script");
    add<ShowMessage> ("show_message");
    add<SetState> ("setstate");
    add2<SetState> ("action.setstate");
    add<SetActive> ("setactive");
    add2<RunScript> ("action.runscript");
    add2<MoveAccelerated> ("action.moveaccelerated");
    add2<MoveTo> ("action.move");
    add2<ChangeCamBounds> ("action.changecambounds");
    // runners
    add<HotSpotManager> ("hotspotmanager");
    add2<HotSpotManager> ("components.hotspotmanager");

    add<Scheduler> ("scheduler");
    add2<Scheduler> ("runner.scheduler");

    add<CollisionEngine> ("collision");
    add2<CollisionEngine> ("runner.collisionengine");
    add2<DynamicWorldBuilder> ("runner.dynamicworld");
    // cameras
    add<OrthographicCamera> ("ortho");
    add2<OrthographicCamera> ("cam.ortho");
    add<PerspectiveCamera> ("perspective");

    // shapes
    add<Poly> ("poly");
    add2<Poly> ("shape.poly");
    add<Rect> ("rect");
    add2<Rect> ("rect");
    add2<Line> ("line");
    add<PolyLine> ("graph");
    add2<PolyLine> ("shape.graph");
    add2<Ellipse> ("shape.ellipse");
    // models
    add<SpriteModel> ("sprite.model");
    add2<SpriteModel> ("asset.sprite");
    add2<BoxedModel> ("asset.boxed");
    // other
    add<Font> ("font");
    add2<Font> ("font");
    add<Constant2D> ("constant");
    add<Linear2Dy> ("linear_y");
    add2<Linear2Dy> ("func.liny");
    add<PatchwiseLinear2D> ("patchwise");

    add<Box3D> ("box3d");
    add<Sphere3D> ("sphere3d");
    //DynamicWorldBuilderFactory
//    m_runnerFactory.Add<CollisionEngineFactory>("collision");
//    m_runnerFactory.Add<CollisionEngine3DFactory>("collision3d");
//
//    m_runnerFactory.Add<DynamicWorldBuilderFactory>("dynamicworld");
//
//    m_modelFactory.Add<SimpleModelFactory>("sprite");
//    m_modelFactory.Add<BoxedModelFactory>("boxed_sprite");
//    m_modelFactory.Add<GenericModel3DFactory>("model3d");
//    m_modelFactory.Add<ModelBox3D>("box3d");
//    m_modelFactory.Add<ModelTrapezoid3D>("trapezoid3d");
//    m_modelFactory.Add<SkeletalModelFactory>("skeletal");
//
//    m_entityFactory.Add<EntityFactory>("default");
//    m_entityFactory.Add<TextViewFactory>("textview");
//    m_entityFactory.Add<SpriteFactory>("sprite");
//    m_entityFactory.Add<BoxedMessageFactory>("boxedmessage");
//    m_entityFactory.Add<SkeletonFactory>("skeleton");
//    m_entityFactory.Add<ParallaxBackgroundFactory>("parallaxbg");
//    //m_entityFactory.Add<HeightMapFactory>("heightmap");
//
//    m_cameraFactory.Add<OrthoCamFactory>("ortho");
//    m_cameraFactory.Add<PerspectiveCamFactory>("perspective");
//
//    m_componentFactory.Add<LuaKeyboardComponentFactory>("luakey");
//    m_componentFactory.Add<GfxComponentFactory>("gfx");
//    //m_componentFactory.Add<Gfx3DComponentFactory>("gfx3d");
//    m_componentFactory.Add<ColliderComponentFactory>("collider");
//
//    m_componentFactory.Add<SmartColliderComponentFactory>("smartcollider");
//    m_componentFactory.Add<SkeletalColliderComponentFactory>("skeletalcollider");
//
//    m_componentFactory.Add<Controller2DComponentFactory>("controller2d");
//    m_componentFactory.Add<Controller3DComponentFactory>("controller3d");
//
//    m_componentFactory.Add<Dynamics2DComponentFactory>("dynamics2d");
//    m_componentFactory.Add<PropertiesCompFactory>("properties");
//    m_componentFactory.Add<StateMachineCompFactory>("statemachine");
//    m_componentFactory.Add<ExtStateMachineCompFactory>("extstatemachine");
//    m_componentFactory.Add<FollowComponentFactory>("follow");
//    //m_componentFactory.Add<Follow3DComponentFactory>("follow3d");
//    m_componentFactory.Add<InfoComponentFactory>("info");
//    m_componentFactory.Add<PlatformComponentFactory>("platform");
//    m_componentFactory.Add<ParallaxComponentFactory>("parallax");
//    m_componentFactory.Add<Parallax3DComponentFactory>("parallax3d");
//    m_componentFactory.Add<TextComponentFactory>("text");
//    m_componentFactory.Add<FPSComponentFactory>("fps");
//    m_componentFactory.Add<HotSpotComponentFactory>("hotspot");
//    m_componentFactory.Add<DepthComponentFactory>("depth");
//    m_componentFactory.Add<CursorComponentFactory>("cursor");
//    m_componentFactory.Add<LightComponentFactory>("light");
//    m_componentFactory.Add<KeyboardInputMethodCompFactory>("keyinput");
//    m_componentFactory.Add<ShadowComponentFactory>("shadow");
//    m_componentFactory.Add<GarbageCollectCompFactory>("garbage");
//    m_componentFactory.Add<PolyMoverCompFactory>("polymover");
//    m_componentFactory.Add<EllipseMoverCompFactory>("ellipsemover");
//    m_componentFactory.Add<Depth25CompFactory>("depth25");
//    m_componentFactory.Add<LuaHookCompFactory>("luahook");
//    //m_componentFactory.Add<RaycastControllerComponentFactory>("raycastcontroller");
//    //m_componentFactory.Add<BillboardComponentFactory>("billboard");
//
//    m_shapeFactory.Add<RectFactory>("rect");
//    m_shapeFactory.Add<LineFactory>("line");
//    m_shapeFactory.Add<CircleFactory>("circle");
//    m_shapeFactory.Add<EllipseFactory>("ellipse");
//    m_shapeFactory.Add<CompoundFactory>("compound");
//    m_shapeFactory.Add<PolyFactory>("poly");
//    m_shapeFactory.Add<GraphFactory>("graph");
//    m_shapeFactory.Add<Plane3DFactory>("plane3d");
//    m_shapeFactory.Add<BoxFactory>("box");
//
////    m_stateInitFactory.Add<AnimInitializerFactory>("anim");
////    m_stateInitFactory.Add<AnimColliderInitializerFactory>("animcollider");
////    m_stateInitFactory.Add<LuaInitializerFactory>("lua");
////    m_stateInitFactory.Add<LuaAnimColliderInitializerFactory>("luaanim");
//
//    m_activityFactory.Add<NoOpActFactory>("noop");
//    m_activityFactory.Add<CallFuncActFactory>("callfunc");
//    m_activityFactory.Add<RepeatActFactory>("repeat");
//    m_activityFactory.Add<AnimateActFactory>("animate");
//    m_activityFactory.Add<FlipActFactory>("flip");
//    m_activityFactory.Add<MoveActFactory>("move");
//    m_activityFactory.Add<RotateActFactory>("rotate");
//    m_activityFactory.Add<MoveAcceleratedActFactory>("moveaccelerated");
//    //m_activityFactory.Add<ChangeStateActFactory>("changestate");
//    m_activityFactory.Add<ChangeRoomActFactory>("gotoroom");
//    m_activityFactory.Add<DelayActFactory>("delay");
//    m_activityFactory.Add<BlinkActFactory>("blink");
//    m_activityFactory.Add<CamBoundsActFactory>("setcambounds");
//    m_activityFactory.Add<EnableKeyActFactory>("enablekey");
//    m_activityFactory.Add<VirtualKeyActFactory>("virtualkey");
//    m_activityFactory.Add<CollisionCheckActFactory>("collisioncheck");
//    m_activityFactory.Add<ScaleActFactory>("scale");
//    m_activityFactory.Add<DelayActFactory>("delay");
//    m_activityFactory.Add<DelayDynamicActFactory>("delay_dynamic");
//    m_activityFactory.Add<ShowMessageActFactory>("show_message");
//    m_activityFactory.Add<SuspendScriptActFactory>("suspend_script");
//    m_activityFactory.Add<ResumeScriptActFactory>("resume_script");
//    m_activityFactory.Add<KillScriptActFactory>("kill_script");
//    m_activityFactory.Add<SuspendAllScriptActFactory>("suspend_all");
//    m_activityFactory.Add<ScrollActFactory>("scroll");
//    m_activityFactory.Add<SetStateActFactory>("setstate");
//    m_activityFactory.Add<WaitClickActFactory>("waitclick");
//    m_activityFactory.Add<TreeMoveActFactory>("treemove");
//    m_activityFactory.Add<SetActiveActFactory>("setactive");
//    m_activityFactory.Add<SetDemoActFactory>("setdemo");
//
//
//    m_skeletalAnimFactory.Add<SkeletalAnimFactory>("default");
//
//    m_stateFactory.Add<Walk25StateFactory>("walk25");
//    m_stateFactory.Add<Jump25StateFactory>("jump25");
//    m_stateFactory.Add<Hit25StateFactory>("hit25");
//    m_stateFactory.Add<SimpleStateFactory>("simple");
}

//void SceneFactory::addStateFactory(const std::string &a, std::unique_ptr<FactoryMethod<State>> f) {
//    m_stateFactory.Add(a, std::move(f));
//}
//void SceneFactory::addComponentFactory(const std::string &a, std::unique_ptr<FactoryMethod<Component>> f) {
//    m_componentFactory.Add(a, std::move(f));
//}
//
//void SceneFactory::addActivityFactory(const std::string &a, std::unique_ptr<FactoryMethod<Activity>> f){
//    m_activityFactory.Add(a, std::move(f));
//}

std::shared_ptr<Entity> SceneFactory::Create(py::object& roomDef) {

    auto& engine = Engine::get();
//
//    // get current room
//    const auto& table = engine.getMainTable();
//    auto room = table.get<std::string>("room");
//    std::cout << "room is = " << room << "\n";
//
//    py::function builder;
//    try {
//        builder = table.get<py::dict>("data")["rooms"][room.c_str()].cast<py::function>();
//    } catch (...) {
//        GLIB_FAIL("Unable to find the builder for room: " << room)
//    }


    auto engineList = roomDef.attr("engines").cast<py::list>();

    for (const auto& p : engineList) {
        PyTable t(p.cast<py::object>());
        engine.AddRunner(make2<Runner>(t));
    }



    //return nullptr;


//    LuaTable vars (LuaWrapper::GetGlobalPath( {"engine", "state"} ));
//    std::string room = vars.Get<std::string>("room");
//
//    LuaWrapper::Load(Engine::get().GetGameDirectory() + "rooms/" + room + "/room.lua");
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
//            LuaTable t(e);
//            auto runner = make<Runner>(t);
//            Engine::get().AddRunner(runner);
//        }
//    }

    //Ref::dump();
    // load room-specific assets
//    auto roomAssets = roomTable.GetVector<std::string>("assets");
//    for (auto& a : roomAssets) {
//        // load the asset
//        LoadModel(a);//    }

    // read the scene tree
    auto scene = std::make_shared<Entity>();
    auto sceneList = roomDef.attr("scene").cast<py::list>();
    for (const auto& p : sceneList) {
        PyTable t(p.cast<py::object>());
        scene->AddChild(make2<Entity>(t));
    }

    //auto rootNode = std::make_shared<Entity>();
//    rootNode->SetTag("_root");
//    luabridge::LuaRef rscene = roomTable.Get<luabridge::LuaRef>("scene");
//    for (int i = 0; i < rscene.length(); ++i) {
//        luabridge::LuaRef rnode = rscene[i+1];
//        LuaTable t(rnode);
//        auto node  = make<Entity>(t);
//        rootNode->AddChild(node);
//    }
//
//    // launch the start script
//    if (roomTable.HasKey("start")) {
//        luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("start");
//        r1();
//    }
//    Ref::dump();
    return scene;
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
//    aujr
// to& am = Engine::get().GetAssetManager();
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
//    luabridge::LuaRef roomRef = LuaWrapper::GetGlobal("room");
//    LuaTable table (roomRef);
//
//    // unload room-specific assets
//    Engine::get().GetAssetManager().CleanUp();
//
//    roomRef = luabridge::Nil();
}


