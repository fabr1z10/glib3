#include <gfx/factories.h>
#include <gfx/components/basicrenderer.h>
#include <gfx/font.h>
#include <gfx/engine.h>
#include <gfx/textmesh.h>
#include <glm/gtx/transform.hpp>
#include <gfx/components/keyinput.h>
#include <gfx/collisionengine3d.h>
#include <gfx/components/switch.h>
#include <gfx/quadmesh.h>
#include <gfx/meshfactory.h>
#include <gfx/components/smartcollider.h>
#include <gfx/components/skeletalcollider.h>
#include <gfx/components/scripthotspot.h>
#include <gfx/components/luakeylistener.h>
#include <gfx/components/depth.h>
#include <gfx/components/follow.h>
#include <gfx/components/follow3d.h>
#include <gfx/components/inputmethod.h>
#include <gfx/components/depth25.h>
#include <gfx/components/mover.h>
#include <gfx/components/ellipsemover.h>

#include <gfx/components/billboard.h>
#include <gfx/components/parallax.h>
#include <gfx/components/parallax3d.h>
#include <gfx/components/info.h>
#include <gfx/components/light.h>
#include <gfx/components/raycastcontroller.h>
#include <gfx/components/statemachine.h>
#include <gfx/components/extstatemachine.h>
#include <gfx/model/model3D.h>
#include <gfx/dynamicworld.h>
#include <gfx/model/basicmodel.h>
#include <gfx/model/textmodel.h>
#include <gfx/components/keyinput.h>
#include <gfx/luacollision.h>
#include <gfx/walkstate.h>
#include <gfx/hit.h>
#include <gfx/aiwalk.h>
#include <gfx/components/shadow.h>
#include <gfx/states/animinitializer.h>
#include <gfx/math/geom.h>
#include <gfx/components/controller2d.h>
#include <gfx/components/controller3d.h>
#include <gfx/components/dynamics2d.h>
#include <gfx/runner.h>
#include <gfx/states/luainitializer.h>
#include <gfx/components/platform.h>
#include <gfx/components/fpscounter.h>
#include <gfx/components/cursor.h>
#include <gfx/states/walk25.h>
#include <gfx/states/jump25.h>

#include <gfx/states/hit25.h>
#include <gfx/states/simple.h>
#include <gfx/components/stateactions.h>
#include <gfx/components/garbagecollect.h>

std::shared_ptr<Component> TextComponentFactory::Create(luabridge::LuaRef &ref) {

    LuaTable table(ref);
    std::string text = table.Get<std::string>("id");
    std::string font = table.Get<std::string>("font");
    float size = table.Get<float>("size", 8);
    TextAlignment align = table.Get<TextAlignment>("align", TOP_LEFT);
    float maxWidth = table.Get<float>("maxwidth", 0.0f);
    glm::vec4 color = table.Get<glm::vec4>("color", glm::vec4(255.0f));
    color /= 255.0f;
    Font* f = Engine::get().GetAssetManager().GetFont(font).get();
    auto mesh = std::make_shared<TextMesh>(f, text, size, align, maxWidth);
    glm::vec2 offset = mesh->getOffset();
    auto model = std::make_shared<TextModel>(mesh);
    auto renderer = Ref::Create<BasicRenderer>(model);
    renderer->SetTransform(glm::translate(glm::vec3(offset, 0.0f)));
    renderer->SetTint(color);
    return renderer;
}


std::shared_ptr<Component> GfxComponentFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);

    std::shared_ptr<Component> renderer;

    if (table.HasKey("image")) {
        std::string image = table.Get<std::string>("image");
        float w = table.Get<float>("width", 0.0f);
        float h = table.Get<float>("height", 0.0f);
        glm::vec2 offset = table.Get<glm::vec2>("offset", glm::vec2(0.0f));
        std::shared_ptr<IMesh> mesh;
        if (table.HasKey("quad")) {
            glm::ivec4 quad = table.Get<glm::ivec4>("quad");
            mesh = std::make_shared<QuadMesh>(image, w, h, offset, quad[0], quad[1], quad[2], quad[3]);
        } else {
            glm::vec2 repeat = table.Get<glm::vec2>("rep", glm::vec2(1.0f, 1.0f));
            glm::vec2 skew = table.Get<glm::vec2>("skew", glm::vec2(0.0f, 0.0f));
            mesh = std::make_shared<QuadMesh>(image, w, h, repeat.x, repeat.y, skew.x, skew.y, offset);
        }
        auto model = std::make_shared<BasicModel>(mesh);
        renderer = Ref::Create<BasicRenderer>(model);
    } else if (table.HasKey("shape")) {
        luabridge::LuaRef sref = table.Get<luabridge::LuaRef>("shape");
        std::string draw = table.Get<std::string>("draw","outline");
        glm::vec4 color = table.Get<glm::vec4>("color");
        color /= 255.0f;
        auto factory = Engine::get().GetSceneFactory();
        auto shape = factory->makeShape(sref);
        std::shared_ptr<IMesh> mesh;
        if (draw == "outline") {
            mesh = MeshFactory::CreateMesh(*(shape.get()), 0.0f);
        } else if (draw == "solid") {
            mesh = MeshFactorySolid::CreateMesh(*(shape.get()), 0.0f);
        }
        auto model = std::make_shared<BasicModel>(mesh);
        auto rend =Ref::Create<BasicRenderer>(model);
        rend->SetTint(color);
        renderer =rend;
    } else if (table.HasKey("tiledata")) {
        std::string image = table.Get<std::string>("img");
        float size = table.Get<float>("size", 1.0f);
        int width = table.Get<int>("width");
        int height = table.Get<int>("height");
        int repx = table.Get<int>("repx", 1);
        int repy = table.Get<int>("repy", 1);

        glm::ivec2 sheetSize = table.Get<glm::ivec2>("sheetsize");
        std::vector<int> data = table.GetVector<int>("tiledata");
        auto mesh = std::make_shared<QuadMesh>(image, height, width, size, data, sheetSize.x, sheetSize.y, repx, repy);
        auto model = std::make_shared<BasicModel>(mesh);
        renderer = Ref::Create<BasicRenderer>(model);
    } else if (table.HasKey("model")) {
        std::string modelId = table.Get<std::string>("model");
        auto model = Engine::get().GetAssetManager().GetModel(modelId);
        renderer = Ref::Create<BasicRenderer>(model);
    } else if (table.HasKey("prim3d")) {
        auto factory = Engine::get().GetSceneFactory();
        auto model = factory->makeModel(table.Get<luabridge::LuaRef>("prim3d"));
        renderer = Ref::Create<BasicRenderer>(model);
    }
    return std::move(renderer);
}

std::shared_ptr<Component> LightComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string cl = table.Get<std::string>("class");
    if (cl == "ambient") {

        glm::vec3 color = table.Get<glm::vec3>("color");
        color /= 255.0f;
        return Ref::Create<AmbientLight>(color);
    } else if (cl=="directional") {
        glm::vec3 dir = table.Get<glm::vec3>("dir");
        glm::vec3 color = table.Get<glm::vec3>("color");
        color /= 255.0f;
        return Ref::Create<DirectionalLight>(dir, color);

    } else {
        GLIB_FAIL("Unknown light class: " << cl);
    }

}

//std::shared_ptr<Component> Gfx3DComponentFactory::Create(luabridge::LuaRef & ref){
//    LuaTable table(ref);
//
//    auto renderer = Ref::Create<Renderer>();
//    std::string shape = table.Get<std::string>("shape");
//    if (shape == "plane") {
//        float width = table.Get<float>("width");
//        float depth = table.Get<float>("depth");
//
//        if (table.HasKey("color")) {
//            glm::vec4 color = table.Get<glm::vec4>("color");
//            color /= 255.0f;
//            auto mesh = Model3DFactory::CreatePlane(width, depth, color);
//            renderer->SetModel(std::make_shared<BasicModel>(mesh));
//        } else {
//            std::string image = table.Get<std::string>("image");
//            std::string plane = table.Get<std::string>("plane", "xy");
//            //Plane p = (plane == "xy") ? Plane::XY : Plane::XZ;
//            glm::vec2 repeat = table.Get<glm::vec2>("rep", glm::vec2(1.0f, 1.0f));
//            glm::vec2 skew = table.Get<glm::vec2>("skew", glm::vec2(0.0f, 0.0f));
//            glm::vec2 offset = table.Get<glm::vec2>("offset", glm::vec2(0.0f));
//            auto mesh = std::make_shared<QuadMesh>(image, width, depth, repeat.x, repeat.y, skew.x, skew.y, offset);
//            renderer->SetModel(std::make_shared<BasicModel>(mesh));
//        }
//    }
//    return (renderer);
//
//}

std::shared_ptr<Component> ColliderComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);

    // input
    std::shared_ptr<Shape> shape;
    auto factory = Engine::get().GetSceneFactory();
    if (table.HasKey("shape")) {
        luabridge::LuaRef shapeR = table.Get<luabridge::LuaRef>("shape");
        shape = factory->makeShape(shapeR);
    }
    int tag = table.Get<int>("tag");
    int flag = table.Get<int>("flag");
    int mask = table.Get<int>("mask");
    

    auto coll = Ref::Create<SimpleCollider>(shape, tag, flag, mask);
    return coll;
}



std::shared_ptr<Component> SmartColliderComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    int tag = table.Get<int>("tag");
    int flag = table.Get<int>("flag");
    int mask = table.Get<int>("mask");
    auto coll = Ref::Create<SmartCollider>(flag, mask, tag);
    table.ProcessVector("attack_tags", [coll] (luabridge::LuaRef ref) {
        std::string anim = ref["anim"].cast<std::string>();
        int attackTag = ref["tag"].cast<int>();
        int attackMask = ref["mask"].cast<int>();
        coll->AddAttackTag(anim, attackTag, attackMask);
    });
    table.ProcessVector("collision_overrides", [coll] (luabridge::LuaRef ref) {
        std::string state = ref["state"].cast<std::string>();
        int flag = ref["flag"].cast<int>();
        int mask = ref["mask"].cast<int>();
        int tag = ref["tag"].cast<int>();
        coll->addStateCollisionDetails(state, flag, mask, tag);
    });
    return coll;
}

std::shared_ptr<Component> SkeletalColliderComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    int tag = table.Get<int>("tag");
    int flag = table.Get<int>("flag");
    int mask = table.Get<int>("mask");

    float scale = table.Get<float>("scale", 1.0f);
    glm::ivec2 attack = table.Get<glm::ivec2>("attack", glm::ivec2(-1,-1));
    auto coll = Ref::Create<SkeletalCollider>(flag, mask, tag);
    if (attack[0] != -1) {
        coll->setAttack(attack[0], attack[1]);
    }
//    table.ProcessVector("bounds", [coll, scale] (luabridge::LuaRef ref) {
//
//        LuaTable t(ref);
//        std::string anim = t.Get<std::string>("anim");
//        float x = t.Get<float>("x");
//        float y = t.Get<float>("y");
//        float width = t.Get<float>("width");
//        float height = t.Get<float>("height");
//        coll->addBound(anim, x, y, width, height, scale);
//    });
//    table.ProcessVector("attack", [coll,scale ] (luabridge::LuaRef ref) {
//
//        LuaTable t(ref);
//        std::string anim = t.Get<std::string>("anim");
//        float time = t.Get<float>("t");
//        int mask = t.Get<int>("mask");
//        int tag = t.Get<int>("tag");
//        float x = t.Get<float>("x");
//        float y = t.Get<float>("y");
//        float width = t.Get<float>("width");
//        float height = t.Get<float>("height");
//        coll->addAttack(anim, time, x, y, width, height, mask, tag, scale);
//    });
    return coll;

}

//
//std::shared_ptr<Component> ParallaxComponentFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    std::string cam = table.Get<std::string>("cam");
//    float factor = table.Get<float>("factor");
//    float width = table.Get<float>("width");
//    float height = table.Get<float>("width");
//    return Ref::Create<Parallax>(cam, factor, width, height,0,0);
//}

std::shared_ptr<Component> Parallax3DComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string cam = table.Get<std::string>("cam");
    std::string img = table.Get<std::string>("img");
    float z = table.Get<float>("z");
    return Ref::Create<Parallax3D>(cam,z,img);
}

//std::shared_ptr<Component> MultiColliderComponentFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//
//    // input
//    luabridge::LuaRef shapesR = table.Get<luabridge::LuaRef>("shapes");
//    int tag = table.Get<int>("tag");
//    int flag = table.Get<int>("flag");
//    int mask = table.Get<int>("mask");
//    std::string initShape = table.Get<std::string>("initialshape");
//    auto factory = Engine::get().GetSceneFactory();
//    std::unordered_map<std::string, std::shared_ptr<Shape>> shapes;
//    for (int i = 0; i < shapesR.length(); ++i) {
//        luabridge::LuaRef shapeR = shapesR[i+1];
//        auto shape = factory->makeShape(shapeR);
//        std::string name = shapeR["name"].cast<std::string>();
//        shapes[name] = shape;
//    }
//    auto coll = Ref::Create<MultiCollider>(shapes, tag, flag, mask, initShape);
//
//    return coll;
//}


std::shared_ptr<Component> StateMachineCompFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string initialState = table.Get<std::string>("initialstate");
    auto ptr = Ref::Create<StateMachine>(initialState);
    auto factory = Engine::get().GetSceneFactory();

    luabridge::LuaRef statesRef = table.Get<luabridge::LuaRef>("states");
    for (int i = 0; i < statesRef.length(); ++i) {
        luabridge::LuaRef stateRef = statesRef[i+1];
        std::string key = stateRef["id"].cast<std::string>();
        luabridge::LuaRef stateDef = stateRef["state"];
        auto state = factory->makeState(stateDef);
        ptr->AddState(key, state);
    }
    return ptr;

}

std::shared_ptr<Component> ExtStateMachineCompFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string initialState = table.Get<std::string>("initialstate");
    auto ptr = Ref::Create<ExtendedStateMachine>(initialState);
    auto factory = Engine::get().GetSceneFactory();
    
    luabridge::LuaRef statesRef = table.Get<luabridge::LuaRef>("states");
    for (int i = 0; i < statesRef.length(); ++i) {
        luabridge::LuaRef stateRef = statesRef[i+1];
        std::string key = stateRef["id"].cast<std::string>();
        luabridge::LuaRef stateDef = stateRef["state"];
        auto state = factory->makeState(stateDef);
        ptr->AddState(key, state);
    }
    
    table.ProcessVector("keys", [ptr] (luabridge::LuaRef ref) {
        int key = ref["id"].cast<int>();
        luabridge::LuaRef callback = ref["func"];
        ptr->AddKey(key, callback);
    });
    
    return ptr;
    
}


std::shared_ptr<Component> PolyMoverCompFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    glm::vec2 origin = table.Get<glm::vec2>("origin", glm::vec2(0.0f));
    int loopType = table.Get<int>("loop_type");
    int startIndex = table.Get<int>("start_index", 0);
    float pct = table.Get<float>("pct", 0.0f);



    auto ptr = std::make_shared<PolygonalMover>(loopType, origin);
    ptr->setStartPosition(startIndex, pct);
    table.ProcessVector("movements", [ptr] (luabridge::LuaRef ref) {
        LuaTable t(ref);
        glm::vec2 delta = t.Get<glm::vec2>("delta");
        float speed = t.Get<float>("speed");
        float hold = t.Get<float>("hold", 0.0f);
        ptr->addMovement(delta, speed, hold);
    });

    if (table.HasKey("callback")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("callback");
        ptr->setCompleteCallback(r);
    }
    return ptr;
}

std::shared_ptr<Component> EllipseMoverCompFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    glm::vec2 origin = table.Get<glm::vec2>("origin", glm::vec2(0.0f));
    glm::vec2 radii = table.Get<glm::vec2>("radii");
    float period = table.Get<float>("period");


    auto ptr = std::make_shared<EllipseMover>(radii[0], radii[1], period, origin);
    return ptr;
}

//std::unique_ptr<Component> StateMachineComponentFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//
//    std::string initialState = table.Get<std::string>("initialstate");
//    std::unique_ptr<StateMachine> comp;
//    if (table.HasKey("keys")) {
//        auto c  = std::unique_ptr<KeyboardControlledStateMachine>(new KeyboardControlledStateMachine(initialState));
//        // read the transition keys
//        auto keys = table.GetVector<luabridge::LuaRef>("keys");
//        for (auto& key : keys) {
//            LuaTable t(key);
//            int k = t.Get<int>("key");
//            bool press = t.Get<bool>("press", true);
//            std::string current =  t.Get<std::string>("current");
//
//            if (t.HasKey("next")) {
//                std::string next =  t.Get<std::string>("next");
//                c->AddKey(current, k, press, std::unique_ptr<StateEvent>(new SEChangeState(next)));
//            } else if (t.HasKey("func")) {
//                luabridge::LuaRef func = t.Get<luabridge::LuaRef>("func");
//                c->AddKey(current, k, press, std::unique_ptr<StateEvent>(new SECallback(func)));
//            }
//        }
//        comp = std::move(c);
//    } else {
//        auto c = std::unique_ptr<RandomTransitionStateMachine>(new RandomTransitionStateMachine(initialState));
//        // read the transition keys
//        auto keys = table.GetVector<luabridge::LuaRef>("transitionmatrix");
//        for (auto& key : keys) {
//            float prob =  key["prob"].cast<float>();
//            std::string current =  key["current"].cast<std::string>();
//            std::string next =  key["next"].cast<std::string>();
//            c->Add(current, next, prob);
//        }
//        comp = std::move(c);
//    }
//
//    // get the array of states
//    auto sceneFactory = Engine::get().GetSceneFactory();
//    luabridge::LuaRef ts = table.Get<luabridge::LuaRef>("states");
//    for (int i = 0 ; i < ts.length(); ++i) {
//        luabridge::LuaRef tss = ts[i+1];
//        std::string id = tss["id"].cast<std::string>();
//
//        auto state = std::make_shared<State>();
//        state->SetId(id);
//        if (!tss["init"].isNil()) {
//            luabridge::LuaRef initializer = tss["init"];
//            auto si = sceneFactory->Get<StateInitializer>(initializer);
//            state->SetInitializer(std::move(si));
//        }
//        if (!tss["behavior"].isNil()) {
//            luabridge::LuaRef behavior = tss["behavior"];
//            auto sb = sceneFactory->Get<StateBehaviour>(behavior);
//            state->SetBehaviour(std::move(sb));
//        }
//        if (!tss["finalizer"].isNil()) {
//            luabridge::LuaRef finalizer = tss["finalizer"];
//            auto si = sceneFactory->Get<StateInitializer>(finalizer);
//            state->SetFinalizer(std::move(si));
//        }
//
//
//
//
//        comp->AddState(id, state);
//    }
//    return std::move(comp);
//}

std::shared_ptr<Component> HotSpotComponentFactory::Create(luabridge::LuaRef& ref) {
    LuaTable table(ref);
    int priority = table.Get<int>("priority");
    auto factory = Engine::get().GetSceneFactory();
    std::shared_ptr<ScriptHotSpot> hotspot;
    if (table.HasKey("shape")) {
        luabridge::LuaRef rshape = table.Get<luabridge::LuaRef>("shape");
        auto shape = factory->makeShape(rshape);
        hotspot = Ref::Create<ScriptHotSpot>(shape, priority);
    } else {
        hotspot = Ref::Create<ScriptHotSpot>(priority);
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
        std::unique_ptr<LuaFunction> f(new LuaFunction(r));
        hotspot->SetOnClick(std::move(f));
    }
    if (table.HasKey("onrmbclick")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onrmbclick");
        std::unique_ptr<LuaFunction> f(new LuaFunction(r));
        hotspot->SetOnRightMouseButtonClick(std::move(f));
    }
    if (table.HasKey("onmove")) {
        luabridge::LuaRef r = table.Get<luabridge::LuaRef>("onmove");
        hotspot->SetOnMove(r);
    }
    return hotspot;
}

std::shared_ptr<Component> DepthComponentFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    auto comp = Ref::Create<DepthCalculator>();
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


std::shared_ptr<Component> FollowComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string cam = table.Get<std::string>("cam");
    glm::vec3 relPos = table.Get<glm::vec3>("relativepos");
    glm::vec3 up = table.Get<glm::vec3>("up");
    auto f = Ref::Create<Follow>(cam, relPos, up);
    if (table.HasKey("z")) {
        float z = table.Get<float>("z");
        f->fixZ(z);
    }
    return f;
}
//std::unique_ptr<Component> Follow3DComponentFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    std::string cam = table.Get<std::string>("cam");
//    float dist = table.Get<float>("distance");
//    float elev = table.Get<float>("elevation");
//    return std::unique_ptr<Component>(new Follow3D(cam, dist, elev));
//
//}

std::shared_ptr<Component> Controller2DComponentFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    float maxClimbAngle = table.Get<float>("maxclimbangle");
    float maxDescendAngle = table.Get<float>("maxdescendangle");
    int horCount = table.Get<int>("horizontalrays", 4);
    int vertCount = table.Get<int>("veticalrays", 4);
    float skinWidth = table.Get<float>("skinwidth", .015f);
    return Ref::Create<Controller2D>(maxClimbAngle, maxDescendAngle, skinWidth, horCount, vertCount);
}

std::shared_ptr<Component> Controller3DComponentFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    float maxClimbAngle = table.Get<float>("maxclimbangle");
    float maxDescendAngle = table.Get<float>("maxdescendangle");
    int horCount = table.Get<int>("horizontalrays", 4);
    int vertCount = table.Get<int>("veticalrays", 4);
    float skinWidth = table.Get<float>("skinwidth", .015f);
    return Ref::Create<Controller3D>(maxClimbAngle, maxDescendAngle, skinWidth, horCount, vertCount);
}

std::shared_ptr<Component> Dynamics2DComponentFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    float g = table.Get<float>("gravity");
    auto ptr = Ref::Create<Dynamics2D>(g);
    if (table.HasKey("additional_info")) {
        luabridge::LuaRef ainfo = table.Get<luabridge::LuaRef>("additional_info");
        ptr->addAdditionalProps(ainfo);
    }
    return ptr;
}

std::shared_ptr<Component> PropertiesCompFactory::Create(luabridge::LuaRef & ref) {
    LuaTable table(ref);
    auto ptr = Ref::Create<Properties>();
    if (table.HasKey("additional_info")) {
        luabridge::LuaRef ainfo = table.Get<luabridge::LuaRef>("additional_info");
        ptr->addAdditionalProps(ainfo);
    }
    return ptr;
}

std::shared_ptr<Component> InfoComponentFactory::Create(luabridge::LuaRef & ref) {
    auto comp = Ref::Create<LuaInfo>(ref);

    return comp;

}

std::shared_ptr<Component> KeyboardInputMethodCompFactory::Create(luabridge::LuaRef &ref) {
    auto comp = std::unique_ptr<KeyboardInputMethod>(new KeyboardInputMethod);
    return comp;
}

std::shared_ptr<Function2D> GetFunc2D(luabridge::LuaRef& ref) {
    LuaTable table(ref);
    std::string type = table.Get<std::string>("type");
    if (type == "linear_x") {
        glm::vec4 values = table.Get<glm::vec4>("values");
        std::unique_ptr<Function2D> f(new Linear2Dx(values[0], values[1], values[2], values[3]));
        return f;
    } else if (type == "linear_y") {
        glm::vec4 values = table.Get<glm::vec4>("values");
        std::unique_ptr<Function2D> f(new Linear2Dy(values[0], values[1], values[2], values[3]));
        return f;
    } else if (type == "constant") {
        float value = table.Get<float>("value");
        std::unique_ptr<Function2D> f(new Constant2D(value));
        return f;
    } else if (type == "patchwise") {
        auto p = std::make_shared<PatchwiseLinear2D>();
        luabridge::LuaRef quads = table.Get<luabridge::LuaRef>("rects");
        for (int i = 0; i < quads.length(); ++i) {
            luabridge::LuaRef f = quads[i + 1];
            LuaTable funcTable(f);
            glm::vec2 pos = funcTable.Get<glm::vec2>("pos");
            glm::vec2 size = funcTable.Get<glm::vec2>("size");
            glm::vec4 domain (pos.x, pos.y, pos.x+size.x, pos.y +size.y);
            //luabridge::LuaRef fref = funcTable.Get<luabridge::LuaRef>("func");
            auto fu = GetFunc2D(f);
            p->AddFunction(domain, std::move(fu));
        }
        return p;
    }
    GLIB_FAIL("Unknown function " << type);
}


//std::unique_ptr<Component> KeyInputComponentFactory::Create(luabridge::LuaRef & ref) {
//    LuaTable table(ref);
//    // read input
//    //int maxLength = table.Get<int>("maxlength");
//    // callback function when user hits enter
//    luabridge::LuaRef callback = table.Get<luabridge::LuaRef>("func");
//    return std::unique_ptr<KeyInput>(new KeyInput(callback));
//}

std::shared_ptr<Component> LuaKeyboardComponentFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    auto keyListener = std::make_shared<LuaKeyListener>();
    luabridge::LuaRef hotkeys = table.Get<luabridge::LuaRef>("keys");
    for (int i = 0; i < hotkeys.length(); ++i) {
        luabridge::LuaRef hotkey = hotkeys[i+1];
        int key = hotkey["key"].cast<int>();
        luabridge::LuaRef callback = hotkey["func"];
        keyListener->addHotKey(key, callback);
    }
    return keyListener;

}


std::shared_ptr<Component> ShadowComponentFactory::Create(luabridge::LuaRef &) {
    return Ref::Create<Shadow>();
}

std::shared_ptr<Component> PlatformComponentFactory::Create(luabridge::LuaRef &) {
    return Ref::Create<PlatformComponent>();
}

//std::unique_ptr<Component> BillboardComponentFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    std::string cam = table.Get<std::string>("cam");
//    return std::unique_ptr<Billboard>(new Billboard(cam));
//}

std::shared_ptr<Component> FPSComponentFactory::Create(luabridge::LuaRef &ref) {
    return Ref::Create<FPSCounter>();
}

std::shared_ptr<Component> CursorComponentFactory::Create(luabridge::LuaRef& ref) {
    return std::make_shared<Cursor>();
}

//std::unique_ptr<Component> RaycastControllerComponentFactory::Create(luabridge::LuaRef& ref) {
//    LuaTable table(ref);
//
//    std::string heightMap = table.Get<std::string>("heightmap", "");
//    return std::unique_ptr<Component>(new RaycastController(heightMap));
//
//}

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
//    cer->SetModel(debugMesh);
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




std::shared_ptr<Runner> HotSpotManagerFactory::Create(luabridge::LuaRef& ref) {
    auto hsm = Ref::Create<HotSpotManager>();
    LuaTable table(ref);
    if (table.HasKey("keys")) {

        luabridge::LuaRef keys = table.Get<luabridge::LuaRef>("keys");
        for (int i = 0; i < keys.length(); ++i) {
            luabridge::LuaRef key = keys[i+1];
            LuaTable t2(key);
            KeyEvent event;
            event.key = t2.Get<int>("key");
            event.action = GLFW_PRESS;
            event.mods = 0;
            LuaFunction f(t2.Get<luabridge::LuaRef>("func"));
            hsm->AddCallback(event, [f] () { f.execute(); });
        }
    }
    if (table.HasKey("rmbclick")) {
        LuaFunction f(table.Get<luabridge::LuaRef>("rmbclick"));
        hsm->setRmbClickCallback([f] (float x, float y) { f.execute(x, y);});

    }
    if (table.HasKey("lmbclick")) {
        LuaFunction f(table.Get<luabridge::LuaRef>("lmbclick"));
        hsm->setLmbClickCallback([f] (float x, float y) { f.execute(x, y);});

    }
    if (table.HasKey("tag")) {
        hsm->SetTag(table.Get<std::string>("tag"));
    }

    return hsm;
    //Engine::get().AddRunner(hsm);
    //g.RegisterToMouseEvent(hsm.get());
}

std::shared_ptr<Runner> SchedulerFactory::Create(luabridge::LuaRef&) {
    return Ref::Create<Scheduler>();
}

std::shared_ptr<Runner> DynamicWorldBuilderFactory::Create(luabridge::LuaRef& ref) {
    LuaTable table(ref);
    float cellWidth = table.Get<float>("width");
    float cellHeight = table.Get<float>("height");
    std::string cam = table.Get<std::string>("cam");
    luabridge::LuaRef items = table.Get<luabridge::LuaRef>("items");
    auto factory = Engine::get().GetSceneFactory();
    auto builder = Ref::Create<DynamicWorldBuilder>(cellWidth, cellHeight, cam);
    for (int i = 0; i <items.length(); ++i) {
        luabridge::LuaRef rnode = items[i+1];
        auto node  = factory->makeEntity(rnode);
        //rootNode->AddChild(node);
        builder->AddItem(node);
    }
    return builder;
}





std::shared_ptr<Runner> CollisionEngineFactory::Create(luabridge::LuaRef& ref) {
    LuaTable table(ref);
    glm::vec2 collisionSize = table.Get<glm::vec2>("size");
    auto ce = Ref::Create<CollisionEngine>(collisionSize.x, collisionSize.y);
    bool coll25 = table.Get<bool>("coll25", false);
    if (coll25) {
        float eps = table.Get<float>("eps", 0.01);
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

    return ce;

}

std::shared_ptr<Component> Depth25CompFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    float g = table.Get<float>("gravity");
    float x = table.Get<float>("x");
    float depth = table.Get<float>("depth");
    float elevation = table.Get<float>("elevation");
    return std::make_shared<Depth25>(g, x,depth, elevation);
}

std::shared_ptr<Runner> CollisionEngine3DFactory::Create(luabridge::LuaRef& ref) {
    LuaTable table(ref);
    glm::vec3 collisionSize = table.Get<glm::vec3>("size");
    auto ce = Ref::Create<CollisionEngine3D>(collisionSize.x, collisionSize.y,collisionSize.z);

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

    return ce;

}

//std::unishared_ptrque_ptr<StateInitializer> AnimInitializerFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    std::string anim = table.Get<std::string>("anim");
//    return std::unique_ptr<AnimInitializer>(new AnimInitializer(anim));
//}
//
//std::shar<StateInitializer> AnimColliderInitializerFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    std::string anim = table.Get<std::string>("anim");
//    std::string collider = table.Get<std::string>("collider", "");
//    return std::unique_ptr<AnimColliderInitializer>(new AnimColliderInitializer(anim, collider));
//}
//
//
//std::unique_ptr<StateInitializer> LuaInitializerFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    luabridge::LuaRef func = table.Get<luabridge::LuaRef>("func");
//    return std::unique_ptr<LuaInitializer>(new LuaInitializer(func));
//}
//
//std::unique_ptr<StateInitializer> LuaAnimColliderInitializerFactory::Create(luabridge::LuaRef &ref) {
//    LuaTable table(ref);
//    luabridge::LuaRef func = table.Get<luabridge::LuaRef>("func");
//    return std::unique_ptr<LuaAnimColliderInitializer>(new LuaAnimColliderInitializer(func));
//}
//


//std::shared_ptr<State> BasicStateFactory::Create(luabridge::LuaRef & r) {
//    LuaTable table(r);
//    std::string anim = table.Get<std::string>("anim");
//    std::vector<std::string> colliders = table.GetVector<std::string>("colliders");
//    return std::make_shared<BasicState>(anim, colliders);
//}
//

std::shared_ptr<State> StateFactory::Create(luabridge::LuaRef &ref) {
    throw;
}

void StateFactory::init(const LuaTable& table, std::shared_ptr<State> state) {
    // need to do this although looks like shit
    auto platformer_state = std::static_pointer_cast<State>(state);
    // loop through
    table.ProcessVector("keys", [platformer_state] (luabridge::LuaRef ref) {
        int id = ref["id"].cast<int>();
        std::string action = ref["action"].cast<std::string>();
        if (action == "changestate") {
            std::string nextState = ref["state"].cast<std::string>();
            platformer_state->AddKey(id, std::make_shared<StateTransition>(nextState));
        } else if (action == "callback") {
            luabridge::LuaRef func = ref["func"];
            platformer_state->AddKey(id, std::make_shared<StateCallback>(func));
//        } else if (action == "playanim") {
//            std::string anim = ref["anim"].cast<std::string>();
//            platformer_state->AddKey(id, std::make_shared<PlayAnim>(platformer_state.get(), anim));
//        }
        }
    });

}


void Walk25StateFactory::init(const LuaTable & table, std::shared_ptr<State> state) {
    StateFactory::init(table, state);

}

std::shared_ptr<State> Walk25StateFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    float speed = table.Get<float>("speed");
    float a = table.Get<float>("acceleration");
    bool fliph = table.Get<bool>("fliph");
    bool fourWay = table.Get<bool>("fourway", true);
    char dir = table.Get<char>("dir", 'e');
    auto ptr = std::make_shared<Walk25>(speed, a, fliph, fourWay, dir);
    init(table, ptr);
    return ptr;

}



void Jump25StateFactory::init(const LuaTable & table, std::shared_ptr<State> state) {
    StateFactory::init(table, state);

}
std::shared_ptr<State> Jump25StateFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    float speed = table.Get<float>("speed");
    float a = table.Get<float>("acceleration");
    auto ptr = std::make_shared<Jump25>(speed, a);
    init(table, ptr);
    return ptr;

}

void SimpleStateFactory::init(const LuaTable & table, std::shared_ptr<State> state) {
    StateFactory::init(table, state);

}

std::shared_ptr<State> SimpleStateFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string anim = table.Get<std::string>("anim");
    auto ptr = std::make_shared<SimpleState>(anim);
    init (table, ptr);
    return ptr;

}

void Hit25StateFactory::init(const LuaTable & table, std::shared_ptr<State> state) {
    StateFactory::init(table, state);

}

std::shared_ptr<State> Hit25StateFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string anim = table.Get<std::string>("anim");
    auto ptr = std::make_shared<Hit25>(anim);
    init(table, ptr);
    return ptr;

}

std::shared_ptr<Component> GarbageCollectCompFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    std::string target = table.Get<std::string>("target");
    glm::vec2 maxDist = table.Get<glm::vec2>("max_dist");
    auto ptr = std::make_shared<GarbageCollect>(target, maxDist.x, maxDist.y);
    return ptr;


}