#include <monkey/scenefactory.h>
#include <monkey/scenefactory.h>
#include <monkey/factories.h>
#include <monkey/components/smartcollider.h>
#include <monkey/components/controller2d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/extstatemachine.h>
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
#include <monkey/components/platform.h>
#include <monkey/activities/setactive.h>
#include <monkey/py.h>
#include <monkey/activities/runscript.h>
#include <monkey/activities/move.h>
#include <monkey/activities/cambounds.h>
#include <monkey/states/walk25.h>
#include <monkey/states/walk3d.h>

#include <monkey/components/controller25.h>
#include <monkey/math/shapes/ellipse.h>
#include <monkey/states/hit25.h>
#include <monkey/states/foewalk25.h>
#include <monkey/states/ishit25.h>
#include <monkey/components/parallax.h>
#include <monkey/fill.h>
#include <monkey/activities/repeat.h>
#include <monkey/components/shadow.h>
#include <monkey/math/shapes/polytri.h>
#include <monkey/entities/skeleton.h>
#include <monkey/activities/freemove.h>
#include <monkey/activities/noop.h>
#include <monkey/activities/scroll.h>
#include <monkey/skeletal/skmodel.hpp>
#include <monkey/skeletal/animation.hpp>
#include <monkey/components/stateactions.h>
#include <monkey/states/attack.h>
#include <monkey/skeletal/skcollider.hpp>
#include <monkey/states/jumpattack.h>
#include <monkey/activities/blink.h>
#include <monkey/math/shapes/plane3d.h>
#include <monkey/skeletal/skcoll.h>
#include <monkey/skeletal/skeletalcollidermanager.h>
#include <monkey/math/shapes/polychain3d.h>
#include <monkey/math/shapes/surf2d.h>
#include <monkey/components/fpscounter.h>
#include <monkey/activities/scale.h>
#include <monkey/components/mover.h>


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

    add2<Entity> ("entity");
    add2<Sprite> ("sprite");
    add2<Skeleton> ("skeleton");

    add2<Text> ("text");
    add2<TextView> ("textview");
    add2<Follow> ("components.follow");
    add2<SimpleCollider> ("components.collider");
    add2<SmartCollider> ("components.smartcollider");
    add2<SkCollider> ("components.skeletalcollider");
    add2<FPSCounter> ("components.fpscounter");
	add2<SkColl> ("components.skc");
	add2<SkeletalColliderManager>("components.collidermanager");
    add2<ScriptHotSpot> ("components.hotspot");
    add2<BasicRenderer> ("components.gfx");
    add2<LuaKeyListener> ("runner.keylistener");
    add2<LuaInfo> ("components.info");
	add2<PolygonalMover> ("components.polymover");
    add2<KeyboardInputMethod> ("components.keyinput");
    add2<Controller2D> ("components.controller2D");
    add2<Controller25> ("components.controller25");
    add2<Dynamics2D> ("components.dynamics2D");
    add2<PlatformComponent>("components.platform");
    add2<ExtendedStateMachine> ("components.statemachine");
    add2<Parallax>("components.parallax");
    add2<Cursor> ("components.cursor");
    add2<Shadow>("components.shadow");
    add2<ShadowX>("components.shadowx");
    add2<NullState> ("state.null");
    add2<SimpleState> ("state.simple");
    add2<Walk25> ("state.walk25");
    add2<Walk3D> ("state.walk3d");
    add2<FoeWalk25> ("state.foewalk25");
    add2<Attack> ("state.attack");
    add2<JumpAttack> ("state.jumpattack");
    add2<Hit25> ("state.hit25");
    add2<IsHit25> ("state.ishit25");
    add2<DelayTime> ("action.delay");
    add2<DelayTimeDynamic> ("action.delaydynamic");
    add2<Animate> ("action.animate");
    add2<Blink> ("action.blink");
    add2<NoOp>("action.noop");
    add2<Scroll> ("action.scroll");
    add2<ChangeRoom> ("action.changeroom");
    add2<CallFunc> ("action.callfunc");
    add2<ShowMessage> ("action.msg");
    add2<SetState> ("action.setstate");
    add2<RunScript> ("action.runscript");
    add2<SuspendScript> ("action.suspendscript");
    add2<ResumeScript> ("action.resumescript");
	add2<KillScript> ("action.killscript");
    add2<MoveAccelerated> ("action.moveaccelerated");
    add2<MoveTo> ("action.move");
    add2<FreeMove> ("action.freemove");
    add2<ChangeCamBounds> ("action.changecambounds");
    add2<Repeat>("action.repeat");
    add2<ScaleTo>("action.scale");
    add2<HotSpotManager> ("components.hotspotmanager");
    add2<Scheduler> ("runner.scheduler");
    add2<CollisionEngine> ("runner.collisionengine");
    add2<DynamicWorldBuilder> ("runner.dynamicworld");
    add2<OrthographicCamera> ("cam.ortho");
    add2<PerspectiveCamera> ("cam.perspective");
    add2<Poly> ("shape.poly");
    add2<Polygon>("shape.polygon");
    add2<PolyTri>("shape.polygontri");
    add2<Rect> ("rect");
    add2<Line> ("line");
    add2<PolyLine> ("shape.graph");
    add2<Ellipse> ("shape.ellipse");
    add2<Circle> ("shape.circle");
    add2<SolidFill>("fill.solid");
    add2<LinearGradient>("fill.lineargradient");
    add2<StateFunc> ("stateaction.callback");
    add2<StateTransition> ("stateaction.statetransition");
    // assets
    add2<SpriteModel> ("asset.sprite");
    add2<BoxedModel> ("asset.boxed");

    //add2<SkeletalModel> ("asset.skeleton");
    //add2<SkeletalModel2> ("asset.skeleton2");
    add2<SkModel> ("asset.skeletalmodel");
    add2<SkAnimation> ("asset.skeletalanimation");
    add2<Font> ("font");

    // functions
    add2<Linear2Dy> ("func.liny");
    add2<Linear2Dx> ("func.linx");
    add2<Constant2D> ("func.const");
    add2<PatchwiseLinear2D> ("func.patch2d");

    add2<DirectionalLight> ("light.directional");
    // mesh
    add2<Plane3D> ("shape.plane3d");
    add2<PolyChain3D> ("shape.polychain3d");
    add2<PySurf2D>("shape.surf2d");
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
    //luabridge::LuaRef roomRef = luabridge::getGlobal(LuaWrapper::L, "room");
    //LuaTable roomTable(roomRef);
    //i/f (roomTable.HasKey("afterstartup")) {
     //   luabridge::LuaRef r1 = roomTable.Get<luabridge::LuaRef>("afterstartup");
      //  r1();
    //}
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


