#include <gfx/factories.h>
#include <gfx/components/renderer.h>
#include <gfx/font.h>
#include <gfx/engine.h>
#include <gfx/textmesh.h>
#include <glm/gtx/transform.hpp>
#include <gfx/components/keyinput.h>
#include <gfx/components/switch.h>
#include <gfx/quadmesh.h>
#include <gfx/meshfactory.h>
#include <gfx/components/multicollider.h>
#include <gfx/components/scripthotspot.h>
#include <gfx/components/luakeylistener.h>
#include <gfx/components/depth.h>
#include <gfx/components/follow.h>
#include <gfx/components/billboard.h>
#include <gfx/components/parallax.h>
#include <gfx/state.h>
#include <gfx/components/info.h>
#include <gfx/components/textview.h>
#include <gfx/components/statemachine.h>
#include <gfx/components/keyinput.h>
#include <gfx/luacollision.h>
#include <gfx/walkstate.h>
#include <gfx/hit.h>
#include <gfx/aiwalk.h>
#include <gfx/components/shadow.h>
#include <gfx/states/animinitializer.h>
#include <gfx/math/geom.h>
#include <gfx/components/controller2d.h>
#include <gfx/components/dynamics2d.h>
#include <gfx/runner.h>
#include <gfx/states/luainitializer.h>
#include <gfx/components/platform.h>
#include <gfx/components/fpscounter.h>


std::unique_ptr<Component> TextComponentFactory::Create(luabridge::LuaRef &ref) {
    auto renderer = std::unique_ptr<Renderer>(new Renderer);
    LuaTable table(ref);
    std::string text = table.Get<std::string>("id");
    std::string font = table.Get<std::string>("font");
    float size = table.Get<float>("size", 8);
    TextAlignment align = table.Get<TextAlignment>("align", TOP_LEFT);
    float maxWidth = table.Get<float>("maxwidth", 0.0f);
    glm::vec4 color = table.Get<glm::vec4>("color", glm::vec4(255.0f));
    color /= 255.0f;
    Font* f = Engine::get().GetAssetManager().GetFont(font);
    auto mesh = std::make_shared<TextMesh>(f, text, size, align, maxWidth);
    glm::vec2 offset = mesh->getOffset();
    renderer->SetRenderingTransform(glm::translate(glm::vec3(offset, 0.0f)));
    renderer->SetTint(color);
    renderer->SetMesh(mesh);
    return std::move(renderer);
}

std::unique_ptr<Component> GfxComponentFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);

    auto renderer = std::unique_ptr<Renderer>(new Renderer);
    if (table.HasKey("image")) {
        std::string image = table.Get<std::string>("image");
        float w = table.Get<float>("width", 0.0f);
        float h = table.Get<float>("height", 0.0f);
        glm::vec2 repeat = table.Get<glm::vec2>("rep", glm::vec2(1.0f, 1.0f));
        glm::vec2 skew = table.Get<glm::vec2>("skew", glm::vec2(0.0f, 0.0f));
        glm::vec2 offset = table.Get<glm::vec2>("offset", glm::vec2(0.0f));
        auto mesh = std::make_shared<QuadMesh>(image, w, h, repeat.x, repeat.y, skew.x, skew.y, offset);
        renderer->SetMesh(mesh);
    } else if (table.HasKey("model")) {
        std::string model = table.Get<std::string>("model");
        std::string anim = table.Get<std::string>("anim", "");
        bool flip = table.Get<bool>("flip", false);
        renderer->SetMesh(Engine::get().GetAssetManager().GetMesh(model));
        renderer->SetFlipX(flip);
        //renderer->SetRenderingTransform(glm::scale(glm::vec3(0.1f))*glm::rotate(90.0f, glm::vec3(1.0f,0.0f,0.0f)));
        //renderer->SetScale(0.1f);
        renderer->SetAnimation(anim);
    } else if (table.HasKey("shape")) {
        luabridge::LuaRef sref = table.Get<luabridge::LuaRef>("shape");
        std::string draw = table.Get<std::string>("draw","outline");
        glm::vec4 color = table.Get<glm::vec4>("color");
        color /= 255.0f;
        auto factory = Engine::get().GetSceneFactory();
        auto shape = factory->Get<Shape>(sref);
        if (draw == "outline") {
            auto mesh = MeshFactory::CreateMesh(*(shape.get()), 0.0f);
            renderer->SetMesh(mesh);
        } else if (draw == "solid") {
            auto mesh = MeshFactorySolid::CreateMesh(*(shape.get()), 0.0f);
            renderer->SetMesh(mesh);
        }
        renderer->SetTint(color);
    } else if (table.HasKey("tiledata")) {
        std::string image = table.Get<std::string>("img");
        float size = table.Get<float>("size", 1.0f);
        int width = table.Get<int>("width");
        int height = table.Get<int>("height");
        glm::ivec2 sheetSize = table.Get<glm::ivec2>("sheetsize");
        std::vector<int> data = table.GetVector<int>("tiledata");
        auto mesh = std::make_shared<QuadMesh>(image, height, width, size, data, sheetSize.x, sheetSize.y);
        renderer->SetMesh(mesh);
    }
    if (table.HasKey("scale")) {
        float scale = table.Get<float>("scale");
        renderer->SetScale(scale);
    }
    return std::move(renderer);
}

std::unique_ptr<Component> ColliderComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    // input
    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
    int tag = table.Get<int>("tag");
    int flag = table.Get<int>("flag");
    int mask = table.Get<int>("mask");
    auto factory = Engine::get().GetSceneFactory();
    auto shape = factory->GetShared<Shape>(shapeR);

    auto coll = std::unique_ptr<Collider>(new Collider(shape, tag, flag, mask));
    return coll;
}

std::unique_ptr<Component> ParallaxComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string cam = table.Get<std::string>("cam");
    float factor = table.Get<float>("factor");
    float width = table.Get<float>("width");
    float height = table.Get<float>("width");
    return std::unique_ptr<Component>(new Parallax(cam, factor, width, height));
}

std::unique_ptr<Component> MultiColliderComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    
    // input
    luabridge::LuaRef shapesR = table.Get<luabridge::LuaRef>("shapes");
    int tag = table.Get<int>("tag");
    int flag = table.Get<int>("flag");
    int mask = table.Get<int>("mask");
    std::string initShape = table.Get<std::string>("initialshape");
    auto factory = Engine::get().GetSceneFactory();
    std::unordered_map<std::string, std::shared_ptr<Shape>> shapes;
    for (int i = 0; i < shapesR.length(); ++i) {
        luabridge::LuaRef shapeR = shapesR[i+1];
        auto shape = factory->GetShared<Shape>(shapeR);
        std::string name = shapeR["name"].cast<std::string>();
        shapes[name] = shape;
    }
    auto coll = std::unique_ptr<MultiCollider>(new MultiCollider(shapes, tag, flag, mask, initShape));

    return coll;
}

std::unique_ptr<Component> StateMachineComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    std::string initialState = table.Get<std::string>("initialstate");
    std::unique_ptr<StateMachine> comp;
    if (table.HasKey("keys")) {
        auto c  = std::unique_ptr<KeyboardControlledStateMachine>(new KeyboardControlledStateMachine(initialState));
        // read the transition keys
        auto keys = table.GetVector<luabridge::LuaRef>("keys");
        for (auto& key : keys) {
            LuaTable t(key);
            int k = t.Get<int>("key");
            bool press = t.Get<bool>("press", true);
            std::string current =  t.Get<std::string>("current");
            
            if (t.HasKey("next")) {
                std::string next =  t.Get<std::string>("next");
                c->AddKey(current, k, press, std::unique_ptr<StateEvent>(new SEChangeState(next)));
            } else if (t.HasKey("func")) {
                luabridge::LuaRef func = t.Get<luabridge::LuaRef>("func");
                c->AddKey(current, k, press, std::unique_ptr<StateEvent>(new SECallback(func)));
            }
        }
        comp = std::move(c);
    } else {
        auto c = std::unique_ptr<RandomTransitionStateMachine>(new RandomTransitionStateMachine(initialState));
        // read the transition keys
        auto keys = table.GetVector<luabridge::LuaRef>("transitionmatrix");
        for (auto& key : keys) {
            float prob =  key["prob"].cast<float>();
            std::string current =  key["current"].cast<std::string>();
            std::string next =  key["next"].cast<std::string>();
            c->Add(current, next, prob);
        }
        comp = std::move(c);
    }

    // get the array of states
    auto sceneFactory = Engine::get().GetSceneFactory();
    luabridge::LuaRef ts = table.Get<luabridge::LuaRef>("states");
    for (int i = 0 ; i < ts.length(); ++i) {
        luabridge::LuaRef tss = ts[i+1];
        std::string id = tss["id"].cast<std::string>();

        auto state = std::make_shared<State>();
        state->SetId(id);
        if (!tss["init"].isNil()) {
            luabridge::LuaRef initializer = tss["init"];
            auto si = sceneFactory->Get<StateInitializer>(initializer);
            state->SetInitializer(std::move(si));
        }
        if (!tss["behavior"].isNil()) {
            luabridge::LuaRef behavior = tss["behavior"];
            auto sb = sceneFactory->Get<StateBehaviour>(behavior);
            state->SetBehaviour(std::move(sb));
        }
        if (!tss["finalizer"].isNil()) {
            luabridge::LuaRef finalizer = tss["finalizer"];
            auto si = sceneFactory->Get<StateInitializer>(finalizer);
            state->SetFinalizer(std::move(si));
        }




        comp->AddState(id, state);
    }
    return std::move(comp);
}

std::unique_ptr<Component> HotSpotComponentFactory::Create(luabridge::LuaRef& ref) {
    LuaTable table(ref);
    int priority = table.Get<int>("priority");
    auto factory = Engine::get().GetSceneFactory();
    std::unique_ptr<ScriptHotSpot> hotspot;
    if (table.HasKey("shape")) {
        luabridge::LuaRef rshape = table.Get<luabridge::LuaRef>("shape");
        auto shape = factory->GetShared<Shape>(rshape);
        hotspot = std::unique_ptr<ScriptHotSpot>(new ScriptHotSpot(shape, priority));
    } else {
        hotspot = std::unique_ptr<ScriptHotSpot>(new ScriptHotSpot(priority));
    }
    if (table.HasKey("onenter")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onenter");
        hotspot->SetOnEnter(r);
    }
    if (table.HasKey("onleave")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onleave");
        hotspot->SetOnLeave(r);
    }
    if (table.HasKey("onclick")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onclick");
        hotspot->SetOnClick(r);
    }
    if (table.HasKey("onmove")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onmove");
        hotspot->SetOnMove(r);
    }
    return hotspot;
}

std::unique_ptr<Component> DepthComponentFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    auto comp = std::unique_ptr<DepthCalculator>(new DepthCalculator);
    if (table.HasKey("depth")) {
        luabridge::LuaRef dref = table.Get<luabridge::LuaRef>("depth");
        auto depthFunc = GetFunc2D(dref);
        comp->SetDepthFunction(std::move(depthFunc));
    }
    if (table.HasKey("scale")) {
        luabridge::LuaRef dref = table.Get<luabridge::LuaRef>("scale");
        auto scaleFunc = GetFunc2D(dref);
        comp->SetScalingFunction(std::move(scaleFunc));
    }
    return comp;
}


std::unique_ptr<Component> FollowComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string cam = table.Get<std::string>("cam");
    glm::vec3 relPos = table.Get<glm::vec3>("relativepos");
    glm::vec3 up = table.Get<glm::vec3>("up");
    auto f = std::unique_ptr<Follow>(new Follow(cam, relPos, up));
    if (table.HasKey("z")) {
        float z = table.Get<float>("z");
        f->fixZ(z);
    }
    return f;
}

std::unique_ptr<Component> Controller2DComponentFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    float maxClimbAngle = table.Get<float>("maxclimbangle");
    float maxDescendAngle = table.Get<float>("maxdescendangle");
    int horCount = table.Get<int>("horizontalrays", 4);
    int vertCount = table.Get<int>("veticalrays", 4);
    float skinWidth = table.Get<float>("skinwidth", .015f);
    return std::unique_ptr<Controller2D>(new Controller2D(maxClimbAngle, maxDescendAngle, skinWidth, horCount, vertCount));
}

std::unique_ptr<Component> Dynamics2DComponentFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    float jumpHeight = table.Get<float>("jumpheight");
    float timeApex = table.Get<float>("timetojumpapex");
    return std::unique_ptr<Dynamics2D>(new Dynamics2D(jumpHeight, timeApex));
}


std::unique_ptr<Component> InfoComponentFactory::Create(luabridge::LuaRef & ref) {
    auto comp = std::unique_ptr<LuaInfo>(new LuaInfo(ref));
    return std::move(comp);
}

std::unique_ptr<Function2D> GetFunc2D(luabridge::LuaRef& ref) {
    LuaTable table(ref);
    std::string type = table.Get<std::string>("type");
    if (type == "linear_x") {
        glm::vec4 values = table.Get<glm::vec4>("values");
        std::unique_ptr<Function2D> f(new Linear2Dx(values[0], values[1], values[2], values[3]));
        return std::move(f);
    } else if (type == "linear_y") {
        glm::vec4 values = table.Get<glm::vec4>("values");
        std::unique_ptr<Function2D> f(new Linear2Dy(values[0], values[1], values[2], values[3]));
        return std::move(f);
    } else if (type == "patchwise") {

        std::unique_ptr<PatchwiseLinear2D> p(new PatchwiseLinear2D);
        for (int i = 0; i < ref.length(); ++i) {
            luabridge::LuaRef f = ref[i + 1];
            LuaTable funcTable(f);
            glm::vec4 domain = funcTable.Get<glm::vec4>("rect");
            bool isX = (funcTable.Get<char>("dir") == 'x');
            glm::vec2 bounds = funcTable.Get<glm::vec2>("bounds");
            p->AddFunction(domain, isX, bounds.x, bounds.y);
        }
        return std::move(p);
    }
    GLIB_FAIL("Unknown function " << type);
}


std::unique_ptr<Component> KeyInputComponentFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    // read input
    int maxLength = table.Get<int>("maxlength");
    // callback function when user hits enter
    luabridge::LuaRef callback = table.Get<luabridge::LuaRef>("func");
    return std::unique_ptr<KeyInput>(new KeyInput(maxLength, callback));
}

std::unique_ptr<Component> LuaKeyboardComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    auto keyListener = std::unique_ptr<LuaKeyListener>(new LuaKeyListener);
    luabridge::LuaRef hotkeys = table.Get<luabridge::LuaRef>("keys");
    for (int i = 0; i < hotkeys.length(); ++i) {
        luabridge::LuaRef hotkey = hotkeys[i+1];
        int key = hotkey["key"].cast<int>();
        luabridge::LuaRef callback = hotkey["func"];
        keyListener->AddHotKey(key, callback);
    }
    return std::move(keyListener);

}

std::unique_ptr<Component> TextViewComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    glm::vec4 viewport = table.Get<glm::vec4>("viewport");
    float w = table.Get<float>("width");
    float h = table.Get<float>("height");
    float size = table.Get<float>("size");
    float deltax = table.Get<float>("deltax", 0.0f);
    glm::vec4 color = table.Get<glm::vec4>("color", glm::vec4(255.0f));
    color /= 255.0f;
    std::string font = table.Get<std::string>("font");
    auto r = std::unique_ptr<TextView>(new TextView(w, h, size, font, color, viewport, deltax));
    return r;

}

std::unique_ptr<Component> ShadowComponentFactory::Create(luabridge::LuaRef &) {
    return std::unique_ptr<Shadow>(new Shadow);
}

std::unique_ptr<Component> PlatformComponentFactory::Create(luabridge::LuaRef &) {
    return std::unique_ptr<PlatformComponent>(new PlatformComponent);
}

std::unique_ptr<Component> BillboardComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string cam = table.Get<std::string>("cam");
    return std::unique_ptr<Billboard>(new Billboard(cam));
}

std::unique_ptr<Component> FPSComponentFactory::Create(luabridge::LuaRef &ref) {
    return std::unique_ptr<FPSCounter>(new FPSCounter);
}



//
//void HotSpotComponentFactory::operator() (luabridge::LuaRef& ref, Entity* parent) {
//    LuaTable table(ref);
//    luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
//    auto shape = ReadShape(shapeR);
//    auto hs = GetHotSpot(ref, shape);
//    Shape* s = hs->GetShape();
//    parent->AddComponent(hs);
//    int layer = table.Get<int>("layer", 1);
//    auto ce = std::make_shared<Entity>();
//    ce->SetLayer(layer);
//    auto cer = std::make_shared<Renderer>();
//    auto debugMesh = MeshFactory::CreateMesh(*s, 1.0f);
//    cer->SetMesh(debugMesh);
//    ce->AddComponent(cer);
//    parent->AddChild(ce);
//}


//std::shared_ptr<State> WalkStateFactory::Create(luabridge::LuaRef & ref) {
//    LuaTable table(ref);
//    float speed = table.Get<float>("speed");
//    auto ptr = std::make_shared<WalkState>(speed);
//    return ptr;
//
//}
//
//std::shared_ptr<State> AIWalkStateFactory::Create(luabridge::LuaRef & ref) {
//    LuaTable table(ref);
//    float speed = table.Get<float>("speed");
//    std::string target = table.Get<std::string>("target");
//    auto ptr = std::make_shared<AIWalk>(target, speed);
//    return ptr;
//
//}


//std::shared_ptr<State> WalkCollisionStateFactory::Create(luabridge::LuaRef & ref) {
//    LuaTable table(ref);
//    float speed = table.Get<float>("speed");
//    float width = table.Get<float>("width");
//    float height = table.Get<float>("height");
//    int horRays = table.Get<int>("horizontal_rays");
//    int vertRays = table.Get<int>("vertical_rays");
//
//    auto ptr = std::make_shared<WalkStateCollision>(width, height, speed, horRays, vertRays);
//    if (table.HasKey("anims")) {
//        luabridge::LuaRef animsTable = table.Get<luabridge::LuaRef>("anims");
//        for (int i = 0; i < animsTable.length(); ++i) {
//            luabridge::LuaRef anim = animsTable[i+1];
//            std::string id = anim["id"].cast<std::string>();
//            std::string animName = anim["anim"].cast<std::string>();
//            ptr->AddAnimation(id, animName);
//        }
//    }
//    return ptr;
//
//}

//
//std::shared_ptr<State> HitStateFactory::Create(luabridge::LuaRef & ref) {
//    LuaTable table(ref);
//    std::string anim = table.Get<std::string>("anim");
//
//    int frame = table.Get<int>("frame", -1);
//    if (frame != -1) {
//        int mask =table.Get<int>("mask");
//        glm::vec2 offset = table.Get<glm::vec2>("offset");
//        luabridge::LuaRef ts = table.Get<luabridge::LuaRef>("shape");
//        auto shape = ReadShape(ts);
//        luabridge::LuaRef callback = table.Get<luabridge::LuaRef>("func");
//        auto ptr = std::make_shared<HitCollision>(anim, frame, shape, offset, mask, callback);
//        return ptr;
//
//
//    } else {
//        auto ptr = std::make_shared<Hit>(anim);
//        return ptr;
//    }
//
//}

//StateMachineComponentFactory::StateMachineComponentFactory() {
//
//
//}
//
//


//void SwitchComponentFactory::operator()(luabridge::LuaRef & ref, Entity * p) {
//    LuaTable table(ref);
//    std::vector<std::string> stateNames = table.GetVector<std::string>("states");
//    std::string initialState = table.Get<std::string>("initial");
//    auto sw = std::make_shared<Switch>(stateNames, initialState);
//    p->AddComponent(sw);
//}





//
//
//
//
//void ButtonComponentFactory::operator() (luabridge::LuaRef& ref, Entity* parent) {
//    LuaTable table(ref);
//    auto renderer = ReadTextComponent(ref);
//    // for a button the shape is determined by the text size
//    auto bounds = renderer->GetBounds();
//    float w = bounds.max.x - bounds.min.x;
//    float h = bounds.max.y - bounds.min.y;
//    auto shape = std::make_shared<Rect>(w, h);
//    //auto debugMesh = MeshFactory::CreateMesh(*(shape.get()), 1.0f);
//    auto hs = GetHotSpot(ref, shape);
//    parent->AddComponent(renderer);
//    parent->AddComponent(hs);
//}
//
//




std::unique_ptr<Runner> HotSpotManagerFactory::Create(luabridge::LuaRef&) {
    auto hsm = std::unique_ptr<HotSpotManager>(new HotSpotManager);
    return hsm;
    //Engine::get().AddRunner(hsm);
    //g.RegisterToMouseEvent(hsm.get());
}

std::unique_ptr<Runner> SchedulerFactory::Create(luabridge::LuaRef&) {
    // set-up the scripting engine
    auto scheduler = std::unique_ptr<Scheduler>(new Scheduler);
    return scheduler;
}

std::unique_ptr<Runner> CollisionEngineFactory::Create(luabridge::LuaRef& ref) {
    LuaTable table(ref);
    glm::vec2 collisionSize = table.Get<glm::vec2>("size");
    auto ce = std::unique_ptr<CollisionEngine>(new CollisionEngine(collisionSize.x, collisionSize.y));
    bool coll25 = table.Get<bool>("coll25", false);
    if (coll25) {
        float eps = table.Get<float>("eps");
        ce->Enable25DCollision(eps);
    }
    if (table.HasKey("response")) {
        // set the collision responsesfg
        luabridge::LuaRef resp = table.Get<luabridge::LuaRef>("response");
        std::unique_ptr<CollisionResponseManager> crm (new CollisionResponseManager);
        for (int i = 0; i < resp.length();++i) {
            luabridge::LuaRef a = resp[i+1];
            LuaTable at(a);
            std::vector<int> tags = at.GetVector<int>("tag");
            std::unique_ptr<LuaCollisionResponse> l(new LuaCollisionResponse);
            if (at.HasKey("onenter")) {
                luabridge::LuaRef onEnter = at.Get<luabridge::LuaRef>("onenter");
                l->SetOnEnter(onEnter);
            }
            if (at.HasKey("onleave")) {
                luabridge::LuaRef onLeave = at.Get<luabridge::LuaRef>("onleave");
                l->SetOnLeave(onLeave);
            }
            if (at.HasKey("onstay")) {
                luabridge::LuaRef onStay = at.Get<luabridge::LuaRef>("onstay");
                l->SetOnStay(onStay);
            }
            crm->AddCollisionResponse(tags[0], tags[1], std::move(l));

        }
        ce->SetResponseManager(std::move(crm));
    }

    return std::move(ce);

}

std::unique_ptr<StateInitializer> AnimInitializerFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string anim = table.Get<std::string>("anim");
    return std::unique_ptr<AnimInitializer>(new AnimInitializer(anim));
}

std::unique_ptr<StateInitializer> AnimColliderInitializerFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string anim = table.Get<std::string>("anim");
    std::string collider = table.Get<std::string>("collider", "");
    return std::unique_ptr<AnimColliderInitializer>(new AnimColliderInitializer(anim, collider));
}


std::unique_ptr<StateInitializer> LuaInitializerFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    luabridge::LuaRef func = table.Get<luabridge::LuaRef>("func");
    return std::unique_ptr<LuaInitializer>(new LuaInitializer(func));
}

std::unique_ptr<StateInitializer> LuaAnimColliderInitializerFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    luabridge::LuaRef func = table.Get<luabridge::LuaRef>("func");
    return std::unique_ptr<LuaAnimColliderInitializer>(new LuaAnimColliderInitializer(func));
}



//std::shared_ptr<State> BasicStateFactory::Create(luabridge::LuaRef & r) {
//    LuaTable table(r);
//    std::string anim = table.Get<std::string>("anim");
//    std::vector<std::string> colliders = table.GetVector<std::string>("colliders");
//    return std::make_shared<BasicState>(anim, colliders);
//}
//
